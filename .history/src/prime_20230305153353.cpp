#include "../headers/prime.h"

using namespace std;
using namespace NTL;

// number - 1 = d * 2^r
bool MillerTest(const ZZ& number, long d, const ZZ& ran){
    // Compute: x = pow(a, d) % number
    ZZ x = PowerMod(x, d, number);
}

bool isPrime(const ZZ& number, long accurancy){
    if (number <= 1) return false;

    PrimeSeq seq;
    long check_num = seq.next();

    do{
        if(number % check_num == 0) return number == check_num;
        check_num = seq.next();
    }while( check_num < 2000);
    
    // if pass then Miller-Rabin check:
    ZZ d;
    long r;

    // number-1 = d* 2^r

    d = (number-1)/2;
    r = 1;

    do{
        r += 1;
        d /= 2;
    }while( d%2 == 0);
    
    // then we had d and r
    ZZ ran; // random number from 0 to number-1
    for(int i = 0; i < accurancy; i+=1){
        ran = RandomBnd(number);

        if( MillerTest(number, d, ran) ) return 0;
    }

    return 1;

}
