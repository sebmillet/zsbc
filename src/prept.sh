#!/bin/sh

# prept.sh

# Script to be used for zsbc compilation

# Takes one argument (the source .txt file) and creates a .c file, ready to be
# compiled and used as a data source inside zsbc.

# The target file defines an array of strings, the last element being NULL
# to mark the end.

VAR=$1
S=$2
T=$3

if [ -z "$T" ]; then
	echo "Usage: prept.sh VARNAME INFILE OUTFILE"
	echo "  Example: prept.sh ""zsbcman"" zsbc.txt zsbcman.c"
	exit
fi

echo "/* Created by prept.sh */" >$T
echo "/* DO NOT UPDATE MANUALLY */" >> $T
echo >> $T
echo "#include <stdlib.h>" >> $T
echo >> $T
echo "const char *${VAR}[] = {" >> $T

# the s/\xE2\x80\x90/-/ translation sequence is to replace '-' characters produced by
# 'nroff -man' (they are UTF-8) by simple '-' characters (plain ascii code).
sed 's/\xE2\x80\x90/-/; s/\\/\\\\/g; s/"/\\"/g; s/^\(.*\)$/\t"\1",/' "$S" >> $T

echo "\tNULL" >> $T
echo "};" >> $T
echo >> $T

