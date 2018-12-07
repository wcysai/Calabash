#pragma GCC optimize(3)
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

LL mask = (1ull << 31) - 1, phi = 1ull << 30;

LL powmod(LL b, LL e) {
    LL r = 1;
    while (e) {
        if (e & 1) r = (r * b) & mask;
        b = (b * b) & mask;
        e >>= 1; 
    }
    return r;
}

LL inv(LL x) {
    LL r = powmod(x, phi - 1);
    assert(((r * x) & mask) == 1);
    return r;
}

int n;
LL x[100005], ix[100005];
LL y[100005];
mt19937_64 gen(time(NULL));

int main() {
    scanf("%d", &n);
    set<LL> xx;
    rep (i, n) {
        do {
            x[i] = (gen() & mask) | 1;
        } while (xx.find(x[i]) != xx.end());
        xx.insert(x[i]);
        printf("%lld ", x[i]);
        ix[i] = inv(x[i]);
    }
    puts("");
    fflush(stdout);
    for (int i = 0; i < n / 2; i++) scanf("%lld", y + i);
    vector<int> cnt;
    int epoch = 10000000 / (n / 2);
    for (int ii = 0; ii < epoch; ii++) {
        int i = ii % n;
        for (int j = 0; j < n / 2; j++) 
            cnt.push_back((y[j] * ix[i]) & mask);
    }
    sort(range(cnt));
    int sz = cnt.size();
    pair<int, int> ans(0, 0);
    int lptr = 0, rptr = 0;
    while (lptr < sz) { 
        while (rptr < sz and cnt[rptr] == cnt[lptr]) rptr++;
        ans = max(ans, {rptr - lptr, cnt[lptr]});
        lptr = rptr;
    }
    printf("%d\n", ans.second);
    return 0;
}
