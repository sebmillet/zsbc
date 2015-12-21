/*
	argarray.b

	Sébastien Millet, December 2015

	Shows that bc can be subject to a clash between variables in function
	calls. Seen on my bc under Ubuntu 15.10. bc version is 1.06.95.

	f shows the issue with by-ref argument in the first position.
	g shows the issue with by-ref argument in the second position.
	For the clash to occur:

		- The argument name needs be identical between function definition and
		  function call.

		- In the function call, the argumant must be specified twice, once as
		  the by-ref argument, once as the by-val argument.
*/

define void f(*r[], a[]) {
	r[0] = 10 * a[0] + 1
}

define void g(a[], *r[]) {
	r[0] = 10 * a[0] + 1
}

p[0] = 5
f(p[], p[])
print "f:p[0]=", p[0], "\t(should be 51 => OK)\n"

a[0] = 5
f(r[], a[])
print "f:r[0]=", r[0], "\t(should be 51 => OK)\n"

a[0] = 5
f(a[], a[])
print "f:a[0]=", a[0], "\t(should be 51 but is 5 on my bc => KO)\n"

p[0] = 5
g(p[], p[])
print "g:p[0]=", p[0], "\t(should be 51 => OK)\n"

a[0] = 5
f(a[], r[])
print "g:r[0]=", r[0], "\t(should be 51 => OK)\n"

a[0] = 5
f(a[], a[])
print "g:a[0]=", a[0], "\t(should be 51 but is 5 on my bc => KO)\n"

quit

