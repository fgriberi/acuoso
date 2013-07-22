/**
 * @file    SequencesOptimizer.h
 * @brief   SequencesOptimizer provides the interface to optimize or humanize a fasta file.
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

/** @brief Class that provides the interface to optimize a fasta file.
*
*/
class SequencesOptimizer
{
public:

    /** @brief Represent a filename
     *
     */
    typedef std::string FileName;

    /** @brief Constructor of class
     *
     */
    SequencesOptimizer();

    /** @brief Constructor of class with parameter
     *
     * @param opt: backend to optimize sequences
     */
    SequencesOptimizer(ICodonUsageModifier* codonUsage, ICodonUsageModifier::Organism org);

    /** @brief Destructor of class
     *
     */
    ~SequencesOptimizer();

    /** @brief Optimizes all sequence of fasta file
    *
    * @param inputFile: input file name
    * @return void
    */
    void optimizer(const std::string& inputFile);

private:

    /** @brief Generate output file
     *
     * @return void
     */
    void generateFile();

    /** @brief Specific backend to optimize sequences
     *
     */
    ICodonUsageModifier* specificOptimizer;

    /** @brief Represent output file with sequences humanized
     * 
     */
    FileName outputFileName;    
};

} //namespace acuoso