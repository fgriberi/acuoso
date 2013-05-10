/*
 * @file   HelperAcuoso.h
 * @brief  This header defines necessary methods in acuoso.
 *
 * @author Franco Riberi
 * @email  fgriberi AT gmail.com
 *
 * Contents:  Header file for acuoso providing necessary methods
 *
 * System:    acuoso: Abstract Codon Usage Optimization Software for Organisms 
 * Language:  C++
 *
 * @date May 10, 2013
 *
 * Copyright (C) 2013 Franco Riberi, FuDePAN
 *
 * This file is part of acuoso.
 *
 * acuoso is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * acuoso is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with acuoso.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _HELPER_ACUOSO_H
#define _HELPER_ACUOSO_H

#include <fstream>
#include <cerrno>
#include <unistd.h>

namespace acuoso
{

/**
 * Filename path
 */
typedef std::string Path;

typedef std::string Command;

namespace helper
{

/** @brief Move to path directory
* 
* @param path: path to move
* @return void
*/
void changeDirectory(const Path& path);

/** @brief execute a Command
 *
 * Execute a give Command using a system call
 * @param cmd: the RNA Backend Command
 * @return int: status 
 */
int runCommand(const Command& cmd);

/** @brief Remove a file
 * 
 * @param fileName: name file to remove
 * @return void
 */
void removeFile(const Path& fileName);

} //namespace helper
} //namespace fideo

#endif  /* _HELPER_ACUOSO_H */
