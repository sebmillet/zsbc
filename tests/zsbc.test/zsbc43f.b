define modify() {
	auto x, hello
	x=2
	hello=x^3
	(z+=x+hello)
	return x-hello
}
define modarray() {
	auto yo[], c, zeta[]
	auto i

	c=11
	alpha[c+1]-=50
	yo[0]=1;yo[1]=1
	for (i=2; i<=9; ++i)
	{
		yo[i]=yo[i-1]+yo[i-2]
		zeta[i*2]=yo[i]*2
		print yo[i], ":", zeta[i*2], ","
	}
}
