	/* Calculate the invert of a mod n */
define _invmod(a, n) {
	auto aa, bb, r, t, anc_t, nou_t
	aa = n
	bb = a
	r = 1
	t = 1
	anc_t = 0
	while (1) {
		q = aa / bb
		anc_r = r
		r = aa - bb * q

		nou_t = anc_t - q * t
		if (nou_t >= 0) nou_t %= n
		if (nou_t < 0) nou_t = n - (-nou_t % n)
		anc_t = t
		t = nou_t

		aa = bb
		bb = r
		if (r <= 1) break;
	}

	if (r != 1) {
			/*
			   No invert can be returned => error
			   Alternate solution: return -1

			   I find triggering an error best: the calculation stops
			   immediately instead of continuing with meaningless values
			*/
		return 1 % 0
	} else {
		return t
	}
}

	/* Calculate 'a^e mod n' */
define _powmod(a, e, m) {
	auto factor, r
	r = 1
	factor = a
	while (e > 0) {
		if (e % 2) r = (r * factor) % m
		factor = (factor * factor) % m
		e /= 2
	}
	return r
}

