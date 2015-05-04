/**
 * @file     SequencesOptimizer.cpp
 * @brief    SequencesOptimizer is the implementation of SequencesOptimizer interface.
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Source file for acuoso providing the implementation of SequencesOptimizer interface.
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
#include "acuoso/SequencesOptimizer.h"

namespace acuoso
{

SequencesOptimizer::SequencesOptimizer()
{
    _specificOptimizer = CodonUsageModifier::new_class("GeneDesign");
    _specificOptimizer->setOrganism(ICodonUsageModifier::HSapiens); //human
}

SequencesOptimizer::SequencesOptimizer(ICodonUsageModifier* opt, ICodonUsageModifier::Organism org)
{
    _specificOptimizer = opt;
    _specificOptimizer->setOrganism(org);
}

SequencesOptimizer::~SequencesOptimizer()
{
    delete _specificOptimizer;
}

void SequencesOptimizer::generateFile()
{
    const std::string path = "/tmp/";
    std::string prefix = "acuoso-XXXXXX";
    etilico::createTemporaryFile(_outputFileName, path, prefix);
}

void SequencesOptimizer::optimizer(const FileName& inputFile)
{
    bioppFiler::FastaParser<biopp::NucSequence> fileSequence(inputFile);
    biopp::NucSequence sequenceToOptimizer;
    biopp::NucSequence sequenceOptimize;
    std::string description;
    generateFile();
    bioppFiler::FastaSaver<biopp::NucSequence> fs(_outputFileName.c_str());
    while (fileSequence.getNextSequence(description, sequenceToOptimizer))
    {
        biopp::AminoSequence aminoTempSequence;
        sequenceToOptimizer.translate(aminoTempSequence);
        _specificOptimizer->changeCodonUsage(aminoTempSequence, sequenceOptimize);
        fs.saveNextSequence(description, sequenceOptimize);
    }
}

} // namespace acuoso