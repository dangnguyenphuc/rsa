#include "../headers/main.h"
#include <NTL/ZZ.h>
#include <unistd.h>
#include <time.h>
#include <NTL/RR.h>
#include <NTL/ZZ_p.h>
#include <NTL/ZZ_pX.h>
#include <NTL/ZZX.h>
#include <NTL/vec_ZZ.h>
#include <NTL/mat_ZZ.h>
#include <NTL/BasicThreadPool.h>
#include <NTL/vector.h>
#include <cmath>
#include <vector>
#include <math.h>

using namespace std;
using namespace NTL;

#define ITERATION_NUM 10
typedef long long ll;


vector<ll> coeffs(ll n) {
    vector<ll> c((n + 1), ll(1));
    for (ll i(1); i <= n; i++) {
        c[i] = c[i - 1] * (n - i + 1) / i;
    }
    return c;
}

bool AKS_primality_test(ll n) {
    if (n <= 1) {
        return false;
    }
    if (n == 2 || n == 3 || n == 5) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0) {
        return false;
    }
    ll r(2);
    while (r <= n) {
        if (n % r == 0) {
            break;
        }
        r = r + 1;
    }
    if (r == n) {
        return true;
    }
    for (ll a(2); a <= min(r - 1, ll( sqrt(n) * log2(n) ) ); a++) {
        vector<ll> c = coeffs(n);
        c[0] = c[0] - 1;
        c[a] = c[a] - 1;
        for (ll i(1); i < n; i++) {
            for (ll j(n); j >= i; j--) {
                c[j] =  c[j] - c[j - i];
            }
        }
        if (c[n] % n != 0) {
            return false;
        }
    }
    return true;
}

// trailing zeros:
long trailing_zeroes(ZZ number) {
    long bits = 0;

    if (number!=0) {
        /* mask the 16 low order bits, add 16 and shift them out if they are all 0 */
        while ((number & 0x0000FFFF)==0) { bits += 16; number >>= 16;}
        /* mask the 8 low order bits, add 8 and shift them out if they are all 0 */
        while ((number & 0x000000FF)==0) { bits +=  8; number >>=  8; }
        /* mask the 4 low order bits, add 4 and shift them out if they are all 0 */
        while ((number & 0x0000000F)==0) { bits +=  4; number >>=  4; }
        /* mask the 2 low order bits, add 2 and shift them out if they are all 0 */
        while ((number & 0x00000003)==0) { bits +=  2; number >>=  2; }
        /* mask the low order bit and add 1 if it is 0 */
        if((number & 0x00000001)==0){ bits += 1; }
    }
    return bits;
}

// Stein's GCD binary GCD
ZZ S_gcd(ZZ number1, ZZ number2){
    if( number1 == 0 ) return number2;
    if (number2 == 0 ) return number1;


    long trail1;
    long trail2;
    long min_trail;

    trail1 = trailing_zeroes(number1);  number1 = number1>>trail1;                       
    trail2 = trailing_zeroes(number2);  number2 = number2>>trail2;
    min_trail = (trail1 > trail2)? trail2 : trail1;

    while (1)
    {
        assert(number1%2==1);
        assert(number2%2==1);

        if(number1 > number2){
            ZZ _swap;
            _swap = number1;
            number1 = number2;
            number2 = _swap;
        }

        number2 = number2 - number1;

        if( number2 == 0 )
        {
            return number1 << min_trail;
        }

        number2 = number2 >> trailing_zeroes(number2);
    }
    

}

// Euclide
ZZ E_gcd(ZZ number1, ZZ number2){
    if (number1 == 0) return number2;
    return E_gcd(number2%number1 , number1);
}

// Extended Euclide to find invert number
bool extendedEuclid(const ZZ& number1, const ZZ& number2, ZZ& t){
/*
Bézout's identity asserts that "number1" and "number2" are coprime if and only if there exist integers s and t such that
    number2*s + number1*t = 1
    Reducing this identity modulo number2 give:
    number1*t = 1 mod number2     
    ===============> Phù hợp để tìm số nghịch đảo do Định nghĩa số nghịch đảo của w là w^(-1) với w^(-1) * w = 1
*/
    t = 0;
    ZZ newt(1);
    ZZ r;
    ZZ newr;
    ZZ quotient;

    r = number2;
    newr = number1;

    ZZ temp1, temp2;

    while (newr != 0)
    {
        quotient = r / newr;
        
        temp1 = t;
        t = newt;
        newt = temp1 - quotient*newt;

        temp2 = r;
        r = newr;
        newr = temp2 - quotient*newr;

    }

    if (r > 1) return 0;
    if (t < 0) t = t + number2;
    return 1;
    

}

ZZ modMul(const ZZ& number1, const ZZ& number2, const ZZ& mod){
    return (number1*number2) % mod;
}

ZZ modPow(ZZ number, ZZ power, ZZ mod){
    assert(power>=long(0));
    if(mod > 0){
        ZZ result(1);
        while ( power > long(0) ){
            if( (power & 1) == 1){
                result = modMul(result,number,mod);
            }
            number = modMul(number, number, mod);
            power = power >> 1;
        }
        return result;
    }else{
        ZZ result(1);
        while ( power > long(0) ){
            if( (power & 1) == 1){
                result = result*number;
            }
            number = number*number;
            power = power >> 1;
        }
        return result;
    }
    
}

// Miller-Rabin primality test -> just determine probable prime number
bool MillerTest(const ZZ& number, const ZZ& d, long r,const ZZ& ran){

    if (ran == 0) return 0;

    // loop variable
    long i = 0;
    ZZ x;
    ZZ y;

    // Compute: x = pow(ran, d) % number
    x = modPow(ran, d, number);

    if ( x == 1 ) return false;

    // Below loop mainly runs 'r-1' times.
    do{
        y = x;
        x = (y*y) % number;
        i += 1;
    } while( i<r && x != 1 );

    return (x != 1) || (y != number-1);

}


// main Miller-Rabin test
bool isPrime(const ZZ& number, long accurancy){
    if (number <= 1) return false;

    PrimeSeq seq;
    long check_num = seq.next();

    do{
        if(number % check_num == 0) return number == check_num;
        check_num = seq.next();
    }while( check_num && check_num < 2000);
    
    // if pass then Miller-Rabin check:
    ZZ d;
    long r;

    // number-1 = d* 2^r

    d = (number)/2;
    r = 1;

    while ( d % 2 == 0)
    {
        r += 1;
        d /= 2;    
    }

    // then we had d and r
    ZZ ran; // random number from 0 to number-1
    for(int i = 0; i < accurancy; i+=1){
        ran = RandomBnd(number);

        if( MillerTest(number, d, r, ran) ) return false;
    }

    return true;

}

ZZ generate_prime(long n_bits){
    ZZ res;
    bool found = false;
    while (!found)
    {
        res = RandomBits_ZZ(n_bits);
        if (res % 2 == 0) res++;
        found = isPrime(res, ITERATION_NUM);
    }
    
    return res;
}

ZZ generate_prime_with_gap(ZZ& p, long key_Bits){
    ZZ res;
    bool found = false;
    ZZ _upper_bound;
    ZZ _lower_bound;
    ZZ _middle_bound;
    ZZ up;
    ZZ low;
    ZZ count(0);

    _middle_bound = modPow(ZZ(2),ZZ(key_Bits/2),ZZ(0)) - ZZ(1);
    _lower_bound = modPow(ZZ(2),ZZ(key_Bits/2)-ZZ(10),ZZ(0));
    _upper_bound = modPow(ZZ(2),ZZ(key_Bits/2)+ZZ(10),ZZ(0));

    while (!found)
    {
        if (count % 2 == 1)
        {
            up = _upper_bound;
            low = p + _lower_bound; 
            res = low + RandomBnd(up-low);
        }else{
            up = p - _middle_bound;
            low = _lower_bound; 
            res = low + RandomBnd(up-low);
        }
        
        if (res % 2 == 0) res++;
        found = isPrime(res, ITERATION_NUM);
        count = count + 1;
    }
    
    return res;
}

int main()
{
    SetNumThreads(4); // Number of threads to use for parallelization

    // clock_t s,e;
    // double time_taken;
    // ZZ n;
    // cout << "n: ";
    // cin >> n;
    // Example: Prime number is
    // 10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000174295123051

    // if (isPrime(n, 10))
    //     cout << "\n" << n << " is probably prime\n";
    // else
    //     cout << "\n" << n << " is composite\n";

    // ZZ n2;
    // cout << "n2: ";
    // cin >> n2;
    // // ZZ invert_n;
    // // cout << extendedEuclid(n,n2,invert_n);
    // // cout<<endl<<invert_n;
    // // chạy thử các trường hợp tìm số nghịch đảo tương ứng trong slide 
    // s = clock();
    // cout << S_gcd(n,n2);
    // e = clock();
    // time_taken = double(e - s) / double(CLOCKS_PER_SEC);
    // printf("\nStein GCD took: %lf \n",time_taken);

    // s = clock();
    // cout << E_gcd(n,n2);
    // e = clock();
    // time_taken = double(e - s) / double(CLOCKS_PER_SEC);
    // printf("Euclide GCD took: %lf",time_taken);
    // // cout << trailing_zeroes(n);
    

    // Generate 2 prime:
    ZZ p;
    p = generate_prime(1024);

    // Print the prime number
    cout << "p = " << p << endl;

    ZZ q;
    q = generate_prime_with_gap(p, 2048);

    // Print the prime number
    cout << "q = " << q << endl;

    return 0;
}

