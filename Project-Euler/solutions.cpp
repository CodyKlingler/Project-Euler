#include <cmath>
#include <iostream>
#include <vector>

//TODO: convert long long, long, and int to uint64,32,16 etc.


using namespace std;

//helpers for pe1
int SumToN(int n) {
    return (n * (n + 1)) / 2;
}
int SumNToK(int n, int k) {
    return n * SumToN(k / n);
}

//sum of multiples of 3 or 5 up to 1000
//computed as sum of multiples of 3 and multiples of 5, minus multiples of 15
//O(1) - (the more obvious method is (O(n))
int pe1() {
    return SumNToK(3, 999) + SumNToK(5, 999) - SumNToK(15, 999);
}

//sum of even numbers in the fibonacci sequence up to  4 million
//I wouldn't be surprised if there is a more optimal solution using the golden ratio
//O(n)
int pe2() {
    const int UPPER_BOUND = 40000000;
    int b = 0;
    int a = 1;
    int nextTerm = 1;
    int evenSum = 0;
    while (nextTerm < UPPER_BOUND) {
        if (!(nextTerm % 2)) {
            evenSum += nextTerm;
        }
        b = a;
        a = nextTerm;
        nextTerm = a + b;
    }
    return evenSum;
}


//find the largest prime factor of 600,851,475,143
//find smallest prime factor, divide n. repeat
// O(n) (roughly)
long long pe3() {
    long long n = 600851475143L;

    long long i = 5;
    long long largestPrimeFactor = 0;
    while (i < n) {
        if (!(n % i)) {
            if (i > largestPrimeFactor) {
                largestPrimeFactor = i;
            }
            n /= i;
            i = 2; // restart linear scan from n=2;
        }
        i++;
    }
    if (n > largestPrimeFactor)
        largestPrimeFactor = n;
    return largestPrimeFactor;
}


// helper to p4
bool isPalindrome(long n) {
    int len = (int)(log10(n) + .9999999);
    int* nums = new int[len] { -1 };

    for (int i = len - 1; i >= 0; i--) {
        nums[i] = n % 10;
        n /= 10;
    }

    for (int i = 0; i <= len - 1 - i; i++) {
        if (nums[i] != nums[len - 1 - i])
            return false;
    }
    return true;
}

//TODO: logic for navigating multiplication table needs fixed (only works by printing answers.)
//O(n**2) - starts with large values.
//maybe could be optimized with weird number theory
void pe4() {
    for (long i = 999; i > 0; i--) {
        long tempi = i;
        for (long j = 999; j >= tempi && tempi <= 999; j--, tempi++) {
            if (isPalindrome(i * j)) {
                //return std::cout << i*j;
            }

        }
    }
}


//find smallest number that is divisible by all numbers less than 20
//O(n) (actually O(primes less than n))
long long pe5() {
    int c[] = { 2, 3, 5, 7, 11, 13, 17, 19 }; //primes less than 20

    long long prod = 1;
    for (int i : c) {
        int n = (int)((log10(20) / log10(i)) + .0001); //basically log(20) (base prime, i)
        prod *= pow(i, n);
    }
    return prod;
}

//difference of sum of squares and square of sum
//I suspect there is a more efficient solution using binomial theorem.
//O(n)
long pe6() {
    using namespace std;
    long sumOfSq = 0;
    long SqOfSum = 0;
    for (int i = 1; i <= 100; i++) {
        SqOfSum += i;
        sumOfSq += i * i;
    }
    SqOfSum *= SqOfSum;
    return SqOfSum - sumOfSq;
}


long pe7() {
    const int findPrime = 10001;
    const int n = 600000;
    bool p[n] = { 0 };
    int primesFound = 1;
    vector<int> primes;
    primes.push_back(2);
    for (int x = 0; x < primesFound; x++) {
        int i = primes[x];
        int k;
        for (int k = i; k < n; k += i) {
            p[k] = 1;
        }

        for (int j = i+1; j < n; j++) {
            if (!p[j]) {
                primes.push_back(j);
                primesFound++;
                cout << primesFound << " : " << j << endl;
                if (primesFound == findPrime) {
                    return j;
                }
            }
        }

    }
    return 0;
}

