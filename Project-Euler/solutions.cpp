#include <cmath>
#include <iostream>
#include <queue>
#include <stack>
#include "myMath.h"

//TODO: figure out a consistent usage of types.
//TODO: make sure to delete all heap allocated arrays.


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
                                                        //there may be a simpler way to calculate this, but I couldn't figure it out. this formula seems strange to me.
        }
        if (factorCount > 500) {
            return triangleNum;
        }
    }
    return -1;
}

//100 numbers, each with 50 digits.
//find the first 10 digits of the sum.
//add 10 (could be 9) leading zeroes to the numbers being added. after you add the digits, trim the least significant one.
//adding the leading zeroes ensures that we have enough digits at the end.
uint64_t pe13() {
        //100 numbers, each with 50 digits.
        char num[100][51] = {
            {"37107287533902102798797998220837590246510135740250"},
            {"46376937677490009712648124896970078050417018260538"},
            {"74324986199524741059474233309513058123726617309629"},
            {"91942213363574161572522430563301811072406154908250"},
            {"23067588207539346171171980310421047513778063246676"},
            {"89261670696623633820136378418383684178734361726757"},
            {"28112879812849979408065481931592621691275889832738"},
            {"44274228917432520321923589422876796487670272189318"},
            {"47451445736001306439091167216856844588711603153276"},
            {"70386486105843025439939619828917593665686757934951"},
            {"62176457141856560629502157223196586755079324193331"},
            {"64906352462741904929101432445813822663347944758178"},
            {"92575867718337217661963751590579239728245598838407"},
            {"58203565325359399008402633568948830189458628227828"},
            {"80181199384826282014278194139940567587151170094390"},
            {"35398664372827112653829987240784473053190104293586"},
            {"86515506006295864861532075273371959191420517255829"},
            {"71693888707715466499115593487603532921714970056938"},
            {"54370070576826684624621495650076471787294438377604"},
            {"53282654108756828443191190634694037855217779295145"},
            {"36123272525000296071075082563815656710885258350721"},
            {"45876576172410976447339110607218265236877223636045"},
            {"17423706905851860660448207621209813287860733969412"},
            {"81142660418086830619328460811191061556940512689692"},
            {"51934325451728388641918047049293215058642563049483"},
            {"62467221648435076201727918039944693004732956340691"},
            {"15732444386908125794514089057706229429197107928209"},
            {"55037687525678773091862540744969844508330393682126"},
            {"18336384825330154686196124348767681297534375946515"},
            {"80386287592878490201521685554828717201219257766954"},
            {"78182833757993103614740356856449095527097864797581"},
            {"16726320100436897842553539920931837441497806860984"},
            {"48403098129077791799088218795327364475675590848030"},
            {"87086987551392711854517078544161852424320693150332"},
            {"59959406895756536782107074926966537676326235447210"},
            {"69793950679652694742597709739166693763042633987085"},
            {"41052684708299085211399427365734116182760315001271"},
            {"65378607361501080857009149939512557028198746004375"},
            {"35829035317434717326932123578154982629742552737307"},
            {"94953759765105305946966067683156574377167401875275"},
            {"88902802571733229619176668713819931811048770190271"},
            {"25267680276078003013678680992525463401061632866526"},
            {"36270218540497705585629946580636237993140746255962"},
            {"24074486908231174977792365466257246923322810917141"},
            {"91430288197103288597806669760892938638285025333403"},
            {"34413065578016127815921815005561868836468420090470"},
            {"23053081172816430487623791969842487255036638784583"},
            {"11487696932154902810424020138335124462181441773470"},
            {"63783299490636259666498587618221225225512486764533"},
            {"67720186971698544312419572409913959008952310058822"},
            {"95548255300263520781532296796249481641953868218774"},
            {"76085327132285723110424803456124867697064507995236"},
            {"37774242535411291684276865538926205024910326572967"},
            {"23701913275725675285653248258265463092207058596522"},
            {"29798860272258331913126375147341994889534765745501"},
            {"18495701454879288984856827726077713721403798879715"},
            {"38298203783031473527721580348144513491373226651381"},
            {"34829543829199918180278916522431027392251122869539"},
            {"40957953066405232632538044100059654939159879593635"},
            {"29746152185502371307642255121183693803580388584903"},
            {"41698116222072977186158236678424689157993532961922"},
            {"62467957194401269043877107275048102390895523597457"},
            {"23189706772547915061505504953922979530901129967519"},
            {"86188088225875314529584099251203829009407770775672"},
            {"11306739708304724483816533873502340845647058077308"},
            {"82959174767140363198008187129011875491310547126581"},
            {"97623331044818386269515456334926366572897563400500"},
            {"42846280183517070527831839425882145521227251250327"},
            {"55121603546981200581762165212827652751691296897789"},
            {"32238195734329339946437501907836945765883352399886"},
            {"75506164965184775180738168837861091527357929701337"},
            {"62177842752192623401942399639168044983993173312731"},
            {"32924185707147349566916674687634660915035914677504"},
            {"99518671430235219628894890102423325116913619626622"},
            {"73267460800591547471830798392868535206946944540724"},
            {"76841822524674417161514036427982273348055556214818"},
            {"97142617910342598647204516893989422179826088076852"},
            {"87783646182799346313767754307809363333018982642090"},
            {"10848802521674670883215120185883543223812876952786"},
            {"71329612474782464538636993009049310363619763878039"},
            {"62184073572399794223406235393808339651327408011116"},
            {"66627891981488087797941876876144230030984490851411"},
            {"60661826293682836764744779239180335110989069790714"},
            {"85786944089552990653640447425576083659976645795096"},
            {"66024396409905389607120198219976047599490197230297"},
            {"64913982680032973156037120041377903785566085089252"},
            {"16730939319872750275468906903707539413042652315011"},
            {"94809377245048795150954100921645863754710598436791"},
            {"78639167021187492431995700641917969777599028300699"},
            {"15368713711936614952811305876380278410754449733078"},
            {"40789923115535562561142322423255033685442488917353"},
            {"44889911501440648020369068063960672322193204149535"},
            {"41503128880339536053299340368006977710650566631954"},
            {"81234880673210146739058568557934581403627822703280"},
            {"82616570773948327592232845941706525094512325230608"},
            {"22918802058777319719839450180888072429661980811197"},
            {"77158542502016545090413245809786882778948721859617"},
            {"72107838435069186155435662884062257473692284509516"},
            {"20849603980134001723930671666823555245252804609722"},
            {"53503534226472524250874054075591789781264330331690"}
        };
        uint64_t sum = 0;



        //add ten leading zeroes to the numbers being added. allows us to easily store 10 digits at the least.
        for (int c = 49; c >=0; c--) {
            for (int n = 0;  n< 100; n++) {
                sum += (num[n][c] - '0') * pow(10,10);
            }
            sum /= 10;
        }
        
        while (sum >= (uint64_t)pow(10, 10)) //trim extra digits.
            sum /= 10;
        
        return sum;
}

//I imagine that this is the only way to solve this.
long pe14() {
    const int max = 1000000;

    long maxIterations = 0;
    long maxN = -1;
  
    for (long i = 1; i < max; i++) {
        long long n = i;
        long currentIterations = 0;
        while (n != 1) {
            n = (n % 2) ? n * 3 + 1 : n / 2;
            currentIterations++;
        }
        if (currentIterations > maxIterations) {
            maxIterations = currentIterations;
            maxN = i;
        }
    }
    return maxN;
}

void reducePascals(long long arr[], int len, long long &n) {
    
    if (len == 2) {
        n = arr[0] + arr[1];
        return;
    }

    long long* nextRow = new long long[len - 1];

    for (int i = 0; i < len - 1; i++) {
        nextRow[i] = arr[i] + arr[i + 1];
        cout << nextRow[i] << " ";
    }
    cout << endl;
    reducePascals(nextRow, len - 1, n);
    delete[] nextRow;
}

long long pe15() {
    //this would be nchoosek(40,20), but that is difficult to compute directly because factorials are so large.
    //we will use an identity of nchoosek(40,20)
    const int lengthSide = 20;
    long long pascalsTriangle[lengthSide+1] = { 0 };

    for (int i = 0; i < lengthSide + 1; i++) {
        pascalsTriangle[i] = nchoosek(lengthSide,i);
        cout << pascalsTriangle[i] << " ";
    }
    cout << endl;
    long long ret;
    reducePascals(pascalsTriangle, lengthSide + 1, ret);
    return ret;
}


//sum of the digits of 2^1000
//calculates 2^1000 by storing digits in an array.
long pe16() {
    const int len = 302; //302 is cieling(log10(2^1000))
    short p2[len] = { 0 }; //store each digit of the current power of two. p[0] being least significant digit, p[len-1] being most significant
    p2[0] = 1; // 2^0

    int maxDigitReached = 0;

    for (int i = 0; i < 1000; i++) {
        for (int d = maxDigitReached; d >= 0; d--) { //double the number in p2. work from most significant down.
            int k = d;
            short times2 = p2[k] * 2;
            p2[k] = times2 % 10;
            while (times2 /= 10) {
                k++;
                times2 += p2[k];
                p2[k] = times2 % 10;
                if (k > maxDigitReached)
                    maxDigitReached = k;
            }
        }
    }
    long sum = 0;
    for (int r = maxDigitReached; r >= 0; r--) {
        sum += p2[r];
    }
    return sum;
}


#include <string>
#include <iostream>
#include <vector> 
#include <map>
#include <iterator>

using namespace std;

#define xx(a) word = a;break;

//can be sped-up by finding these values before compilation. not significant for the non-iterative calculation.
int lookuplength(int n) {
    const char* word;
    switch (n) {
    case 0: return strlen("");
    case 1: return strlen("one");
    case 2: return strlen("two");
    case 3: return strlen("three");
    case 4: return strlen("four");
    case 5: return strlen("five");
    case 6: return strlen("six");
    case 7: return strlen("seven");
    case 8: return strlen("eight");
    case 9: return strlen("nine");
    case 10: return strlen("ten");
    case 11: return strlen("eleven");
    case 12: return strlen("twelve");
    case 13: return strlen("thirteen");
    case 14: return strlen("fourteen");
    case 15: return strlen("fifteen");
    case 16: return strlen("sixteen");
    case 17: return strlen("seventeen");
    case 18: return strlen("eighteen");
    case 19: return strlen("nineteen");
    case 20: return strlen("twenty");
    case 30: return strlen("thirty");
    case 40: return strlen("forty");
    case 50: return strlen("fifty");
    case 60: return strlen("sixty");
    case 70: return strlen("seventy");
    case 80: return strlen("eighty");
    case 90: return strlen("ninety");
    case 100: return strlen("hundred");
    case 1000: return strlen("thousand");
    default: return strlen("and");
    }
}


//logic for breaking number into words
int numlen(int n) {
    if (n == 1000) {
        return lookuplength(1) + lookuplength(1000);
    }
    if (n >= 100) {
        int len = lookuplength(n / 100) + lookuplength(100); 
        if (n % 100 != 0)
            len += (numlen(-1) + numlen(n % 100));
        return len;
    }
    if (n <= 19) {
        return lookuplength(n);
    }
    if (n < 100) {
        return lookuplength(10 * (n / 10)) + lookuplength(n % 10);
    }
}

//calculates the sum by counting the amount of times that each word is used.
//i should have written the code to be more dynamic, but it works fine for calculating the sum for n<=1000
long pe17() {
    long sum = 0;

    sum += lookuplength(1) * (9 * 10 + 100 + 1);
    for (int i = 2; i < 10; i++) {
        sum += lookuplength(i) * (9 * 10 + 100);
    }
    
    for (int i = 10; i < 20; i++) {
        sum += lookuplength(i) * 10;
    }
    for (int i = 2; i < 10; i++) {
        sum += lookuplength(i*10) * 10*10;
    }
    sum += lookuplength(100) *100*9;

    sum += lookuplength(1000);
    sum += strlen("and") * 99 * 9;

    return sum;
}

//generates each word and counts the length.
long pe17_iterative() {
    long sum = 0;
    for (int i = 1; i <= 1000; i++) {
        int thislen = numlen(i);
        sum += thislen;
    }
    return sum;
}




//find the greatest path from top to bottom of the triangle.
//this is a dynamic programming problem
//generate the maximum path in each row iteratively.
//bad design would lead you to test every single path recursively
//O(n)
long pe18() {
    const int rows = 15;
    vector<int> triangle[] = {
        {75},
        {95, 64},
        {17, 47, 82},
        {18, 35, 87, 10},
        {20, 4, 82, 47, 65},
        {19, 1, 23, 75, 3, 34},
        {88, 2, 77, 73, 7, 63, 67},
        {99, 65, 4, 28, 6, 16, 70, 92},
        {41, 41, 26, 56, 83, 40, 80, 70, 33},
        {41, 48, 72, 33, 47, 32, 37, 16, 94, 29},
        {53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14},
        {70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57},
        {91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48},
        {63, 66, 4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31},
        {4, 62, 98, 27, 23, 9, 70, 98, 73, 93, 38, 53, 60, 4, 23}
    };

    for (int i = 1; i < rows; i++) {
        for (int j = 0; j<triangle[i].size(); j++) {
            int greaterParent;
            #define myMax(a,b) (a>b)?a:b;
            if (j == 0) 
                greaterParent = triangle[i - 1][j];
            else if (j == triangle[i].size() - 1) 
                greaterParent = triangle[i - 1][j - 1];
            else
                greaterParent = myMax(triangle[i - 1][j], triangle[i - 1][j - 1]);
            
            triangle[i][j] += greaterParent;
        }
        cout << endl;
    }

    int max = -1;
    for (int i = 0; i < triangle[rows - 1].size(); i++) {
        if (triangle[rows - 1][i] > max)
            max = triangle[rows - 1][i];
    }

    return max;
}

/*
1 Jan 1900 was a Monday.
Thirty days has September,
April, June and November.
All the rest have thirty-one,
Saving February alone,
Which has twenty-eight, rain or shine.
And on leap years, twenty-nine.
A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.
*/
//How many Sundays fell on the first of the month during the twentieth century(1 Jan 1901 to 31 Dec 2000) ?
int pe19() {

    const char* days[] = { "mon", "tues", "wed", "thur", "fri", "sat", "sun" };
    const char* months[] = { "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" };
    int sundayMonths = 0;
    int year = 1900;
    int month = 0;
    int day = 0;
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    while (year <= 2000) {
        bool isLeapYear = (!(year % 4) && (year % 100)) || (!(year % 100) && !(year % 400));
        for (int month = 0; month < 12; month++) {
            if (day == 6 && year >= 1901) {
                sundayMonths++;
            }
            int daysThisMonth = (isLeapYear && month == 1) ? daysInMonth[month] + 1 : daysInMonth[month];
            day = (day + daysThisMonth) % 7;
        }
        year++; 
    }
    return sundayMonths;
}