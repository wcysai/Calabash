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

int k, n;
int a[100005], b[100005];
vector<int> chosen[100005];

int main() {
    scanf("%d%d", &n, &k);
    rep (i, n) scanf("%d", a + i);
    rep (i, n) scanf("%d", b + i);
    int done = 0;
    rep (i, n) {
        chosen[a[i]].push_back(b[i]); 
    }
    vector<int> other;
    Rep (i, k) {
        if (chosen[i].size()) {
            sort(range(chosen[i]));
            done++;
            other.insert(other.end(), chosen[i].begin(), chosen[i].end() - 1);
        }
    }
    if (done >= k) {
        printf("0\n");
    } else {
        sort(range(other));
        LL ans = 0;
        rep (i, k - done) ans += other[i];
        printf("%lld\n", ans);
    }
    return 0;
}
