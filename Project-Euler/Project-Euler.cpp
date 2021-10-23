#include "solutions.h"
#include <iostream>
#include <vector>
#include <chrono>


//On my machine
//int is 32 bits
//long is 32 bits
//long long is 64 bits


int main() {

	
	auto startTime = std::chrono::high_resolution_clock::now();
	cout << pe16() << endl;
	auto stopTime = std::chrono::high_resolution_clock::now();
	cout << (double)(std::chrono::duration_cast<chrono::milliseconds>(stopTime - startTime).count())/1000.0 << " s" << endl;

}