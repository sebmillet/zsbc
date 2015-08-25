define fc(*a) {
	a += 1
	return -1
}
define fz(*hal) {
	hal *= 2
	return 1 - hal
}
define void ccf(*foo) {
	foo += 1
	return
}
define f2(alpha[]) {
	alpha[1] = 10
	alpha[0]
	alpha[1]
	alpha[2]
}

define fr(*beta[]) {
	beta[1] = 20
	beta[0]
	beta[1]
	beta[2]
	return 9
}

define factbyref(*x) {
	if (x > 1) {
		t=x
		return t*factbyref(--x)
	} else {
		return x
	}
}

define g(*a) {
	a
}
