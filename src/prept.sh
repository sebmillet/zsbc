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
sed 's/\\/\\\\/g; s/"/\\"/g; s/^\(.*\)$/\t"\1",/' "$S" >> $T

echo "\tNULL" >> $T
echo "};" >> $T
echo >> $T

