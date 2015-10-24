#!/bin/sh

# Generate bc library tests from gmp

echo "This will create 02-bc*.exp"
echo "Continue? (y/n)"

read A
if [ "$A" != "y" -a "$A" != "Y" ]; then
	echo "Aborted."
	exit
fi

#for i in "01" "02" "03" "04" "05" "10" "20" "21" "30" "40" "41" "42" "43" "45"; do
#for i in "46"; do
for i in "RIENDUTOUT"; do
	II=zsbc.test/01gmp-$i.exp
	O=zsbc.test/02bc-$i.exp

	echo "$II => $O"

	FII=$(basename $II)
	BFII=$FII
	FO=$(basename $O)
	FII=`echo $FII | sed 's/\./\\\\./g'`

	echo "## Generated by tests/gen.sh" > $O
	echo "##   $BFII -> $FO" >> $O
	echo "##   Date: "`LANG=\"C\" date` >> $O
	echo "##" >> $O
	echo "## git information: $BFII version used to generate $FO:" >> $O
	git log -n 1 $II | head -n 3 | sed 's/^/##   /' >> $O
	echo >> $O
	echo "## *** DO NOT UPDATE MANUALLY ***" >> $O
	echo >> $O
	cat $II >> $O
	sed -i "s/\/$FII/\/$FO/" $O
	sed -i 's/^\(send_user.*\)GMP - /\1BC - /' $O
	sed -i 's/^spawn "\$ZSBC" --SCM/& --numlib bc/' $O
	sed -i 's/set test \"Get GMP Library version\"/set test \"Get BC library version\"/' $O
	sed -i 's/-nocase \"gmp library\"/-nocase \"bc library\"/' $O
	sed -i 's/fail \"Could not get GMP library version\"/fail \"Could not get BC library version\"/' $O
	sed -i '/==DELETE-BEGIN-TAG==/,/==DELETE-END-TAG==/d' $O
done

