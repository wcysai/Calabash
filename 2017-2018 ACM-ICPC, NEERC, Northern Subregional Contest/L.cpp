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

vector<tuple<LL, int, LL, int>> ans;

void yield(LL f1, int n1, LL f2 = 0, int n2 = 0) {
    ans.emplace_back(f1, n1, f2, n2);
}

int main() {
    freopen("little.in", "r", stdin);
    freopen("little.out", "w", stdout);

    LL n, sqrtn; cin >> n;
    sqrtn = sqrt(n); while ((sqrtn+1)*(sqrtn+1) <= n) sqrtn++;
    if (__builtin_popcountll(n) == 1) return puts("-1"), 0;

    // one prime
    yield(n, 1);
    if (sqrtn * sqrtn == n) yield(sqrtn, 2);
    for (int f = 3; f <= 1000000; f++) {
        LL val = n; int cnt = 0;
        while (val % f == 0) val /= f, cnt++;
        if (val == 1 and cnt > 2) yield(f, cnt);
    }

    // two primes
    if (sqrtn * (sqrtn + 1) == n) yield(sqrtn, 1, sqrtn + 1, 1);
    for (int f1 = 2; f1 <= 1000000; f1++) {
        LL f2 = f1 + 1, val = n; int n1 = 0, n2 = 0;
        while (val % f1 == 0) val /= f1, n1++;
        while (val % f2 == 0) val /= f2, n2++;
        if (val == 1 and n1 and n2 and n1 + n2 > 2) yield(f1, n1, f2, n2);
    }

    printf("%d\n", int(ans.size()));
    for (auto pr : ans) {
        LL f1, f2; int n1, n2;
        tie(f1, n1, f2, n2) = pr;
        printf("%d", n1 + n2);
        rep (_, n1) printf(" %lld", f1);
        rep (_, n2) printf(" %lld", f2);
        printf("\n");
    }
    return 0;
}
