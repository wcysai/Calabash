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
int a[200005], b[200005], ptr[200005];
pair<int, int> sa[200005];
int c[200005];

priority_queue<pair<int, int>> pq;

void update(int& x, int y) { x = max(x, y); }

const int MAX_TRY = 2000000;
int main() {
    scanf("%d", &n);
    rep (i, n) c[i] = -1;
    rep (i, n) scanf("%d", a + i);
    rep (i, n) scanf("%d", b + i);
    rep (i, n) sa[i] = {a[i], i}; sort(sa, sa + n, greater<>());
    rep (i, n) pq.emplace(b[i] + sa[0].first, i);
    rep (_, MAX_TRY) {
        if (pq.empty()) break;
        int val, id; tie(val, id) = pq.top(); pq.pop();
        update(c[(id+sa[ptr[id]].second)%n], val);
        if (++ptr[id] >= n) continue;
        pq.emplace(b[id] + sa[ptr[id]].first, id);
    }
    rep (i, n) if (c[i] == -1)
        rep (j, n) c[i] = max(c[i], a[j] + b[(i-j+n)%n]);
    rep (i, n) printf("%d ", c[i]);
    return 0;
}
