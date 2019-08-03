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

int n, k;
int v[1024];

bool check(int x, int &delta) {
    int cnt = 0;
    multiset<int> s(v, v + n);
    delta = INT_MAX;
    while (true) {
        if (++cnt > k) return false;
        int rem = x;
        do {
            auto it = prev(s.upper_bound(rem));
            rem -= *it;
            s.erase(it);
        } while (s.size() and rem >= *s.begin());
        if (s.empty()) return true;
        delta = min(delta, *s.begin() - rem);
    }
}

int main() {
    int T; scanf("%d", &T);
    Rep (t, T) {
        scanf("%d%d", &n, &k);
        rep (i, n) scanf("%d", v + i);
        int x, delta;
        x = max(*max_element(v, v + n), (accumulate(v, v + n, 0) + (k - 1)) / k);
        while (!check(x, delta)) x ++;
        printf("Case #%d: %d\n", t, x);
    }
    return 0;
}
