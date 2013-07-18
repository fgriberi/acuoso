/**
 * @file     GeneDesign.h
 * @brief    Provide the interface to GeneDesign backend.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Source file for acuoso providing backend GeneDesign implementation.
 *
 * System:   acuoso: Abstract Codon Usage Optimization Software for Organisms
 * Language: C++
 *
 * @date      July 2013
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

#ifndef GENE_DESIGN_H
#error Internal header file, Only include in GeneDesign.cpp file.
#endif

#include <biopp/biopp.h>
#include <biopp-filer/bioppFiler.h>
#include <etilico/etilico.h>
#include "acuoso/ICodonUsageModifier.h"

namespace acuoso
{

/** @breif Provide the interface to GeneDesign backend.
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

} //namespace acuoso