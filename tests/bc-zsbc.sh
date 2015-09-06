#!/bin/sh

IDIR=../../../bc-1.06.95/Test
ODIR=tmp
ZSBCEXE=../src/zsbc

mkdir -p $ODIR

for F in $IDIR/*; do
	G=$(basename $F)
	BCOUT=`echo $G | sed s/\.b$/-bc.out/`
	ZSBCOUT=`echo $G | sed s/\.b$/-zsbc.out/`
	echo "$F" -- "$BCOUT -- $ZSBCOUT"

	cat "$F" | bc -l > $ODIR/$BCOUT
	cat "$F" | $ZSBCEXE -numlib bc -l > $ODIR/$ZSBCOUT
done

