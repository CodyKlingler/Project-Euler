#pragma once
#include <cmath>
#include <iostream>
#include <vector>

//TODO: convert long long, long, and int to uint64,32,16 etc.

using namespace std;



//sum of multiples of 3 or 5 up to 1000
//computed as sum of multiples of 3 and multiples of 5, minus multiples of 15
//O(1) - (the more obvious method is (O(n))
int pe1();

//sum of even numbers in the fibonacci sequence up to  4 million
//I wouldn't be surprised if there is a more optimal solution using the golden ratio
//O(n)
int pe2();


//find the largest prime factor of 600,851,475,143
//find smallest prime factor, divide n. repeat
// O(n) (roughly)
long long pe3();


//TODO: logic for navigating multiplication table needs fixed (only works by printing answers.)
//O(n**2) - starts with large values.
//maybe could be optimized with weird number theory
long pe4();


//find smallest number that is divisible by all numbers less than 20
//O(n) (actually O(primes less than n))
uint64_t pe5();

//difference of sum of squares and square of sum
//I suspect there is a more efficient solution using binomial theorem.
//O(n)
long pe6();


long pe7();

uint64_t pe8();

uint64_t pe8e();

uint64_t pe9();

uint64_t pe10();

uint64_t pe11();

uint64_t pe12();

uint64_t pe13();

long pe14();

long long pe15();

long pe16();