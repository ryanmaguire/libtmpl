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
result="test_results/`uname -s`_`uname -m`_`date +%Y_%m_%d_%H_%M_%S`.txt"
touch $result
LINELEN=50
BUFFERLEN=5
DARGS="-I/usr/local/include/ -L/usr/local/lib/ -Wno-float-equal -Wno-padded"
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

for OPT in "" "-O3"; do
    if [[ "$OPT" == "-O3" ]]; then
        echo "=================" >> $result
        echo "WITH OPTIMIZATION" >> $result
        echo "=================" >> $result
    else
        echo "===============" >> $result
        echo "NO OPTIMIZATION" >> $result
        echo "===============" >> $result
    fi

    for dir in */; do
        if [[ "$dir" == *"test_results"* ]]; then
            continue
        fi
        echo "$dir" >> $result
        for FILE in `find $dir/ -iname "*unit_test*.c" | sort`; do
            FILENAME=$(basename -- $FILE)
            LEN=$(($LINELEN-${#FILENAME}))
            for CCOMP in $COMPILER_LIST; do
    	        LEN2=$(($BUFFERLEN - ${#CCOMP}))
                if [ "$CCOMP" == "clang" ]; then
                    CARGS="$DARGS -Weverything $OPT"
                else
                    CARGS="$DARGS -Wall -Wextra -Wpedantic $OPT"
                fi

                if !($CCOMP $CARGS $FILE -o test.out -ltmpl -lm); then
                    printf "    $FILENAME %-${LEN}s| " >> $result
                    printf "$CCOMP:%${LEN2}s NO COMPILE\n" >> $result
                else
                    printf "    $FILENAME %-${LEN}s| " >> $result
                    OUT=`./test.out`
                    printf "$CCOMP:%-${LEN2}s $OUT\n" >> $result
                    rm -f test.out
                fi
            done
        done
    done
done
