#   Choose whatever C compiler you want. Tested with gcc, clang, tcc, and pcc
#   on GNU/Linux (Debian, Ubuntu, Fedora, and more) and FreeBSD 12.1.
CC = gcc

#   Compiler arguments (works for GCC, Clang, TCC, and PCC).
#   -O3 is optimization level 3
#   -c means compiler without linking.
#   -I../ means include the parent directory so libtmpl/ is in the path.
#   -flto is link time optimization.
CARGS = -O3 -c -I../ -flto

#   Location where the .h files will be stored.
INCLUDE_TARGET = /usr/local/include/libtmpl

#   C file for creating tmpl_endianness.h
DET_END_FILE = ./det_end.c
DET_END_EXEC = det_end_out

#   Location of source files for all sub-libraries.
SRCS_MATH = ./src/math/*.c
SRCS_BYTE = ./src/bytes/*.c
SRCS_CMPL = ./src/complex/*.c
SRCS_EUC2 = ./src/euclidean_planar_geometry/*.c
SRCS_IEEE = ./src/ieee754/*.c

all: make

make:
	make clean
	make create_include_folder
	make determine_endianness
	make compile
	make clean

clean:
	rm -f *.so *.o

#   Check if /usr/local/include/libtmpl/ is already a directory. If not then
#   create this via mkdir. If it already exists, remove the old header files in
#   case libtmpl has been updated since the most recent build on your computer.
#   Lastly, copy the contents of the include/ directory to
#   /usr/local/include/libtmpl/include/. Most compilers automatically have this
#   in their path so libtmpl files can be included via:
#	#include <libtmpl/include/file_name.h>
create_include_folder:
	if [ ! -d $(INCLUDE_TARGET) ]; then \
		sudo mkdir -p $(INCLUDE_TARGET)/include/; \
	else \
		sudo rm -f "$includedir/include/*.h"; \
	fi

	sudo cp ./include/*.h $(INCLUDE_TARGET)/include/

determine_endianness:
	$(CC) $(DET_END_FILE) -o $(DET_END_EXEC)
	./$(DET_END_EXEC)
	make clean
	rm -f $(DET_END_EXEC)


compile:
	if !($(CC) $(CARGS) $(SRCS_MATH)); then exit 1; fi
	if !($(CC) $(CARGS) $(SRCS_CMPL)); then exit 1; fi
	if !($(CC) $(CARGS) $(SRCS_BYTE)); then exit 1; fi
	if !($(CC) $(CARGS) $(SRCS_EUC2)); then exit 1; fi
	if !($(CC) $(CARGS) $(SRCS_IEEE)); then exit 1; fi

