define pow2(param) {
	return 2^param
}

define powmod(myx, myy, mymod)
{
	alpha = myx^myy
	return alpha%mymod
}

define checkreturn() {
	return 1
	return 2
}

define fact(x) {
	if (x > 1)
		return fact(x - 1) * x
	else
		return 1
}

define myfcnt(alpha,beta) {
	alpha *= 2
	beta *=3
	return alpha+beta
}

