#include "../headers/main.h"
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;


int main()
{
  ZZ n;

  cout << "n: ";
  cin >> n;

  if (isPrime(n, 10))
     cout << n << " is probably prime\n";
  else
     cout << n << " is composite\n";
}