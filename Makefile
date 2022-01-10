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

#   Choose whatever C compiler you want. Tested with gcc, clang, tcc, and pcc
#   on GNU/Linux (Debian, Ubuntu, Fedora, and more) and FreeBSD 12.1.
CC = cc

# Compiler arguments (works for GCC, Clang, TCC, and PCC).
# -O3 is optimization level 3
# -c means compile without linking.
# -I../ includes that directory in the path.
# -flto is link time optimization.
# -fopenmp uses OpenMP.
CARGS = -O3 -c -flto -I../
CARGSOMP = -O3 -c -flto -fopenmp -I../

# Linking arguments. -O3, -I, and -flto are the same as before.
# -lm means link against the standard math library.
# -o means create an output.
# -shared means the output is a shared object, like a library file.
LARGS = -O3 -flto -shared -o $(SONAME) -lm
LARGSOMP = -O3 -fopenmp -flto -shared -o $(SONAME) -lm

# Name of the created Share Object file (.so).
SONAME = libtmpl.so

# Location to store SONAME at the end of building.
SODIR = /usr/local/lib

# Location where the .h files will be stored.
INCLUDE_TARGET = /usr/local/include/libtmpl

# Name of the header file containing endianness info. We need to create this.
END_HEADER = ./include/tmpl_endianness.h

# C file for determining endianness and creating END_HEADER.
DET_END_FILE = ./det_end.c

# Name of the executable create by DET_END_FILE.
DET_END_EXEC = det_end_out

# Location of source files for all sub-libraries.
SRCS = ./src/**/*.c
SRCS_LINK = ./*.o

all: make

make:
	rm -f *.so *.o
	sudo rm -f $(END_HEADER)
	sudo rm -rf $(INCLUDE_TARGET)
	sudo mkdir -p $(INCLUDE_TARGET)/include/
	sudo rm -f $(SODIR)/$(SONAME)
	$(CC) $(DET_END_FILE) -o $(DET_END_EXEC)
	./$(DET_END_EXEC)
	rm -f $(DET_END_EXEC)
	$(CC) $(CARGS) $(SRCS)
	$(CC) $(SRCS_LINK) $(LARGS)
	sudo cp ./include/*.h $(INCLUDE_TARGET)/include/
	sudo mv $(SONAME) $(SODIR)
	rm -f *.o

inplace:
	rm -f *.so *.o
	$(CC) $(DET_END_FILE) -o $(DET_END_EXEC)
	./$(DET_END_EXEC)
	rm -f $(DET_END_EXEC)
	$(CC) $(CARGS) $(SRCS)
	$(CC) $(SRCS_LINK) $(LARGS)
	rm -f *.o

# Same as make, but compiling with OpenMP support.
omp:
	rm -f *.so *.o
	sudo rm -f $(END_HEADER)
	sudo rm -rf $(INCLUDE_TARGET)
	sudo mkdir -p $(INCLUDE_TARGET)/include/
	sudo rm -f $(SODIR)/$(SONAME)
	$(CC) $(DET_END_FILE) -o $(DET_END_EXEC)
	./$(DET_END_EXEC)
	rm -f $(DET_END_EXEC)
	$(CC) $(CARGSOMP) $(SRCS)
	$(CC) $(SRCS_LINK) $(LARGSOMP)
	sudo cp ./include/*.h $(INCLUDE_TARGET)/include/
	sudo mv $(SONAME) $(SODIR)
	rm -f *.o

# Same as inplace, but compiling with OpenMP support.
omp_inplace:
	rm -f *.so *.o
	$(CC) $(DET_END_FILE) -o $(DET_END_EXEC)
	./$(DET_END_EXEC)
	rm -f $(DET_END_EXEC)
	$(CC) $(CARGSOMP) $(SRCS)
	$(CC) $(SRCS_LINK) $(LARGSOMP)
	rm -f *.o

uninstall:
	rm -f *.so *.o
	sudo rm -f $(SODIR)/$(SONAME)
	sudo rm -rf $(INCLUDE_TARGET)/

