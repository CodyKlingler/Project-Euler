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
	cout << pe17() << endl;
	auto stopTime = std::chrono::high_resolution_clock::now();
	cout << (double)(std::chrono::duration_cast<chrono::milliseconds>(stopTime - startTime).count())/1000.0 << " s" << endl;

	auto startTime2 = std::chrono::high_resolution_clock::now();
	cout << pe17_iterative() << endl;
	auto stopTime2 = std::chrono::high_resolution_clock::now();
	cout << (double)(std::chrono::duration_cast<chrono::milliseconds>(stopTime2 - startTime2).count()) / 1000.0 << " s" << endl;


}