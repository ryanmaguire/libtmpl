#!/bin/bash

# This script is for removing libtmpl from your system.
SONAME="libtmpl.so"
SODIR="/usr/local/lib"
INCLUDE_TARGET=/usr/local/include/libtmpl
END_HEADER=include/tmpl_endianness.h

echo "Removing libtmpl:"
echo "    Clearing older files..."
rm -f *.so *.o

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
