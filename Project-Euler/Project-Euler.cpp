#include "solutions.h"
#include <iostream>
#include <vector>
#include <chrono>

//see solutions.cpp for the actual code.
//this file is just used to test solutions


int main() {

	
	auto startTime = std::chrono::high_resolution_clock::now();
	cout << pe6() << endl;
	auto stopTime = std::chrono::high_resolution_clock::now();
	cout << (double)(std::chrono::duration_cast<chrono::milliseconds>(stopTime - startTime).count())/1000.0 << " s" << endl; //print running time

	
}