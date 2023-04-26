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
#include <cmath>
#include <vector>
#include <math.h>
#include <NTL/vector.h>
using namespace std;
using namespace NTL;

typedef long long ll;

vector<ll> coeffs(ll n) {
    vector<ll> c((n + 1), ll(1));
    for (ll i(1); i <= n; i++) {
        c[i] = c[i - 1] * (n - i + 1) / i;
    }
    return c;
}

bool is_prime(ll n) {
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

int main() {
    ll n;
    cout << "Enter a number: ";
    cin >> n;
    if (is_prime(n)) {
        cout << n << " is prime.\n";
    } else {
        cout << n << " is composite.\n";
    }
    return 0;
}
