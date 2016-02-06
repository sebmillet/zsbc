#!/bin/sh

# prepb.sh

# Script to be used for zsbc compilation

# Takes one argument (the source .b file) and creates a .c file, ready to be
# compiled and used as a data source inside zsbc.

# The target file is a succession of 'char'-type values, and that's it.
#   => that means, there is not intermediate structure like array of null-char
#      terminated strings.
#      The only null-char found are a succession of 2 '\0', appearing at the
#      end of the char list.

VAR=$1
S=$2
T=`echo $S | sed 's/\.b$/.c/'`

if [ -z "$S" ]; then
	echo "Usage: prepb.sh VARNAME FILE"
	echo "  Example: prepb.sh ""libbc_libmath"" bc/libmath.b"
	exit
fi

echo "/* Created by prepb.sh */" >$T
echo "/* DO NOT UPDATE MANUALLY */" >> $T
echo >> $T
echo "#include <stdlib.h>" >> $T
echo >> $T
echo "char ${VAR}[] = {" >> $T
sed -r ':a; s%(.*)/\*.*\*/%\1%; ta; /\/\*/ !b; N; ba' "$S" | sed 's/^\s*//' | sed '/^$/d' | sed "s/./'&', /g" | sed "s/'\\\\'/'\\\\\\\\'/g" | sed "s/$/'\\\\n', /" >> $T

# See http://flex.sourceforge.net/manual/Multiple-Input-Buffers.html
#   The input buffer (when used in read-only mode) needs have two
#   null characters at the end.
echo "'\\\\0', '\\\\0'" >> $T

echo "};" >> $T
echo >> $T
echo "const size_t ${VAR}_len = sizeof($VAR);" >> $T
echo >> $T

