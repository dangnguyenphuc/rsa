#include "../headers/main.h"
#include <iostream>
#include <NTL/ZZ.h>


using namespace std;
using namespace NTL;

/*
 *Compile by hit this in cmd line: 
 g++ -g -O2 -std=c++11 -pthread -march=native <name>.cpp -o <name> -lntl -lgmp -lm
 * */

int main(){

  ZZ a, b, c;

  cin >> a;
  cin >> b;
  c = (a+1)*(b+1);
  cout << c << "\n";
  return 0;
}


