#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL;

LL a, b, tot;


int main() {
    cin >> a >> b; a--; b--;
    tot = a + b;
    LL beg = (tot + 1) * (tot + 2) / 2;
    if (tot & 1) {
        beg -= b;
    } else {
        beg -= a;
    }
    cout << beg << endl;
    return 0;
}
