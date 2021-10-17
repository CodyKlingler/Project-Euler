#include <cmath>
#include <iostream>
#include <queue>
#include <stack>

//TODO: convert long long, long, and int to uint64,32,16 etc.


using namespace std;

//helpers for pe1
int SumToN(int n) {
    return (n * (n + 1)) / 2;
}
int SumNToK(int n, int k) {
    return n * SumToN(k / n);
}

//finds sum of multiples of 3 or 5 up to 1000
//computed as sum of multiples of 3 and multiples of 5, minus multiples of 15
//Obvious Solution: O(n)
//My Solution: O(1)
int pe1() {
    return SumNToK(3, 999) + SumNToK(5, 999) - SumNToK(15, 999);
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

//would be a teeny bit faster if I changed the logic to not use a stack.
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

//using my siv from problem 7,
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


void printgrid() {
    int c = 0;
    cout << "{\n";
    for (int i = 0; i < 10; i++) {
        cout << "{";
        for (int j = 0; j < 9; j++) {
            cout << c++ << ", ";
        }
        cout << c++ << "},\n";
    }
    cout << "\n};";
}


uint64_t pe11() {
    const int h = 10;
    const int w = 10;
    const int windowLen = 4;
    uint8_t arr[h][w] = {
{0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
{10, 11, 12, 13, 14, 15, 16, 17, 18, 19},
{20, 21, 22, 23, 24, 25, 26, 27, 28, 29},
{30, 31, 32, 33, 34, 35, 36, 37, 38, 39},
{40, 41, 42, 43, 44, 45, 46, 47, 48, 49},
{50, 51, 52, 53, 54, 55, 56, 57, 58, 59},
{60, 61, 62, 63, 64, 65, 66, 67, 68, 69},
{70, 71, 72, 73, 74, 75, 76, 77, 78, 79},
{80, 81, 82, 83, 84, 85, 86, 87, 88, 89},
{90, 91, 92, 93, 94, 95, 96, 97, 98, 99},

    };

    uint64_t max = 0;
    uint64_t currentProduct = 1;

    //up-down
    for (int i = 0; i < w; i++) {
        uint64_t currentProduct = 1;
        for (int j = 0; j < h - windowLen; j++) {
            for (int k = 0; k < windowLen; k++) {
                currentProduct *= arr[j+k][i];
            }
        }
        if (currentProduct > max)
            max = currentProduct;
    }

    //left-right
    for (int i = 0; i < h; i++) {
        uint64_t currentProduct = 1;
        for (int j = 0; j < w - windowLen; j++) {
            for (int k = 0; k < windowLen; k++) {
                currentProduct *= arr[j][i+k];
            }
        }
        if (currentProduct > max)
            max = currentProduct;
    }

    //diagonal, negative slope
    for (int i = 0; i < w-(windowLen-2); i++) {
        uint64_t currentProduct = 1;
        for (int j = i; j < h-(windowLen-1); j++) {
            for (int k = 0; k < windowLen; k++) {
                uint64_t element = arr[j + k][i + j + k];
                currentProduct *= element;
                for (int o = 0; o < k; o++) {
                    cout << "  ";
                }
                cout << element << endl;
            }
        }
        cout << endl;
        if (currentProduct > max)
            max = currentProduct;
    }



    return (uint64_t)arr[2][3];

}