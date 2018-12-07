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

int n, k;
int a[1 << 20];
int minv[1 << 20];
pair<int, int> src[1 << 20], dest[1 << 20];
typedef bitset<100008> bs;

int main() {
    scanf("%d%d", &n, &k);
    rep (i, n) scanf("%d", a + i);
    deque<int> q;
    for (int i = 0; i < n - k; i++) {
        while (q.size() and a[q.back()] <= a[i]) q.pop_back();
        q.push_back(i);
    }
    for (int i = n - k; i < n; i++) {
        while (q.size() and q.front() < i - (n - k)) q.pop_front();
        while (q.size() and a[q.back()] <= a[i]) q.pop_back();
        q.push_back(i);
        minv[i - (n - k)] = a[q.front()];
    }
    rep (i, n) src[i] = {a[i], i};
    rep (i, k) dest[i] = {minv[i], i};
    sort(src, src + n, greater<>());
    sort(dest, dest + k, greater<>());
    bs ok, cur; ok.reset(); ok = ~ok; cur.reset();
    int ptr = 0;
    rep (i, k) {
        while (ptr < n and src[ptr].first >= dest[i].first) {
            cur.set(src[ptr].second);
            ptr++;
        }
        ok &= cur >> dest[i].second;
    }
    rep (i, n - k + 1) {
        if (ok[i]) {
            printf("%d\n", i + 1);
            return 0;
        }
    }
    printf("-1\n");
    return 0;
}
