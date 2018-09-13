#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)
#define Rep(i, n) for (int i = 1; i <=n; i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif

typedef long long LL;

int n, k;
LL T;

bool flag[100005];
unsigned x[100005], y[100005];

void xfrm(int ord) {
    _debug("%d", ord);
    memset(flag, 0, sizeof flag);
    LL b = (1ll << ord) % n;
    rep (i, n) {
        if (flag[i]) continue;
        vector<int> id;
        vector<unsigned> value;
        for (int j = 0; ; j++) {
            int idd = (i + j * b) % n;
            if (flag[idd]) break;
            id.push_back(idd);
            flag[idd] = true;
        }
        int sz = id.size();
        int len = k % (2 * sz);
        for (int i : id) value.push_back(x[i]);
        value.insert(value.end(), range(value));
        value.insert(value.end(), range(value));
        partial_sum(range(value), value.begin(), bit_xor<unsigned>());
        for (int i = 0; i < sz; i++) {
            y[id[i]] = value[i + len - 1];
            if (i) y[id[i]] ^= value[i - 1];
        }
    }
    memcpy(x, y, sizeof y);
}

void powmod(LL T) {
    int ord = 0;
    while (T) {
        if (T & 1) xfrm(ord);
        ord++;
        T >>= 1;
    }
}

int main() {
    scanf("%d%d%lld", &n, &k, &T);
    rep (i, n) scanf("%u", x+i);
    powmod(T);
    rep (i, n) printf("%u%c", x[i], i==n-1?'\n':' ');
    return 0;
}
