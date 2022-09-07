#!/bin/bash

################################################################################
#                                   LICENSE                                    #
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
#   Date:       September 7, 2022                                              #
################################################################################

result="test_results/unit_test_results_`uname -m`_`date +%Y%m%d%H%M%S`.txt"
touch $result

COMPILER_LIST="gcc"

if  command -v clang &> /dev/null; then
    COMPILER_LIST="$COMPILER_LIST clang"
fi

if  command -v tcc &> /dev/null; then
    COMPILER_LIST="$COMPILER_LIST tcc"
fi

if  command -v pcc &> /dev/null; then
    COMPILER_LIST="$COMPILER_LIST pcc"
fi

echo "===============" >> $result
echo "NO OPTIMIZATION" >> $result
echo "===============" >> $result
echo "" >> $result

for FILE in `find . -iname "*unit_test*.c"`; do
    for CCOMP in $COMPILER_LIST; do
        CARGS="-I/usr/local/include/ -L/usr/local/lib/ -Wno-float-equal -Wno-padded"
        if [ "$CCOMP" == "clang" ]; then
            CARGS="$CARGS -Weverything"
        else
            CARGS="$CARGS -Wall -Wextra -Wpedantic"
        fi

        if !($CCOMP $CARGS $FILE -o test.out -ltmpl -lm); then
            echo "$FILE | $CCOMP: NO COMPILE" >> $result
        else
            printf "$FILE | $CCOMP: " >> $result
            ./test.out >> $result
            rm -f test.out
        fi
    done
done

echo "" >> $result
echo "=================" >> $result
echo "WITH OPTIMIZATION" >> $result
echo "=================" >> $result
echo "" >> $result

for FILE in `find . -iname "*unit_test*.c"`; do
    for CCOMP in $COMPILER_LIST; do
        CARGS="-I/usr/local/include/ -L/usr/local/lib/ -Wno-float-equal -Wno-padded -O3"
        if [ "$CCOMP" == "clang" ]; then
            CARGS="$CARGS -Weverything"
        else
            CARGS="$CARGS -Wall -Wextra -Wpedantic"
        fi

        if !($CCOMP $CARGS $FILE -o test.out -ltmpl -lm); then
            echo "$FILE | $CCOMP: NO COMPILE" >> $result
        else
            printf "$FILE | $CCOMP: " >> $result
            ./test.out >> $result
            rm -f test.out
        fi
    done
done

