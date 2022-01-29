#!/bin/bash

################################################################################
#                                  LICENSE                                     #
################################################################################
#   This file is part of libtmpl.                                              #
#                                                                              #
#   libtmpl is free software: you can redistribute it and/or modify            #
#   it under the terms of the GNU General Public License as published by       #
#   the Free Software Foundation, either version 3 of the License, or          #
#   (at your option) any later version.                                        #
#                                                                              #
#   libtmpl is distributed in the hope that it will be useful,                 #
#   but WITHOUT ANY WARRANTY; without even the implied warranty of             #
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
#   GNU General Public License for more details.                               #
#                                                                              #
#   You should have received a copy of the GNU General Public License          #
#   along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.          #
################################################################################
#   Author:     Ryan Maguire                                                   #
#   Date:       March 10, 2021                                                 #
################################################################################

# This script is for removing libtmpl from your system.
SONAME="libtmpl.so"
SODIR="/usr/local/lib"
INCLUDE_TARGET=/usr/local/include/libtmpl
END_HEADER=include/tmpl_endianness.h

echo "Removing libtmpl:"
echo "    Clearing older files..."
rm -f *.so *.o *.obj *.lib

echo "    Removing endianness header file if it exists..."
if [ -e "$END_HEADER" ]; then
    rm -f "$END_HEADER";
fi

echo -e "    Removing include directory if it exists..."
if [ -d "$INCLUDE_TARGET" ]; then
    sudo rm -rf "$INCLUDE_TARGET";
fi

echo "    Removing shared object file if it exists..."
if [ -e "$SODIR/$SONAME" ]; then
    sudo rm -f "$SODIR/$SONAME";
fi

echo "libtmpl removed."
