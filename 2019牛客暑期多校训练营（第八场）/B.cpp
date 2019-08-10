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
map<int, vector<int>> occ;

inline LL c2(LL x) {
    return x * (x + 1) / 2;
}

LL compute(const vector<int> &vec) {
    LL tot = c2(n);
    for (int i = 1; i < vec.size(); i++) tot -= c2(vec[i] - vec[i-1] - 1);
    tot -= c2(vec[0]);
    tot -= c2(n - vec.back() - 1);
    return tot;

}

int main() {
    scanf("%d", &n);
    rep (i, n) {
        int a; scanf("%d", &a);
        occ[a].push_back(i);
    }
    LL ans = 0;
    for (auto& p : occ) ans += compute(p.second);
    cout << ans << endl;
    return 0;
}

