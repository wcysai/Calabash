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

struct bit_purq {
    int N;
    vector<LL> tr;

    void init(int n) { tr.assign(N = n + 5, 0ll); }

    LL sum(int n) {
        LL ans = 0;
        while (n) { ans += tr[n]; n &= n - 1; }
        return ans;
    }

    int bsearch(LL s) {
        LL sum = 0;
        int pos = 0;
        for (int i = 20; i >= 0; i--) {
            if (pos + (1 << i) < N and sum + tr[pos + (1 << i)] <= s) {
                sum += tr[pos + (1 << i)];
                pos += (1 << i);
            }
        }
        return pos;
    }

    void add(int n, LL x) {
        while (n < N) { tr[n] += x; n += n & -n; }
    }
} bitw, bitc;

int n, m;
int w[200005], id[200005];

int main() {
    int q; scanf("%d", &q);
    while (q--) {
        scanf("%d%d", &n, &m);
        rep (i, n) scanf("%d", w + i);
        vector<pair<int, int>> poss;
        rep (i, n) poss.emplace_back(w[i], i);
        sort(range(poss));
        rep (i, n) id[poss[i].second] = i + 1;
        bitw.init(n); bitc.init(n);
        rep (i, n) {
            int bnd = m - w[i];
            int pos = bitw.bsearch(bnd);
            printf("%lld ", i - bitc.sum(pos));
            bitw.add(id[i], w[i]);
            bitc.add(id[i], 1);
        }
        puts("");
    }
    return 0;
}
