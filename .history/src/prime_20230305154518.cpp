#include "../headers/prime.h"

using namespace std;
using namespace NTL;

// number - 1 = d * 2^r
bool MillerTest(const NTL::ZZ& number, const NTL::ZZ& d, long r,const NTL::ZZ& ran){
    // loop variable
    long i = 0;
    NTL::ZZ y;

    // Compute: x = pow(ran, d) % number
    NTL::ZZ x = PowerMod(ran, d, number);
    if (x == 1 || x == number - 1 ) return true;

    // Below loop mainly runs 'r-1' times.
    do{
        y = x;
        x = (y*y) % number;
        i += 1;
    }while( i<r && x != 1 );

    return (x == 1) && (y == number-1);

}

bool isPrime(const NTL::ZZ& number, long accurancy){
    if (number <= 1) return false;

    NTL::PrimeSeq seq;
    long check_num = seq.next();

    do{
        if(number % check_num == 0) return number == check_num;
        check_num = seq.next();
    }while( check_num < 2000);
    
    // if pass then Miller-Rabin check:
    NTL::ZZ d;
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

        if( !MillerTest(number, d, r, ran) ) return 0;
    }

    return 1;

}
