#include "../headers/main.h"

using namespace std;
using namespace NTL;

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