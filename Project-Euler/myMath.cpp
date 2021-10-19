

long long factorial(int  n) {
	long long fac = 1;
	for (int i = 2; i <= n; i++) {
		fac *= i;
	}
	return fac;
}

long long nchoosek(int n, int k) {
	long long fac = 1;
	for (int i = k + 1; i <= n; i++) {
		fac *= i;
	}
	fac /= factorial(n - k);
	return fac;
}