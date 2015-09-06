#!/bin/sh

IDIR="bc-tests"
ODIR=tmpout
ZSBCEXE=../src/zsbc

mkdir -p $ODIR

ok=0
ko=0
for F in $IDIR/*.b; do
	G=$(basename $F)
	BCOUT=`echo $G | sed s/\.b$/-bc.out/`
	ZSBCOUT=`echo $G | sed s/\.b$/-zsbc.out/`

	cat "$F" | bc -l > $ODIR/$BCOUT
	cat "$F" | $ZSBCEXE -numlib bc -l > $ODIR/$ZSBCOUT

	PRINTBCHASH=`sha1sum $ODIR/$BCOUT`
	BCHASH=`echo $PRINTBCHASH | sed 's/ .*$//'`
	PRINTZSBCHASH=`sha1sum $ODIR/$ZSBCOUT`
	ZSBCHASH=`echo $PRINTZSBCHASH | sed 's/ .*$//'`
	if [ $BCHASH = $ZSBCHASH ]; then
		PREF="OK  "
		ok=$(($ok+1))
	else
		PREF="*KO*"
		ko=$(($ko+1))
	fi
	echo "$PREF\tbc\t$PRINTBCHASH"
	echo "$PREF\tzsbc\t$PRINTZSBCHASH"
	echo
done

echo "$ok tests OK"
echo "$ko tests *KO*"

