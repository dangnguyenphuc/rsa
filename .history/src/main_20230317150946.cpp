#include "../headers/main.h"
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

ZZ modMul(const ZZ& number1, const ZZ& number2, const ZZ& mod){
    return (number1*number2) % mod;
}

ZZ modPow(const ZZ& number, const ZZ& power, const ZZ& mod){
    ZZ result(1);

}


bool MillerTest(const ZZ& number, const ZZ& d, long r,const ZZ& ran){

    if (ran == 0) return 0;

    // loop variable
    long i = 0;
    ZZ x;
    ZZ y;

    // Compute: x = pow(ran, d) % number
    x = PowerMod(ran, d, number);

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
  
  
  if (isPrime(n, 10))
     cout << "\n" << n << " is probably prime\n";
  else
     cout << "\n" << n << " is composite\n";
  
  return 0;
}

