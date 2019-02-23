#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, \
    ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

bool isprime(int x) {
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0) return false;
    return true;
}

const char *get_suffix(int x) {
    x %= 100;
    if (x >= 10 and x <= 20) return "th";
    x %= 10;
    if (x == 1) return "st";
    if (x == 2) return "nd";
    if (x == 3) return "rd";
    return "th";
}

int main() {
    int x, T = 0; 
    while (cin >> x, x) {
        T++;
        printf("Case #%d: %d%s Wilson number is equal to %d.\n", T,
        x, get_suffix(x), x == 4 ? 2 : (isprime(x) ? x - 1 : 0));
    }
    return 0;
}
