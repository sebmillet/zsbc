#!/bin/sh

# valgrind2.sh

valgrind --leak-check=full --show-leak-kinds=all ../src/zsbc -n bc -l vg2.b 2> valgrind2.txt

echo See file valgrind2.txt for valgrind analyzis results
