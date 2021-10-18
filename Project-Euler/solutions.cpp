#include <cmath>
#include <iostream>
#include <queue>
#include <stack>
#include "myMath.h"

//TODO: convert long long, long, and int to uint64,32,16 etc.


using namespace std;

//helpers for pe1
int SumToN(int n) {
    return (n * (n + 1)) / 2;
}
int SumMultiplesOfNtoK(int n, int k) {
    return n * SumToN(k / n);
}

//finds sum of multiples of 3 or 5 up to 1000
//computed as sum of multiples of 3 and multiples of 5, minus multiples of 15
//Obvious Solution: O(n)
//My Solution: O(1)
int pe1() {
    return SumMultiplesOfNtoK(3, 999) + SumMultiplesOfNtoK(5, 999) - SumMultiplesOfNtoK(15, 999);
}

//finds sum of even numbers in the fibonacci sequence up to  4 million
//I wouldn't be surprised if there is a more efficient solution using the golden ratio
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


//finds the largest prime factor of 600,851,475,143
//find smallest prime factor, divide n. repeat
//O(n)
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

//maybe could be optimized with weird number theory
//O(n**2) - starts with largest values on multiplication table (from perfect squares to the edges)
long pe4() {
    for (long i = 999; i > 0; i--) {
        long tempi = i;
        stack<long> s;
        for (long j = 999; j >= tempi && tempi <= 999; j--, tempi++) {
            s.push(i * j);
        }
        while (s.size()) {
            if (isPalindrome(s.top())) {
                return s.top();
            }
            s.pop();
        }
    }
}


//find smallest number that is divisible by all numbers less than 20
//O(~n) (actually O(primes less than n))
uint64_t pe5() {
    int c[] = { 2, 3, 5, 7, 11, 13, 17, 19 }; //primes less than 20

    uint64_t prod = 1;
    for (int i : c) {
        int n = (int)((log10(20) / log10(i)) + .0001); //basically log(20) (base prime)
        prod *= uint64_t(pow(i, n)+.5);
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
    queue<int> primes;
    primes.push(2);
    while(primes.size()) {
        int currentPrime = primes.front();
        primes.pop();
        int k;
        for (int k = currentPrime; k < n; k += currentPrime) {
            p[k] = 1;
        }

        for (int j = currentPrime+1; j < n; j++) {
            if (!p[j]) {
                primes.push(j);
                primesFound++;
                if (primesFound == findPrime) {
                    return j;
                }
                break;
            }
        }

    }
    return 0;
}


//Obvious but less efficient solution
//O(nm), n=windowSize, m = numLen
uint64_t pe8() {
    const char num[] = "316717653133062491922511967442657474235534919493496983520312774506326239578318016984801869478851843858615607891129494954595017379583319528532088055111254069874715852386305071569329096329522744304355766896648950445244523161731856403098711121722383113622298934233803081353362766142828064444866452387493035890729629049156044077239071381051585930796086670172427121883998797908792274921901699720888093776657273330010533678812202354218097512545405947522435258490771167055601360483958644670632441572215539753697817977846174064955149290862569321978468622482839722413756570560574902614079729686524145351004748216637048440319989000889524345065854122758866688116427171479924442928230863465674813919123162824586178664583591245665294765456828489128831426076900422421902267105562632111110937054421750694165896040807198403850962455444362981230987879927244284909188845801561660979191338754992005240636899125607176060588611646710940507754100225698315520005593572972571636269561882670428252483600823257530420752963450";
    const int numLen = 1000;
    const int windowSize = 13;

    uint64_t currentProduct;
    uint64_t max = 0;
    for (int i = 0; i < numLen-windowSize; i++) {
        currentProduct = 1;
        for (int j = 0; j < windowSize; j++) {
            currentProduct *= num[i + j] - '0';
        }
        if (currentProduct > max)
            max = currentProduct;
    }
    return max;
}

//TODO: debug
//opimized by making this a true sliding window. special handling of zero values to prevent div/0
//Obvious solution is O(n*m), n=windowSize, m = numLen
//This is O(m)
uint64_t pe8e() {
    const char num[] = "316717653133062491922511967442657474235534919493496983520312774506326239578318016984801869478851843858615607891129494954595017379583319528532088055111254069874715852386305071569329096329522744304355766896648950445244523161731856403098711121722383113622298934233803081353362766142828064444866452387493035890729629049156044077239071381051585930796086670172427121883998797908792274921901699720888093776657273330010533678812202354218097512545405947522435258490771167055601360483958644670632441572215539753697817977846174064955149290862569321978468622482839722413756570560574902614079729686524145351004748216637048440319989000889524345065854122758866688116427171479924442928230863465674813919123162824586178664583591245665294765456828489128831426076900422421902267105562632111110937054421750694165896040807198403850962455444362981230987879927244284909188845801561660979191338754992005240636899125607176060588611646710940507754100225698315520005593572972571636269561882670428252483600823257530420752963450";
    const int numLen = 1000;
    const int windowSize = 13;


    uint64_t currentProduct = 1;
    int zeroCount = 0;

    for (int i = 0; i < windowSize; i++) {
        int nextInt = num[i] - '0';
        if (nextInt == 0) {
            nextInt = (zeroCount==0) ? -1 : 1; //if we havent encountered a zero, make the sum negative.
            zeroCount++;
        }
        currentProduct *= nextInt;
    }

    uint64_t max = currentProduct;
    for (int i = windowSize; i < numLen; i++) {
        int nextInt = num[i]-'0';
        int prevInt = num[i - windowSize] - '0';

        if (prevInt == 0) {
            zeroCount--;
            prevInt = (zeroCount==0) ? -1 : 1;
        }

        if (nextInt == 0) {
            nextInt = (zeroCount==0) ? -1 : 1; //if we havent encountered a zero, make the sum negative.
            zeroCount++;
        }

        currentProduct /= prevInt;
        currentProduct *= nextInt;
        if (currentProduct > max)
            max = currentProduct;
    }

    return max;
}



//obvious solution is to check every combination of a and b in a**2 + b**2 = c**2
//obvious is O(n**2), n = perimeter (1000)
//my solution is O(n). if A is given, you can derive a formula to solve for the exact value of B.  
//my solution also doesn't use square roots or floats, which would expensive and approximate.
//I think that you can solve this even faster though. the triple that is found is an integer factor of the triple 8, 15, 17. 1000 % (8*15*17) = 0. 
uint64_t pe9() {
    //(1000-(a+b))^2 = a^2 + b^2 = c^2
    const int perimeter = 1000;
    for (int a = 1; a < perimeter-2; a++) {
        uint64_t numerator = perimeter * (perimeter - 2 * a);
        uint64_t denominator = 2 * (perimeter - a);
        int b = numerator / denominator;
        if (b && numerator % denominator == 0) {
            int c = perimeter - (a + b);
            cout << a << " " << b << " " << c << endl;
            return a * b * c;
        }
    }
    cout << "bb";
    return -1;
}

//using my sieve from problem 7,
uint64_t pe10() {
    const uint64_t n = 2000000;
    bool* p = new bool[n] {0};

    uint64_t sum = 0;

    queue<int> primes;
    primes.push(2);

    while (primes.size()) {
        int currentPrime = primes.front();
        //cout << currentPrime << endl;
        sum += currentPrime;
        primes.pop();

        int k;
        for (int k = currentPrime; k < n; k += currentPrime) {
            p[k] = 1;
        }

        for (int j = currentPrime + 1; j < n; j++) {
            if (!p[j]) {
                primes.push(j);
                break;
            }
        }

    }
    return sum;
}


uint64_t pe11() {
    const int h = 20;
    const int w = 20;
    const int windowLen = 4;
uint8_t arr[h][w] = {
    {8, 2, 22, 97, 38, 15, 0, 40, 0, 75, 4, 5, 7, 78, 52, 12, 50, 77, 91, 8},
    {49, 49, 99, 40, 17, 81, 18, 57, 60, 87, 17, 40, 98, 43, 69, 48, 4, 56, 62, 0},
    {81, 49, 31, 73, 55, 79, 14, 29, 93, 71, 40, 67, 53, 88, 30, 3, 49, 13, 36, 65},
    {52, 70, 95, 23, 4, 60, 11, 42, 69, 24, 68, 56, 1, 32, 56, 71, 37, 2, 36, 91},
    {22, 31, 16, 71, 51, 67, 63, 89, 41, 92, 36, 54, 22, 40, 40, 28, 66, 33, 13, 80},
    {24, 47, 32, 60, 99, 3, 45, 2, 44, 75, 33, 53, 78, 36, 84, 20, 35, 17, 12, 50},
    {32, 98, 81, 28, 64, 23, 67, 10, 26, 38, 40, 67, 59, 54, 70, 66, 18, 38, 64, 70},
    {67, 26, 20, 68, 2, 62, 12, 20, 95, 63, 94, 39, 63, 8, 40, 91, 66, 49, 94, 21},
    {24, 55, 58, 5, 66, 73, 99, 26, 97, 17, 78, 78, 96, 83, 14, 88, 34, 89, 63, 72},
    {21, 36, 23, 9, 75, 0, 76, 44, 20, 45, 35, 14, 0, 61, 33, 97, 34, 31, 33, 95},
    {78, 17, 53, 28, 22, 75, 31, 67, 15, 94, 3, 80, 4, 62, 16, 14, 9, 53, 56, 92},
    {16, 39, 5, 42, 96, 35, 31, 47, 55, 58, 88, 24, 0, 17, 54, 24, 36, 29, 85, 57},
    {86, 56, 0, 48, 35, 71, 89, 7, 5, 44, 44, 37, 44, 60, 21, 58, 51, 54, 17, 58},
    {19, 80, 81, 68, 5, 94, 47, 69, 28, 73, 92, 13, 86, 52, 17, 77, 4, 89, 55, 40},
    {4, 52, 8, 83, 97, 35, 99, 16, 7, 97, 57, 32, 16, 26, 26, 79, 33, 27, 98, 66},
    {88, 36, 68, 87, 57, 62, 20, 72, 3, 46, 33, 67, 46, 55, 12, 32, 63, 93, 53, 69},
    {4, 42, 16, 73, 38, 25, 39, 11, 24, 94, 72, 18, 8, 46, 29, 32, 40, 62, 76, 36},
    {20, 69, 36, 41, 72, 30, 23, 88, 34, 62, 99, 69, 82, 67, 59, 85, 74, 4, 36, 16},
    {20, 73, 35, 29, 78, 31, 90, 1, 74, 31, 49, 71, 48, 86, 81, 16, 23, 57, 5, 54},
    {1, 70, 54, 71, 83, 51, 54, 69, 16, 92, 33, 48, 61, 43, 52, 1, 89, 19, 67, 48}
};

uint64_t max = 0;
uint64_t currentProduct = 1;

//up-down
for (int i = 0; i < w; i++) {
    for (int j = 0; j <= h - windowLen; j++) {
        uint64_t currentProduct = 1;
        for (int k = 0; k < windowLen; k++) {
            currentProduct *= arr[j + k][i];
        }
        if (currentProduct > max)
            max = currentProduct;
    }
}

//left-right
for (int i = 0; i <= w - windowLen; i++) {
    for (int j = 0; j < h; j++) {
        uint64_t currentProduct = 1;
        for (int k = 0; k < windowLen; k++) {
            currentProduct *= arr[j][i + k];
        }
        if (currentProduct > max)
            max = currentProduct;
    }
}
//diagonal, negative slope
for (int i = 0; i < w - windowLen + 1; i++) {
    for (int j = 0; j < h - windowLen + 1; j++) {
        uint64_t currentProduct = 1;
        for (int k = 0; k < windowLen; k++) {
            uint8_t element = arr[j + k][i + k];
            currentProduct *= element;
        }
        if (currentProduct > max)
            max = currentProduct;
    }
}

//diagonal, positive slope
for (int i = 0; i <= w - windowLen; i++) {
    for (int j = h - 1; j >= windowLen - 1; j--) {
        uint64_t currentProduct = 1;
        for (int k = 0; k < windowLen; k++) {
            uint8_t element = arr[j - k][i + k];
            currentProduct *= element;
        }
        if (currentProduct > max)
            max = currentProduct;
    }
}
return max;
}

//Problem: find the first triangle number with greater than 500 factors.
//continually go through all primes less than current triangle number. divide it by any prime factors. 
//keep track of how many unique, and non unique prime factors. Do math to find out the amount of unique combinations of factors.
//very fast compared to bruteforce.
//O(?) - the time complexity is rather complicated. If I had to guess i would say n^2 or n^3.
uint64_t pe12() {

    const uint64_t n = 16000; //generate all primes less than n. increase n if you also increase the number of factors to beyond 500.
    bool* p = new bool[n] {0};

    vector<long> primes;
    primes.push_back(2);
    int primesFound = 1;

    //generate primes via sieve.
    for (int i = 0; i < n; i++) {
        int currentPrime = primes[primesFound - 1];
        for (int k = currentPrime; k < n; k += currentPrime) {
            p[k] = 1;
        }
        for (int j = currentPrime + 1; j < n; j++) {
            if (!p[j]) {
                primes.push_back(j);
                primesFound++;
                break;
            }
        }
    }
    //put the primes into an array for quick access.
    long* primeArr = new long[primes.size()];
    std::vector<long>::iterator it = primes.begin();
    for (int i = 0; it != primes.end(); it++,i++) {
        primeArr[i] = *it;
    }


    long long triangleNum = 0;
    int pCount;
    const int divisors = 500;
    short pFCount[divisors] = {0}; //arrays used to track number of each prime factor
    short uPFactors[divisors] = {0};

    for (int i = 1; ; i++) {
        triangleNum += i;

        long long currentTriangleNum = triangleNum;
        pCount = 0;

        // continually go through all primes less than current triangle number. divide it by any prime factors. 
        //keep track of how many unique, and non unique prime factors. Do math to find out the amount of unique combinations of factors.
        for (int j = 0; primeArr[j] <= currentTriangleNum && j < primes.size(); j++) { 
            if (currentTriangleNum % primeArr[j] == 0) {
                uPFactors[pCount] = primeArr[j];
                pFCount[pCount] = 0;
                while (currentTriangleNum % primeArr[j] == 0) {
                    currentTriangleNum /= primeArr[j];
                    pFCount[pCount]++;
                }
                pCount++;
            }
        }
        if (currentTriangleNum > primeArr[primes.size() - 1]) {
            return -2; //didnt generate enough primes. increase 'n'
        }

        int factorCount = pow(2,pCount); //Use the binomial theorem to find combinations of unique primes.
        for (int j = 0; j < pCount; j++) {
            factorCount *= (1 + .5 * (pFCount[j] - 1)); //math that I worked out on paper. accounts for non-unique primes.
        }
        if (factorCount > 500) {
            return triangleNum;
        }
    }
    return -1;
}