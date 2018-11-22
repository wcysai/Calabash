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
#define PROBLEM "decisions"
typedef long long LL;
typedef unsigned long long ULL;
template <class T1, class T2> T1 minz(T1& l, T2 r) { return l = min(l, (T1)r); }
template <class T1, class T2> T1 maxz(T1& l, T2 r) { return l = max(l, (T1)r); }

typedef bitset<1024> bset, *bsetp;

int a[2048];
int n, c;
bsetp prep[2048];

int main() {
#ifndef __LOCAL_DEBUG__
    freopen(PROBLEM ".in", "r", stdin);
    freopen(PROBLEM ".out", "w", stdout);
#endif
    while (scanf("%d", &n), n) {
        rep (i, n) scanf("%d", a + i);
        scanf("%d", &c);
        rep (i, n) {
            prep[i] = new bset[n - i + 1];
            prep[i][0].reset();
            prep[i][0].set(0); prep[i][0].set(a[i]);
            for (int j = i + 1; j <= n; j++) 
                prep[i][j - i] = prep[i][j - i - 1] | (prep[i][j - i - 1] << a[j]);
        }
        
        int q; scanf("%d", &q);
        int k = 0;
        string str;
        while (q--) {
           int aa, bb, cc; scanf("%d%d%d", &aa, &bb, &cc);
           int l, r, t;
           l = (aa + k) % (n - bb + 1) + 1;
           r = l + bb - 1;
           t = (cc + k) % (c + 1);
           // _debug("l=%d, r=%d, t=%d", l, r, t);
           l--; r--;
           bool ans = prep[l][r - l].test(t);
           if (ans) k++;
           str.push_back(ans ? 'Y' : 'N');
        }
        cout << str << endl;
        rep (i, n) delete[] prep[i];
    }
    return 0;
}
