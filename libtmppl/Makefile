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
#   Date:       August 31, 2021                                                #
################################################################################

#   Choose whatever C compiler you want. Tested with g++ and clang++.
CC = c++

# Name of the created Share Object file (.so).
SONAME = libtmppl.so

# Location to store SONAME at the end of building.
SODIR = /usr/local/lib

# Location where the .h files will be stored.
INCLUDE_TARGET = /usr/local/include/libtmppl

# Compiler arguments (works for GCC, Clang, TCC, and PCC).
# -O3 is optimization level 3
# -c means compile without linking.
# -I../ includes that directory in the path.
# -flto is link time optimization.
# -fopenmp uses OpenMP.
CPPARGS = $(CARGS) -O3 -c -flto -I../../ -I../
CPPARGSOMP = $(CARGS) -O3 -c -flto -fopenmp -I../../ -I../

# Linking arguments. -O3, -I, and -flto are the same as before.
# -lm means link against the standard math library.
# -o means create an output.
# -shared means the output is a shared object, like a library file.
LARGS = -O3 -I../ -flto -shared -o $(SONAME) -ltmpl
LARGSOMP = -O3 -fopenmp -L../ -flto -shared -o $(SONAME) -ltmpl

#   Location of source files for all sub-libraries.
SRCS = ./src/*.cpp
SRCS_LINK = ./*.o

.PHONY: clean install uninstall all omp

all: make

make:
	rm -f *.o
	$(CC) $(CPPARGS) $(SRCS)
	$(CC) $(SRCS_LINK) $(LARGS)
	rm -f *.o

# Same as make, but compiling with OpenMP support.
omp:
	rm -f *.o
	$(CC) $(CPPARGSOMP) $(SRCS)
	$(CC) $(SRCS_LINK) $(LARGSOMP)
	rm -f *.o

install:
	mkdir -p /usr/local/include/libtmppl/include/
	cp ./include/*.hpp /usr/local/include/libtmppl/include/
	cp $(SONAME) /usr/local/lib/$(SONAME)

clean:
	rm -f *.o *.so

uninstall:
	rm -f *.so *.o
	rm -f /usr/local/lib/$(SONAME)
	rm -rf /usr/local/include/libtmppl/
