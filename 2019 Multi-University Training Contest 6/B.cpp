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

int n;
int a[50005], k[50005], rk[50005];

int lis(const vector<int>& a) {
    int n = a.size();
    static vector<int> p;
    p.reserve(n); p = {0};
    for (int x : a) {
        auto pos = lower_bound(range(p), x);
        if (pos == p.end()) p.push_back(x);
        else *pos = x;
    }
    return p.size() - 1;
}

int check(int pref) {
    static vector<int> p;
    p.reserve(n); p.clear();
    rep (i, n) if (rk[i] < pref) p.push_back(a[i]);
    return lis(p);
}

int ans[50005];
void bsearch(int al, int ar, int l, int r) {
    if (al == ar) return;
    if (l == r) {
        for (int i = al; i < ar; i++) ans[i] = l;
        return;
    }
    int mid = (l + r) / 2, a = check(mid);
    bsearch(a, ar, mid + 1, r);
    bsearch(al, a, l, mid);
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        rep (i, n) scanf("%d", a + i);
        rep (i, n) scanf("%d", k + i), rk[k[i] - 1] = i;
        vector<int> t(a, a + n);
        int maxans = lis(t);
        bsearch(1, maxans + 1, 1, n + 1);
        int last = 1;
        Rep (i, maxans) {
            while (last < ans[i]) {
                printf("%d%c", i, last == n ? '\n' : ' ');
                last++;
            }
        }
    }
    return 0;
}
