
//helpers for pe1
int Sum1ToN(int n) {
	return (n * (n + 1)) / 2;
}
int SumMultiplesOfNtoK(int n, int k) {
	return n * Sum1ToN(k / n);
}


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