define void f(*r[], p[], q[]) {
	r[0] = 2 * p[0] + q[0]
	r[1] = 2 * p[1] + q[1]
}

define void g1(*r[], *s[]) {
	r[0] = 2 * r[0] + s[0] + 1
	r[1] = 1000 * r[1] + s[1] + 2
	s[0] = 1234
}

define void g2(*r[], *s[]) {
	s[0] = 1234
	r[0] = 2 * r[0] + s[0] + 1
	r[1] = 2 * r[1] + s[1] + 2
}

p[0] = 500
p[1] = 501

f(r[], p[], p[])
print "ROUND1-1:", p[0], ";", p[1], "\n"
print "ROUND1-2:", r[0], ";", r[1], "\n"
f(r[], p[], p[])
print "ROUND2-1:", p[0], ";", p[1], "\n"
print "ROUND2-2:", r[0], ";", r[1], "\n"
g1(p[],p[])
print "ROUND3-1:", p[0], ";", p[1], "\n"
print "ROUND3-2:", r[0], ";", r[1], "\n"
g2(p[],p[])
print "ROUND4-1:", p[0], ";", p[1], "\n"
print "ROUND4-2:", r[0], ";", r[1], "\n"
