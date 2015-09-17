define void tarray() {
	for (i = 1000; i <= 2000; ++i) {
		zeta1[i] = i^2+1
	}
	for (i = 0; i < 1000; ++i) {
		zeta1[i] = i^2+1
	}
}

define void tarrayref(*zeta1[]) {
	for (i = 1000; i <= 2000; ++i) {
		zeta1[i] = i^2-1
	}
	for (i = 0; i < 1000; ++i) {
		zeta1[i] = i^2-1
	}
}

define void tarray2() {
	for (i = 0; i <= 2000; i+=2) {
		zeta2[i] = i^2+2
	}
	for (i = 1; i <= 2000; i+=2) {
		zeta2[i] = i^2+2
	}
}

define void tarray2ref(*zeta2[]) {
	for (i = 0; i <= 2000; i+=2) {
		zeta2[i] = i^2-2
	}
	for (i = 1; i <= 2000; i+=2) {
		zeta2[i] = i^2-2
	}
}

define void verif(ar[], shift, id) {
	for (i = 0; i <= 2000; ++i) {
		if (ar[i] != i^2 + shift) {
			print "ERROR on indice ", i, "\n"
			return
		}
	}
	print "VERIFOK:", id, "\n"
}

define void verif2(*ar[], shift, id) {
	for (i = 0; i <= 2000; ++i) {
		if (ar[i] != i^2 + shift) {
			print "ERROR on indice ", i, "\n"
			return
		}
	}
	print "VERIFBYREFOK:", id, "\n"
}

define void e0(a[]) {
		a[0]
}

