#include "../headers/main.h"
#include <NTL/ZZ.h>
#include<unistd.h>

using namespace std;
using namespace NTL;

// trailing zeros:
Bcd#include "../headers/main.h"
#include <NTL/ZZ.h>
#include<unistd.h>

using namespace std;
using namespace NTL;

// trailing zeros:
unsigned trailing_zeroes(ZZ number) {
    unsigned bits = 0;

    if (x) {
        /* assuming `x` has 32 bits: lets count the low order 0 bits in batches */
        /* mask the 16 low order bits, add 16 and shift them out if they are all 0 */
        while (!(number & 0x0000FFFF)) { bits += 16; number >>= 16;}
        /* mask the 8 low order bits, add 8 and shift them out if they are all 0 */
        if (!(number & 0x000000FF)) { bits +=  8; number >>=  8; }
        /* mask the 4 low order bits, add 4 and shift them out if they are all 0 */
        if (!(number & 0x0000000F)) { bits +=  4; number >>=  4; }
        /* mask the 2 low order bits, add 2 and shift them out if they are all 0 */
        if (!(number & 0x00000003)) { bits +=  2; number >>=  2; }
        /* mask the low order bit and add 1 if it is 0 */
        bits += (number & 1) ^ 1;
    }
    return bits;
}


// Euclide
ZZ E_gcd(ZZ number1, ZZ number2){
    if (number1 == 0) return number2;
    return E_gcd(number2%number1 , number1);
}

// Stein's GCD binary GCD
ZZ S_gcd(ZZ number1, ZZ number2){
    
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
    ZZ result(1);
    while ( power > long(0) ){
        if( (power & 1) == 1){
            result = modMul(result,number,mod);
        }
        number = modMul(number, number, mod);
        power = power >> 1;
        
    }
    return result;
}


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

int main()
{
    ZZ n;
    cout << "n: ";
    cin >> n;
    // Example: Prime number is
    // 10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000174295123051

    // if (isPrime(n, 10))
    //     cout << "\n" << n << " is probably prime\n";
    // else
    //     cout << "\n" << n << " is composite\n";
    cout<<
    return 0;

    // ZZ n2;
    // cout << "n2: ";
    // cin >> n2;
    // ZZ invert_n;
    // cout << extendedEuclid(n,n2,invert_n);
    // cout<<endl<<invert_n;
    // chạy thử các trường hợp tìm số nghịch đảo tương ứng trong slide :)
}

