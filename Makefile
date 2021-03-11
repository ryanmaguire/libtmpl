#   Choose whatever C compiler you want. Tested with gcc, clang, tcc, and pcc
#   on GNU/Linux (Debian, Ubuntu, Fedora, and more) and FreeBSD 12.1.
CC = gcc

# Name of the created Share Object file (.so).
SONAME = libtmpl.so

# Location to store SONAME at the end of building.
SODIR = /usr/local/lib

#   Compiler arguments (works for GCC, Clang, TCC, and PCC).
#   -O3 is optimization level 3
#   -c means compiler without linking.
#   -I../ means include the parent directory so libtmpl/ is in the path.
#   -flto is link time optimization.
CARGS = -O3 -c -I../ -flto

# Linking arguments. -O3, -I../, and -flto are the same as before.
# -lm means link against the standard math library.
# -o means create an output.
# -shared means the output is a shared object, like a library file.
LARGS = -O3 -I../ -flto -shared -o $(SONAME) -lm

# Location where the .h files will be stored.
INCLUDE_TARGET = /usr/local/include/libtmpl

# Name of the header file containing endianness info. We need to create this.
END_HEADER = include/tmpl_endianness.h

# C file for determining endianness and creating END_HEADER.
DET_END_FILE = ./det_end.c

# Name of the executable create by DET_END_FILE.
DET_END_EXEC = det_end_out

#   Location of source files for all sub-libraries.
SRCS_MATH = ./src/math/*.c
SRCS_BYTE = ./src/bytes/*.c
SRCS_CMPL = ./src/complex/*.c
SRCS_EUC2 = ./src/euclidean_planar_geometry/*.c
SRCS_IEEE = ./src/ieee754/*.c
SRCS_LINK = ./*.o

all: make

make:
	make clean
	make clean_old
	make create_include_folder
	make determine_endianness
	make compile
	make link
	make clean

clean:
	rm -f *.so *.o

clean_old:
	if [ -e $(END_HEADER) ]; then rm -f $(END_HEADER); fi
	if [ -d $(INCLUDE_TARGET) ]; then sudo rm -rf $(INCLUDE_TARGET); fi
	sudo mkdir -p $(INCLUDE_TARGET)/include/
	if [ -d $(SODIR)/$(SONAME) ]; then rm -f $(SODIR)/$(SONAME); fi

create_include_folder:
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

link:
	if !($(CC) $(SRCS_LINK) $(LARGS)); then exit 1; fi
	sudo mv $(SONAME) $(SODIR)


