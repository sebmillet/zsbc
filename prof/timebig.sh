#!/bin/sh

# Check zsbc run time with plenty of variables defined and used.
# In parallel, will also check whether zsbc can cope with
# blocks of instructions that contain millions of lines.
#
# The goal is to verify there is no O(n^2) execution time
# left behind.

# Sébastien Millet, October 2015

#
#   * WARNING *
#
#   This script makes sense in a very specific environment.
#   I tuned it with my PC so that measures are
#   "not too slow, not too fast" => the 'time' instruction
#   shows interesting results.
#   On my PC it is 8s, 18s and 35 for 2, 4 and 8 million,
#   respectively.
#   Thus I know the execution time is ~O(n).
#   I write "~" because the REAL order must be O(n).ln(n)
#   or the like.
#

ZSBC=../src/zsbc

echo "Generating .b files..."
./lotofvar.pl 40000 > big1M.b
./lotofvar.pl 80000 > big2M.b
./lotofvar.pl 160000 > big4M.b

echo
echo "Measuring run time with 1 million variables"
time $ZSBC big1M.b > /dev/null

echo
echo "Measuring run time with 2 million variables"
time $ZSBC big2M.b > /dev/null

echo
echo "Measuring run time with 4 million variables"
time $ZSBC big4M.b > /dev/null

echo
echo "Done. Think of cleaning big*M.b files"

