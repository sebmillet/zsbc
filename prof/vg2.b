/*
   This script will perform some calculations
   and exit.
   Intended to be used along with tools like gprof or valgrind.

   After calculations it simply prints 0 and exits

   It must be run with bc numlib and bc' mathlib => run zsbc as is:
     zsbc -n bc -l vg.b
*/

define z(x, n) {
	auto i, y
	for (i = 0; i < n; ++i) {
		y = a(x)
		y = s(x)
		y = c(x)
		y = l(x)
		y = e(x)
	}
}

scale=70
z(8.12345, 30)
quit

