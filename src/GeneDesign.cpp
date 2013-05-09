/**
 * @file     GeneDesign.cpp
 * @brief    GeneDesign is the implementation of ICodonUsageModifier interface.
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
#include <mili/mili.h>
#include <fideo/fideo.h>
#include <biopp-filer/bioppFiler.h>
#include "acuoso/BackendExceptions.h"
#include "acuoso/ICodonUsageModifier.h"

namespace acuoso
{

class GeneDesign : public ICodonUsageModifier
{
private:    
    virtual void changeCodonUsage(const biopp::AminoSequence& src, biopp::NucSequence& dest) const;
    virtual void setOrganism(Organism organism);
    virtual ~GeneDesign() {}
    Organism org;
};

static const std::string FILE_ERROR = "error.txt";
static const std::string SEQUENCE = "sequence";
static const std::string FILE_NAME_INPUT = ".FASTA";
static const std::string FILE_NAME_OUTPUT = "_gdRT_";

static const std::string RUN_PATH = "runGD";
static const std::string RESULT_PATH = "resultGD";

REGISTER_FACTORIZABLE_CLASS(ICodonUsageModifier, GeneDesign, std::string, "GeneDesign");

void GeneDesign::setOrganism(Organism organism)
{
    org = organism;
}

void GeneDesign::changeCodonUsage(const biopp::AminoSequence& src, biopp::NucSequence& dest) const
{
    dest.clear();

    //move to the directory where is the humanize
    std::string executablePath;
    fideo::FideoConfig::getInstance()->getPath(RUN_PATH.c_str(), executablePath);
    if (chdir(executablePath.c_str()) != 0)
    {
        throw InvalidPathChdir();
    }

    std::stringstream file_name;
    file_name << SEQUENCE << FILE_NAME_INPUT;
    bioppFiler::FastaSaver<biopp::AminoSequence> fs(file_name.str());
    fs.saveNextSequence("temp", src);
    std::stringstream ss;
    ss << "perl Reverse_Translate.pl -i ";
    ss << file_name.str();
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

    const fideo::Command cmd = ss.str(); //Command is: perl Reverse_Translate.pl -i FILE_NAME -o organism
    fideo::helper::runCommand(cmd);

    //move to the directory where is the result of humanize
    fideo::FideoConfig::getInstance()->getPath(RESULT_PATH.c_str(), executablePath);
    if (chdir(executablePath.c_str()) != 0)
    {
        throw InvalidPathChdir();
    }

    std::ifstream fileError;
    fileError.open(FILE_ERROR.c_str());
    if (fileError)
    {
        throw ErrorHumanizer();
    }
    fileError.close();

    std::stringstream file_output;
    file_output << SEQUENCE << FILE_NAME_OUTPUT << org << FILE_NAME_INPUT;

    bioppFiler::FastaParser<biopp::NucSequence> fp(file_output.str());
    std::string name;
    if (!fp.getNextSequence(name, dest))
    {
        throw EmptySequence();
    }
    biopp::AminoSequence acTemp;
    dest.translate(acTemp);
    assert(src == acTemp);
    fideo::helper::removeFile(file_output.str());
}
}