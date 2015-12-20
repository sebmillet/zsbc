define rec(a[], doupdate, level) {
	if (doupdate) a[1] = 2
	if (level > 1) {
		return rec(a[], doupdate, level - 1)
	} else {
		return a[0];
	}
}

define void fill(*a[], n) {
	for (i = 0; i < n; ++i) {
		a[i] = (i + 1) ^ 2;
	}
}

define void prep(n) {
	fill(alpha[], n)
}

l = 20
n = 2000000
print "Filling array with ", n, " element(s)\n"
prep(n);
print "Now calling recursive function - READ ONLY\n"
rec(alpha[], 0, l)
print "Now calling recursive function - READ/WRITE\n"
rec(alpha[], 1, l)
print "Done\n"
quit
