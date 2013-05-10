/*
 * @file      HelperAcuoso.cpp
 * @brief     This is the implementation of HelperAcuoso interface.
 *
 * @author    Franco Riberi
 * @email     fgriberi AT gmail.com
 *
 * Contents:  Source file for acuoso providing class HelperAcuoso implementation.
 *
 * System:    acuoso: Abstract Codon Usage Optimization Software for Organisms
 * Language:  C++
 *
 * @date May 2013
 *
 * Copyright (C) 2013 Franco Riberi, FuDePAN
 *
 * This file is part of acuoso.
 *
 * acuoso is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of tghe License, or
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

#include "acuoso/HelperAcuoso.h"
#include "acuoso/BackendExceptions.h"

namespace acuoso
{

namespace helper
{

static const int SYSTEM_ERROR = -1;
static const int FILE_ERROR = -1;

void changeDirectory(const std::string& path)
{
    if (chdir(path.c_str()) != 0)
    {
        throw InvalidPathChdir();
    }
}

int runCommand(const Command& cmd)
{
    const int status = system(cmd.c_str());
    if (status == SYSTEM_ERROR)
    {
		throw SystemCallException();	        
    }
    else
    {
        if (WIFEXITED(status))
        {
            return WEXITSTATUS(status);
        }
        else
        {
            if (WIFSIGNALED(status))
            {
                throw RNABackendException("Termination signal " + mili::to_string(WTERMSIG(status)) + " in " + cmd);
            }
            else
            {
				throw NonTerminationException();                
            }
        }
    }
}

void removeFile(const std::string& fileName)
{
    if (unlink(fileName.c_str()) == acuoso::helper::FILE_ERROR)
    {
        throw RNABackendException("Error in unlink of '" + fileName + "': " + std::string(strerror(errno)));
    }
}

} //namespace helper
} //namespace acuoso