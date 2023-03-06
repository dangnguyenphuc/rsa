#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

long witness(const ZZ& n, const ZZ& x)
{
   ZZ m, y, z;
   long j, k;

   if (x == 0) return 0;

   // compute m, k such that n-1 = 2^k * m, m odd:

   

   z = PowerMod(x, m, n); // z = x^m % n
   if (z == 1) return 0;

   j = 0;
   do {
      y = z;
      z = (y*y) % n; 
      j++;
   } while (j < k && z != 1);

   return z != 1 || y != n-1;
}


long PrimeTest(const ZZ& n, long t)
{
   if (n <= 1) return 0;

   // first, perform trial division by primes up to 2000

   PrimeSeq s;  // a class for quickly generating primes in sequence
   long p;

   p = s.next();  // first prime is always 2
   while (p && p < 2000) {
      if ((n % p) == 0) return (n == p);
      p = s.next();  
   }

   // second, perform t Miller-Rabin tests

   ZZ x;
   long i;
    long k;
    ZZ m;
    k = 1;
   m = n/2;
   while (m % 2 == 0) {
      k++;
      m /= 2;
   }

   for (i = 0; i < t; i++) {
      x = RandomBnd(n); // random number between 0 and n-1

      if (witness(n, x, m, k)) 
         return 0;
   }

   return 1;
}

int main()
{
   ZZ n;

   cout << "n: ";
   cin >> n;

   if (PrimeTest(n, 10))
      cout << n << " is probably prime\n";
   else
      cout << n << " is composite\n";
}