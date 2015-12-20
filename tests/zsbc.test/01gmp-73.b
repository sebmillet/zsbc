define void f(*r[], p[], q[]) {
	r[0]=1000*p[0]
	r[1]=1000*q[0]+q[1]
}

define void g(*r[], p[]) {
	r[0]=-1
	r[1]=0
	f(r[], r[], p[])
}

g[0]=105
g[1]=107
g(r[], g[])
print "1:", r[0], ";2:", r[1], "\n"

