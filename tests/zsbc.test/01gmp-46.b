define a() {
	break;
	return 0
}

define b() {
	for (i=0; i<10; ++i) {
		break;
	}
}

define beta() {
	return 1-a1()
}

define void allo() {
	return 1
}

define ya() {
	return
}

define xy() {
	a(1)
	a()
}

define fact(x) {
	if (x <= 1) return 1 else return x - 1
}

define void noval() {
	return;
}

define ll() {
	a()
	noval()
	1+a()
	1+noval()
}

define fbyval(x) {
}

define caller1() {
	1+fbyval(a)^2
	1+fbyval(1+a)^2
	1+fbyval(a[])^2
}

define fbyref(*x) {
}

define caller2() {
	1+fbyref(a)^2
	1+fbyref(1+a)^2
	1+fbyref(a[])^2
}

define farraybyval(x[]) {
}

define caller3() {
	1+farraybyval(a)^2
	1+farraybyval(1+a)^2
	1+farraybyval(a[])^2
}

define farraybyref(*x[]) {
}

define caller4() {
	1+farraybyref(a)^2
	1+farraybyref(1+a)^2
	1+farraybyref(a[])^2
}

define novalinif() {
	if (noval()) 0
}

define novalinfor() {
	for (; noval();) 0
	for (noval(); noval(); noval()) 0
}

define novalinwhile() {
	while (noval()) {
	}
}

define novalinreturn() {
	return noval()
}

