#!/bin/bash

# This script is for removing libtmpl from your system.
SONAME="libtmpl.so"
SODIR="/usr/local/lib"
INCLUDE_TARGET=/usr/local/include/libtmpl
END_HEADER=include/tmpl_endianness.h

echo -e "\nRemoving libtmpl:"
echo -e "\tClearing older files..."
rm -f *.so *.o

echo -e "\tRemoving endianness header file..."
if [ -e "$END_HEADER" ]; then
    rm -f "$END_HEADER";
fi

echo -e "\tRemoving include directory if it exists..."
if [ -d "$INCLUDE_TARGET" ]; then
    sudo rm -rf "$INCLUDE_TARGET";
fi

echo -e "\tRemoving shared object file if it exists..."
if [ -e "$SODIR/$SONAME" ]; then
    sudo rm -f "$SODIR/$SONAME";
fi

echo -e "\nlibtmpl removed."

echo -e "\nWe're sad to see you go! Please fill out our online survey at-"
echo "Joking of course, this is an open source C library. If there are any"
echo "improvements you'd like to suggest, please raise an issue or leave a"
echo "comment on the GitHub page: https://github.com/ryanmaguire/libtmpl"
