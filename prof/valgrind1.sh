#!/bin/sh

# valgrind1.sh

valgrind --leak-check=full --show-leak-kinds=all ../src/zsbc vg1.b 2> valgrind1.txt

echo See file valgrind1.txt for valgrind analyzis results
