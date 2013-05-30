/**
 * @file     BackendExceptions.h
 * @brief    This header defines all acuoso exceptions
 *
 * @author   Franco Riberi
 * @email    fgriberi AT gmail.com
 *
 * Contents: Header file for acuoso providing system exceptions definitions.
 *
 * System:   acuoso: Abstract Codon Usage Optimization Software for Organisms
 * Language: C++
 *
 * @date     April 2013
 *
 * This file is part of acuoso.
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


#ifndef BACKEND_EXCEPTIONS_H
#define BACKEND_EXCEPTIONS_H

#include <mili/mili.h>

namespace acuoso
{

struct AcuosoExceptionHierarchy {};
typedef mili::GenericException<AcuosoExceptionHierarchy> AcuosoException;

//State exception
class StateException: public AcuosoException
{
public:
    StateException(const std::string& description): AcuosoException(description) {}
};

DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidLengthSequence, AcuosoExceptionHierarchy, "RNA messenger length is not multiple of 3.");
DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidPathChdir, AcuosoExceptionHierarchy, "Error in chdir path.");
DEFINE_SPECIFIC_EXCEPTION_TEXT(ErrorHumanizer, AcuosoExceptionHierarchy, "Error in the humanization.");
DEFINE_SPECIFIC_EXCEPTION_TEXT(EmptySequence, AcuosoExceptionHierarchy, "Empty humanized sequence.");
DEFINE_SPECIFIC_EXCEPTION_TEXT(OrganismNotSupported, AcuosoExceptionHierarchy, "Organism not supported.");
DEFINE_SPECIFIC_EXCEPTION_TEXT(RNABackendException, AcuosoExceptionHierarchy, "RNABackend");
DEFINE_SPECIFIC_EXCEPTION_TEXT(SystemCallException, AcuosoExceptionHierarchy, "System call failed");
DEFINE_SPECIFIC_EXCEPTION_TEXT(NonTerminationException, AcuosoExceptionHierarchy, "Non termination for some reason");
DEFINE_SPECIFIC_EXCEPTION_TEXT(ChdirException, AcuosoExceptionHierarchy, "Invalid path of executable");
DEFINE_SPECIFIC_EXCEPTION_TEXT(UnlinkException, AcuosoExceptionHierarchy, "Error unlink file");
DEFINE_SPECIFIC_EXCEPTION_TEXT(RmdirkException, AcuosoExceptionHierarchy, "Error in rmdir");
DEFINE_SPECIFIC_EXCEPTION_TEXT(IndexOutOfRange, AcuosoExceptionHierarchy, "Index out of range");
DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidDerived, AcuosoExceptionHierarchy, "Invalid derived class");

}
#endif /* BACKEND_EXCEPTIONS_H */
