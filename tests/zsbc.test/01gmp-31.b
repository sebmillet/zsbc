define void donothing(a[]) {
	print "donothing start\n"
}

define void doread(a[]) {
	print "doread start\n"
	a[0]
}

define void dowrite(a[]) {
	print "dowrite start\n"
	a[0] = 10
	a[0]
}

alpha[0]=5

donothing(alpha[])
print "donothing end\n"

doread(alpha[])
print "doread end\n"

dowrite(alpha[])
print "dowrite end\n"

