/**
 * @file    ICodonUsageModifier.h
 * @brief   ICodonUsageModifier provides the interface to humanizer service.
 *
 * @author  Franco Riberi
 * @email   fgriberi AT gmail.com
 *
 * Contents: Header file for acuoso providing struct ICodonUsageModifier.
 *
 * System:   acuoso: Abstract Codon Usage Optimization Software for Organisms
 * Language: C++
 *
 * @date    October 2012
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

#ifndef I_CODON_USAGE_MODIFIER_H
#define I_CODON_USAGE_MODIFIER_H

#include <biopp/biopp.h>
#include <mili/mili.h>
#include "acuoso/BackendExceptions.h"

namespace acuoso
{

struct ICodonUsageModifier;

/** @brief Represent all backends availables
*
*/
typedef std::list<std::string> Backends;

/** @brief Represent a FactoryRegistry
*
*/
typedef mili::FactoryRegistry<ICodonUsageModifier, std::string> CodonUsageModifier;
        
/** @brief Interface for sequence's humanized services.
*
*/
struct ICodonUsageModifier
{
    typedef mili::Factory<std::string, ICodonUsageModifier> Factory;

    /** @brief Enum that representing all organisms supported
    *
    */
    enum Organism
    {
        minimumValue = 1,
        SCerevisiae = minimumValue,
        EColi,
        HSapiens, //human
        CElegans,
        DMelanogaster,
        BSubtilis,
        numberOfOrganisms
    };

    /** @brief Humanized an messenger RNA sequence.
     *
     * @param src: sequence the messenger RNA to humanized.
     * @param dest: sequence the messenger RNA as result.
     * @return void
     */
    virtual void changeCodonUsage(const biopp::AminoSequence& src, biopp::NucSequence& dest) const = 0;

    /** @brief Set organism to humanizer.
     *
     * @param org: organism to set
     * @return void
     */
    virtual void setOrganism(Organism org) = 0;

    /** @brief Destructor of class
     *
     */
    virtual ~ICodonUsageModifier() {}

    /** @brief Get available backends to optimizer
     *
     * Method that provide the available backends for optimizer service.
     * @param backends: to fill with different backends
     * @return void
     */
    static void getAvailableBackends(Backends& backends)
    {
        Factory::KeyIterator it(CodonUsageModifier::getConstructibleObjectsKeys());
        while (!it.end())
        {
            backends.push_back(*it);
            it++;
        }
    }
};

} //namespace acuoso
#endif /* I_CODON_USAGE_MODIFIER_H */
