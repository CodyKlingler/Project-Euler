#include "solutions.h"
#include <iostream>
#include <vector>
#include <chrono>





int main() {



	
	auto startTimeP12alt = std::chrono::high_resolution_clock::now();
	cout << pe12() << endl;
	auto stopTimeP12alt = std::chrono::high_resolution_clock::now();
	cout << (double)(std::chrono::duration_cast<chrono::milliseconds>(stopTimeP12alt - startTimeP12alt).count())/1000.0 << " s" << endl;
	
	/*
	cout << pe12() << endl;
	auto stopTimeP12 = chrono::high_resolution_clock::now();
	cout << (double)(std::chrono::duration_cast<chrono::milliseconds>(stopTimeP12 -stopTimeP12alt).count()) / 1000.0 << " s" << endl;
	*/
}