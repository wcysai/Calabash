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

#define left asehufaohr
#define right aehuofaqhgfeoa

int n, m;
int g[512][512];
int left[1 << 20], right[1 << 20], top[1 << 20], bottom[1 << 20], sz[1 << 20], cnt[1 << 20];
int tot;
vector<int> arr;

int main() {
    scanf("%d%d", &n, &m);
    rep (i, n) rep (j, m) {
        scanf("%d", &g[i][j]);
        arr.push_back(g[i][j]);
    }
    sort(range(arr));
    arr.erase(unique(range(arr)), arr.end());
    tot = arr.size();
    for (int i = 0; i < tot; i++) left[i] = top[i] = INT_MAX;
    rep (i, n) rep (j, m) {
        g[i][j] = lower_bound(range(arr), g[i][j]) - arr.begin();
        int val = g[i][j];
        left[val] = min(left[val], i);
        right[val] = max(right[val], i);
        top[val] = min(top[val], j);
        bottom[val] = max(bottom[val], j);
        sz[val]++;
    }
    /*
    rep (i, n) { rep (j, m) printf("%d ", g[i][j]); puts(""); }
    rep (i, tot) {
        _debug("%d:[%d,%d], [%d,%d]", i, left[i], right[i], top[i], bottom[i]);
    }
     */
    LL ans = 0;
    rep (id, tot) {
        for (int i = left[id]; i <= right[id]; i++) {
            for (int j = top[id]; j <= bottom[id]; j++) {
                cnt[g[i][j]]++;
            }
        }
        for (int i = left[id]; i <= right[id]; i++) {
            for (int j = top[id]; j <= bottom[id]; j++) {
                if (cnt[g[i][j]] == sz[g[i][j]]) ans++;
                cnt[g[i][j]] = 0;
            }
        }
    }
    cout << ans - tot << endl;
    return 0;
}

/*
3 4
 1 2 2 4
 1 1 1 4
 5 1 7 4
 */
