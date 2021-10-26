#include "solutions.h"
#include <iostream>
#include <vector>
#include <chrono>
#include "BigInt.h"

//On my machine
//int is 32 bits
//long is 32 bits
//long long is 64 bits



int main() {


	BigInt abcd((unsigned long long)200000000000);
	abcd.print();
	BigInt efgh((unsigned long long)64);
	efgh.print();
	BigInt qqq = abcd * efgh;


	BigInt* q;
	BigInt x((long long) 1);

	/*
	q = &x;
	for (int i = 0; i < 128; i++) {
		BigInt r((unsigned long long)3);
		BigInt a = *q * r;
		q = &a;
		cout << *q << endl;
	}
	*/

	cout << "IT EXECUTED." << endl;
	//cout << std::dec << endl;

	auto startTime = std::chrono::high_resolution_clock::now();
	//cout << pe19() << endl;
	auto stopTime = std::chrono::high_resolution_clock::now();
	cout << (double)(std::chrono::duration_cast<chrono::milliseconds>(stopTime - startTime).count())/1000.0 << " s" << endl;

	

}