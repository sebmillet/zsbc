define ok1(a, b) {
	return 1
}

define ok2(a, a[]) {
	return 1
}

define ok3(*a, a[]) {
	return 1
}

define ok4(a, *a[]) {
	return 1
}

define ok5(*a, *a[]) {
	return 1
}

define ok6(a[], a) {
	return 1
}

define ok7(*a[], a) {
	return 1
}

define ok8(a[], *a) {
	return 1
}

define ok9(*a[], *a) {
	return 1
}

define ko1(a, a) {
	return 1
}

define ko2(a, *a) {
	return 1
}

define ko3(*a, a) {
	return 1
}

define ko4(*a, *a) {
	return 1
}

define ko5(a[], a[]) {
	return 1
}

define ko6(*a[], a[]) {
	return 1
}

define ko7(a[], *a[]) {
	return 1
}

define ko8(*a[], *a[]) {
	return 1
}

define autoko1() {
	auto a, a
	return 1
}

define autoko2() {
	auto a[], a[]
	return 1
}

define autoko3(a) {
	auto a
	return 1
}

define autoko4(a[]) {
	auto a[]
	return 1
}

define autoko5(*a) {
	auto a
	return 1
}

define autoko6(*a[]) {
	auto a[]
	return 1
}

define autook1(a) {
	auto a[]
	return 1
}

define autook2(a[]) {
	auto a
	return 1
}

define autook3(*a) {
	auto a[]
	return 1
}

define autook4(*a[]) {
	auto a
	return 1
}

