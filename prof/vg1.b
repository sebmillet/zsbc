/*
   This script will perform some calculations
   and exit.
   Intended to be used along with tools like gprof or valgrind.

   After calculations it prints a big number and exists.
*/

define p(n, l) {
	auto i, r
	for (i = 0; i < n; ++i) {
		r += 2^i;
	}
	for (i = 0; i < l; ++i) {
		.=r++;
	}
	return r;
}

p(508, 500)
p(509, 500)
p(510, 500)
p(511, 500)
p(512, 500)
p(513, 500)
p(514, 500)
p(515, 500)
quit
