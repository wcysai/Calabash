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
int mmin, mmax;
int m[64], c[64];
bool ok[10240];

bool subsolve(vector<int> q) {
    memset(ok, 0, sizeof ok);
    bitset<10240> bs;
    bs.reset(); bs.set(0);
    for (int x : q) bs |= bs << x; 
    for (int i = mmin; i <= mmax; i++) if (bs[i]) return true;
    return false;
}

bool solve(vector<int> q) {
    vector<int> qn;
    for (int i = 0; i < n; i++) {
        int cur = q[i], rem = cur;
        for (int use = 1; use <= rem; use *= 2) {
            if (1ll * use * m[i] > mmax) continue;
            qn.emplace_back(use * m[i]);
            rem -= use;
        }
        if (rem and 1ll * rem * m[i] <= mmax) qn.emplace_back(rem * m[i]);
    }
    return subsolve(qn);
}

bool check(int dup) {
    vector<int> q(c, c + n);
    for (int& x : q) x /= dup;
    return solve(q);
}

int main() {
    cin >> n >> mmin >> mmax;
    rep (i, n) cin >> m[i] >> c[i];
    int ans = 0;
    int l = 1, r = 1000005;
    while (l != r) {
        int mid = (l + r) / 2;
        if (check(mid)) l = mid + 1;
        else r = mid;
    }
    cout << l - 1 << endl;
    return 0;
}
