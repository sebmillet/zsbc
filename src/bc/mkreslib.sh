#!/bin/sh

# Script to be used for zsbc compilation

VAR="libbc_libmath"
S=$1
T=`echo $S | sed 's/\.b$/.c/'`

if [ -z "$S" ]; then
	echo "Usage: mkreslib.sh FILE"
	exit
fi

echo "/* Created by mkreslib.sh */" >$T
echo "/* DO NOT UPDATE MANUALLY */" >> $T
echo >> $T
echo "#include <stdlib.h>" >> $T
echo >> $T
echo "const char ${VAR}[] = {" >> $T
sed -r ':a; s%(.*)/\*.*\*/%\1%; ta; /\/\*/ !b; N; ba' "$S" | sed 's/^\s*//' | sed '/^$/d' | sed "s/./'&', /g" | sed "s/'\\\\'/'\\\\\\\\'/g" | sed "s/$/'\\\\n', /" >> $T
echo "};" >> $T
echo >> $T
echo "const size_t ${VAR}_len = sizeof($VAR);" >> $T
echo >> $T

