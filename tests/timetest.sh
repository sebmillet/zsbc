#!/bin/sh
#
# Time the functions.
SUBDIR="bc-tests"
SYSBC=/usr/bin/bc
if [ x$BC = x ] ; then
  BC="../src/zsbc --numlib bc"
fi
for file in $SUBDIR/exp.b $SUBDIR/ln.b $SUBDIR/sine.b $SUBDIR/atan.b $SUBDIR/jn.b $SUBDIR/mul.b $SUBDIR/div.b $SUBDIR/raise.b $SUBDIR/sqrt.b $SUBDIR/fact.b
do
for prog in "$SYSBC" "$BC" $OTHERBC
do
echo Timing $file with $prog
time $prog -l $file | egrep CPU
done
done
