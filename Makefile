#   Choose whatever C compiler you want. Tested with gcc, clang, tcc, and pcc
#   on GNU/Linux (Debian, Ubuntu, Fedora, and more) and FreeBSD 12.1.
CC = cc

# Name of the created Share Object file (.so).
SONAME = libtmpl.so

# Location to store SONAME at the end of building.
SODIR = /usr/local/lib

#   Compiler arguments (works for GCC, Clang, TCC, and PCC).
#   -O3 is optimization level 3
#   -c means compiler without linking.
#   -I/usr/local/include includes that directory in the path..
#   -flto is link time optimization.
CARGS = -O3 -c -flto -I/usr/local/include

# Linking arguments. -O3, -I, and -flto are the same as before.
# -lm means link against the standard math library.
# -o means create an output.
# -shared means the output is a shared object, like a library file.
LARGS = -O3 -I/usr/local/include -flto -shared -o $(SONAME) -lm

# Location where the .h files will be stored.
INCLUDE_TARGET = /usr/local/include/libtmpl

# Name of the header file containing endianness info. We need to create this.
END_HEADER = ./include/tmpl_endianness.h

# C file for determining endianness and creating END_HEADER.
DET_END_FILE = ./det_end.c

# Name of the executable create by DET_END_FILE.
DET_END_EXEC = det_end_out

#   Location of source files for all sub-libraries.
SRCS =  ./src/**/*.c
SRCS_LINK = ./*.o

all: make

make:
	make clean
	make clean_old
	make determine_endianness
	make create_include_folder
	make compile
	make link
	make clean

clean:
	rm -f *.so *.o

clean_old:
	sudo rm -f $(END_HEADER)
	sudo rm -rf $(INCLUDE_TARGET)
	sudo mkdir -p $(INCLUDE_TARGET)/include/
	sudo rm -f $(SODIR)/$(SONAME)

create_include_folder:
	sudo cp ./include/*.h $(INCLUDE_TARGET)/include/

determine_endianness:
	$(CC) $(DET_END_FILE) -o $(DET_END_EXEC)
	./$(DET_END_EXEC)
	rm -f $(DET_END_EXEC)

compile:
	$(CC) $(CARGS) $(SRCS)

link:
	$(CC) $(SRCS_LINK) $(LARGS)
	sudo mv $(SONAME) $(SODIR)
