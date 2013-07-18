/**
 * @file     OptimizerOfSequences.cpp
 * @brief    OptimizerOfSequences is the implementation of OptimizerOfSequences interface.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Source file for acuoso providing the implementation of OptimizerOfSequences interface.
 *
 * System:   acuoso: Abstract Codon Usage Optimization Software for Organisms
 * Language: C++
 *
 * @date      April 2013
 *
 * This file is part of Acuoso.
 *
 * Copyright (C) 2013 - Franco Riberi, FuDePAN.
 *
 * Acuoso is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Acuoso is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Acuoso. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <fstream>
#include <etilico/etilico.h>
#include "acuoso/OptimizerOfSequences.h"

namespace acuoso
{

/** @brief Represent a filename
 *
 */
typedef std::string FileName;

/** @brief Represent a file
 *
 */
typedef std::ofstream File;

static const std::string FILE_OUTPUT = "project/acuoso/sequenceOptimized.fasta";

OptimizerOfSequences::OptimizerOfSequences()
{
    specificOptimizer = CodonUsageModifier::new_class("GeneDesign");
    specificOptimizer->setOrganism(ICodonUsageModifier::HSapiens); //human
}

OptimizerOfSequences::OptimizerOfSequences(ICodonUsageModifier* opt, ICodonUsageModifier::Organism org)
{
    specificOptimizer = opt;
    specificOptimizer->setOrganism(org);
}

OptimizerOfSequences::~OptimizerOfSequences()
{
    delete specificOptimizer;
}

void OptimizerOfSequences::generateFile()
{
    File file;
    if (file.is_open())
    {
        file.close();
    }
    std::string currentPath;
    etilico::getCurrentPath(currentPath);
    currentPath += FILE_OUTPUT;
    file.open(currentPath.c_str());
    if (!file)
    {
        throw FileNotFound();
    }
}

void OptimizerOfSequences::optimizer(const FileName& fileInput)
{
    generateFile();
    bioppFiler::FastaParser<biopp::NucSequence> fileSequence(fileInput);
    biopp::NucSequence sequenceToOptimizer;
    biopp::NucSequence sequenceOptimize;
    std::string description;
    bioppFiler::FastaSaver<biopp::NucSequence> fs(FILE_OUTPUT.c_str());
    while (fileSequence.getNextSequence(description, sequenceToOptimizer))
    {
        biopp::AminoSequence aminoTempSequence;
        sequenceToOptimizer.translate(aminoTempSequence);
        specificOptimizer->changeCodonUsage(aminoTempSequence, sequenceOptimize);
        fs.saveNextSequence(description, sequenceOptimize);
    }
}

} // namespace acuoso