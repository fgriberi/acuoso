/**
 * @file     GeneDesign.cpp
 * @brief    GeneDesign is an implementation of ICodonUsageModifier interface.
 *           It's a specific backend to humanizer. It's a external software.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Source file for acuoso providing backend GeneDesign implementation.
 *
 * System:   acuoso: Abstract Codon Usage Optimization Software for Organisms
 * Language: C++
 *
 * @date      October 2012
 *
 * This file is part of acuoso.
 *
 * Copyright (C) 2012 - Franco Riberi, FuDePAN.
 *
 * acuoso is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * acuoso is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with acuoso. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <unistd.h>
#include <biopp/biopp.h>
#include <biopp-filer/bioppFiler.h>
#include <etilico/etilico.h>
#include "acuoso/ICodonUsageModifier.h"

/** @brief Temporal functions
*
*/
int linkFictitious()
{
    return 1;
}

/** @brief Temporal method requerid to execute remo
*
* @param derivedKey: name of derived class
* @return pointer to the base class
*/
acuoso::ICodonUsageModifier* getDerived(const std::string& derivedKey)
{
    acuoso::ICodonUsageModifier* const ptr = mili::FactoryRegistry<acuoso::ICodonUsageModifier, std::string>::new_class(derivedKey);
    mili::assert_throw<acuoso::InvalidDerived>(ptr != NULL);
    return ptr;
}

namespace acuoso
{

/** @breif Is an implementation of ICodonUsageModifier interface.
*
*/
class GeneDesign : public ICodonUsageModifier
{
private:

    virtual void changeCodonUsage(const biopp::AminoSequence& src, biopp::NucSequence& dest) const;
    virtual void setOrganism(Organism organism);
    virtual ~GeneDesign();

    /** @brief Generates the command to call geneDesign
    *
    * @param fileName: input of geneDesing
    * @param cmd: to fill with command generated
    * @return void
    */
    void generateCommand(const std::string& fileName, etilico::Command& cmd) const;

    /** @brief Controls whether geneDesign generates an error file
    *
    * @param nameFile: input file name
    * @return void
    */
    void checkErrorFile(const std::string& nameFile) const;

    /** @brief Gets the file name
    *
    * @param toParse: path to parse
    * @param fileName: to fill with file name
    * @return void
    */
    void getFileOutput(std::stringstream& toParse, std::string& fileName) const;

    /** @brief Store specific organism
    *
    */
    Organism org;
};

static const std::string FILE_ERROR = "error.txt";
static const std::string FASTA_EXTENSION = ".FASTA";
static const std::string FILE_EXTENSION = "_gdRT_";
static const std::string EXTENSION_DIRECTORY = "_gdRT";
static const std::string RUN_PATH = "runGD";

static const size_t SIZE_EXPECTED = 3;
static const size_t NAME_FILE = 2;

REGISTER_FACTORIZABLE_CLASS(ICodonUsageModifier, GeneDesign, std::string, "GeneDesign");

GeneDesign::~GeneDesign()
{}

void GeneDesign::setOrganism(Organism organism)
{
    org = organism;
}

void GeneDesign::generateCommand(const std::string& fileName, etilico::Command& cmd) const
{
    std::stringstream ss;
    ss << "perl Reverse_Translate.pl -i ";
    ss << fileName;
    ss << " -o ";

    switch (org)
    {
        case SCerevisiae:
            ss << 1;
            break;
        case EColi:
            ss << 2;
            break;
        case HSapiens:
            ss << 3;
            break;
        case CElegans:
            ss << 4;
            break;
        case DMelanogaster:
            ss << 5;
            break;
        case BSubtilis:
            ss << 6;
            break;
        default:
            throw OrganismNotSupported();
    }
    cmd = ss.str();
}

void GeneDesign::checkErrorFile(const std::string& nameFile) const
{
    std::ifstream fileError;
    fileError.open(nameFile.c_str());
    if (fileError)
    {
        throw ErrorHumanizer();
    }
    fileError.close();
}

void GeneDesign::getFileOutput(std::stringstream& toParse, std::string& fileName) const
{
    std::vector<std::string> result;
    toParse >> mili::Separator(result, '/');
    if (result.size() != SIZE_EXPECTED)
    {
        throw IndexOutOfRange();
    }
    fileName = result[NAME_FILE];
}

void GeneDesign::changeCodonUsage(const biopp::AminoSequence& src, biopp::NucSequence& dest) const
{
    dest.clear();

    //move to the directory where is the humanize
    std::string executablePath;
    etilico::Config::getInstance()->getPath(RUN_PATH, executablePath);
    if (chdir(executablePath.c_str()) != 0)
    {
        throw ChdirException();
    }

    std::string fileName;
    etilico::createTemporaryFilename(fileName);
    bioppFiler::FastaSaver<biopp::AminoSequence> fs(fileName.c_str());
    fs.saveNextSequence("temp", src);
    etilico::Command command; //Command is: perl Reverse_Translate.pl -i FILE_NAME -o organism
    generateCommand(fileName, command);
    etilico::runCommand(command);

    //move to the directory where is the result of humanize
    const std::string directoryResult = fileName + EXTENSION_DIRECTORY;
    if (chdir(directoryResult.c_str()) != 0)
    {
        throw ChdirException();
    }
    checkErrorFile(FILE_ERROR.c_str());

    std::stringstream output;
    output << fileName << FILE_EXTENSION << org << FASTA_EXTENSION;
    std::string fileOutput;
    getFileOutput(output, fileOutput);

    bioppFiler::FastaParser<biopp::NucSequence> fp(fileOutput.c_str());
    std::string name;
    if (!fp.getNextSequence(name, dest))
    {
        throw EmptySequence();
    }
    biopp::AminoSequence acTemp;
    dest.translate(acTemp);
    assert(src == acTemp);
    mili::assert_throw<UnlinkException>(unlink(fileName.c_str()) == 0);
    mili::assert_throw<UnlinkException>(unlink(fileOutput.c_str()) == 0);
    mili::assert_throw<RmdirkException>(rmdir(directoryResult.c_str()) == 0);
}

} // namespace acuoso
