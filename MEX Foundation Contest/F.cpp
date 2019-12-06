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
 
set<LL> s = {0, 1, 2};
 
LL sqrtu(LL x) {
    LL r = sqrt(x);
    while (r * r < x) r++;
    return r;
}
 
void solve(LL x) {
    if (s.count(x)) return;
    LL rt = sqrtu(x), rem = rt * rt - x;
    solve(rt); solve(rem);
    printf("%lld %lld\n", rt, rem);
    s.insert(x);
}
 
int main() {
    LL n; cin >> n;
    solve(n);
    return 0;
}