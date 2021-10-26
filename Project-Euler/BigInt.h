#pragma once

#include <iostream>

using namespace std;
class BigInt
{
public:

	friend ostream& operator<<(ostream& os, const BigInt& big);
	BigInt operator*(BigInt& b);
	BigInt operator*(unsigned long long& b);
	void add(unsigned long long n, unsigned int digit);
	BigInt(unsigned int x, unsigned int a);
	BigInt(unsigned long long x);
	void print();
	~BigInt();
	char* decimal() const;
protected:
	unsigned int length = 0;
	unsigned int* arr = 0;
	unsigned int MSB = 0;

};




