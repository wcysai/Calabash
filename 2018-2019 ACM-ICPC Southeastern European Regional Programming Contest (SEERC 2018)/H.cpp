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

int n, m;

bool pt[200005];
int u[200005], v[200005];

int main() {
    srand(time(NULL));
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        Rep (i, m) scanf("%d%d", u + i, v + i);
        vector<int> ans;
        do {
            ans.clear();
            Rep (i, n) pt[i] = rand() & 1;
            Rep (i, m) if (pt[u[i]] == 0 and pt[v[i]] == 1) ans.push_back(i);
        } while (ans.size() <= m / 4);
        printf("%d\n", int(ans.size()));
        for (int id : ans) printf("%d ", id);
        puts("");
    }

    return 0;
}
