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

p(4096, 200000)
quit
