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

const int MAXN = 200005;
int n;
LL t, ans;
LL tl[MAXN], spd[MAXN], tr[MAXN];

set<pair<LL, int>>
    s,          // spd[u], u
    enter,      // tl[u], u
    leave,      // tr[u], u
    new_enter;  // tr[u] + spd[u], u

void entering(int u) {
    _debug("t=%lld, enter %d", t, u);
    s.emplace(spd[u], u);
    enter.erase(make_pair(tl[u], u));
    new_enter.erase(make_pair(tl[u] + spd[u], u));
}

void leaving(int u) {
    _debug("t=%lld, leave %d", t, u);
    s.erase(make_pair(spd[u], u));
    leave.erase(make_pair(tr[u], u));
}

int main() {
    scanf("%d", &n);
    rep (i, n) {
        scanf("%lld%lld%lld", tl + i, tr + i, spd + i);
        enter.emplace(tl[i], i);
        leave.emplace(tr[i], i);
        new_enter.emplace(tl[i] + spd[i], i);
    }
    while (true) {
        while (enter.size() and enter.begin()->first <= t) entering(enter.begin()->second);
        while (leave.size() and leave.begin()->first <= t) leaving(leave.begin()->second);
        if (s.empty()) {
            if (enter.empty()) break;
            int id; tie(t, id) = *new_enter.begin();
            _debug("A");
            ans++; entering(id);
        } else {
            int u = s.begin()->second;
            LL tv = tr[u];
            if (tv - t < spd[u]) {
                _debug("B");
                leaving(u);
                continue;
            }
            if (new_enter.size()) {
                int v; LL t2; tie(t2, v) = *new_enter.begin();
                if (t2 - t < spd[u]) {
                    t = t2; ans++;
                    _debug("t=%lld, u=%d, v=%d, t2=%lld", t, u, v, t2);
                    entering(u);
                    continue;
                }
                tv = min(tv, t2);
            }
            LL sz = (tv - t) / spd[u];
            ans += sz; t += sz * spd[u];
        }
    }
    printf("%lld\n", ans);
    return 0;
}
