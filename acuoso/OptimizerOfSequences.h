/**
 * @file    OptimizerOfSequences.h
 * @brief   OptimizerOfSequences provides the interface to optimized a fasta file.
 *
 * @author  Franco Riberi
 * @email   fgriberi AT gmail.com
 *
 * Contents: Header file for acuoso providing OptimizerSequence.
 *
 * System:   acuoso: Abstract Codon Usage Optimization Software for Organisms
 * Language: C++
 *
 * @date    April 2013
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

#include <biopp/biopp.h>
#include <biopp-filer/bioppFiler.h>
#include "acuoso/ICodonUsageModifier.h"
#include "acuoso/BackendExceptions.h"

namespace acuoso
{

/** @brief Class that provides the interface to optimized a fasta file.
*
*/
class OptimizerOfSequences
{
public:

    /** @brief Constructor of class
     *
     */
    OptimizerOfSequences();

    /** @brief Constructor of class with parameter
     *
     * @param opt: backend to optimize sequences
     */
    OptimizerOfSequences(ICodonUsageModifier* codonUsage, ICodonUsageModifier::Organism org);

    /** @brief Destructor of class
     *
     */
    ~OptimizerOfSequences();

    /** @brief Optimizes all sequence of fasta file
    *
    * @param fileInput: input file name
    * @return void
    */
    void optimizer(const std::string& fileInput);

private:

    /** @brief Generate output file
     *
     * @return void
     */
    void generateFile();

    /// Specific backend to optimizer sequence
    ICodonUsageModifier* specificOptimizer;
};

} //namespace acuoso