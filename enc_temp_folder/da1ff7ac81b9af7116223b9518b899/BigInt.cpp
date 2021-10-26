#include "BigInt.h"
#include <vector>

unsigned int findMSB(unsigned long long x) {
	unsigned int i;
	for (i = 0; x; i++) {
		x = x >> 1;
	}
	return i;
}
void BigInt::print() {
	for (int i = length - 1; i >= 0; i--) {
		cout << std::hex << arr[i] << ' ';
	}
	cout << endl;
}
BigInt::BigInt(unsigned int x, unsigned int a) {
	length = (x + 31) / 32;
	MSB = x;
	arr = new unsigned int[length] { 0 };
}

BigInt::BigInt(unsigned long long x) {
	length = 2;
	MSB = findMSB(x);
	arr = new unsigned int[2]{ (unsigned int)x, (unsigned int)(x >> 32)}; //backwards becasue the numbers are stored in little endian
	cout << '(';
	for (int i = 0; i < 2; i++) {
		cout << arr[i] << '\t';
	}
	cout << ')' << endl;
}



BigInt BigInt::operator*(BigInt& b)
{
	BigInt product(MSB + b.MSB, 1);

	for (unsigned int i = 0; i < this->length; i++) {
		for (unsigned int j = 0; j < b.length; j++) {
			unsigned long long subProduct = this->arr[i] * b.arr[j];
			product.add(subProduct, i + j);
		}
	}
	return product;
}
void BigInt::add(unsigned long long n, unsigned int index) {
	if (!arr)
		return;
	unsigned long long* loc = (unsigned long long*)(&arr[index]);
	*loc += n;
	if (*loc < n)
		loc[1] += 1;
	for (int i = 1; loc[i]==0; i++) { //loc[i] is 0 if overflow. need to go
		loc[i + 1]++;
	}
}

BigInt BigInt::operator*(unsigned long long& b)
{

	return *this; // change. only so it compiles
}

char* BigInt::decimal() const {
	const int len = this->MSB / 3; //divided by 3 because the floor(log2(10)) = 3. should provide a close over estimate of the number of digits we need. 
	char* pow2 = new char[len] {0};
	char* decimalNotation = new char[len] { 0 };
	pow2[0] = 1;
	vector<char>* digitsToSum = new vector<char>[len];


	int maxDigitReached = 0;
	int currentBit = 0;
	int currentIntIndex = 0;
	unsigned int currentInt = this->arr[currentIntIndex];
	unsigned int currentMask = 1;
	for (int i = 0; i < this->MSB; i++) {
		for (int d = maxDigitReached; d >= 0; d--) { //double the number in p2. work from most significant down.
			int k = d;
			char times2 = pow2[k] * 2;
			pow2[k] = times2 % 10;
			while (times2 /= 10) {
				k++;
				times2 += pow2[k];
				pow2[k] = times2 % 10;
				if (k > maxDigitReached)
					maxDigitReached = k;
			}
		}
		currentBit++;
		currentMask = currentMask << 1;
		if (currentBit > 32) {
			currentIntIndex++;
			currentInt = this->arr[currentIntIndex++];
			currentMask = 1;
		}
		if (currentMask && currentInt) {
			for (int j = 0; j < maxDigitReached; j++) {
				digitsToSum->push_back(pow2[j]);
			}
		}
	}

	for (int i = 0; i < len; i++) {
		vector<char>::iterator it = digitsToSum[i].begin();
		int sum = 0;
		for (int j = 0; j < digitsToSum[j].size(); j++) {
			sum += digitsToSum[i][j];
		}
		decimalNotation[i] = sum % 10;
		int k = 0;
		while (sum /= 10) {
			k++;
			digitsToSum[i + k].push_back(sum % 10);
		}
	}

	//delete[] pow2;
	//delete[] digitsToSum;
	return decimalNotation;
}

ostream& operator<<(ostream& os, const BigInt& big) {
	char* decimalRepresentation = big.decimal();
	os << decimalRepresentation;
	//delete[] decimalRepresentation;
	return os;
}

BigInt::~BigInt() {
	//if (arr)
		//delete[] arr;
		
}