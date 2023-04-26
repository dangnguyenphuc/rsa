#include <NTL/ZZ.h>
#include <iostream>

int main() {
    NTL::ZZ a(123);
    NTL::ZZ e (456);
    NTL::ZZ n (789);
    NTL::ZZ result(NTL::PowerMod(a, e, n));

    std::cout << "Result of " << a << "^" << e << " mod " << n << " is " << result << std::endl;

    return 0;
}