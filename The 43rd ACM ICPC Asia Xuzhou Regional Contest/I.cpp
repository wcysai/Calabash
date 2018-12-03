#include <bits/stdc++.h>
using namespace std;

#ifdef __LOCAL_DEBUG__
# define _debug(fmt, ...) fprintf(stderr, "\033[94m%s: " fmt "\n\033[0m", \
    __func__, ##__VA_ARGS__)
#else 
# define _debug(...) ((void) 0)
#endif
#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x) (x).begin(), (x).end()
typedef long long LL;
typedef unsigned long long ULL;

int n, k, q;
int u[12], v[12];
int p[64];
int ans;

void dfs(int rem) {
    if (rem == 0) {
        ans++;
        return;
    }
    if (p[u[rem]] > p[v[rem]]) return;
    dfs(rem - 1);
    swap(p[u[rem]], p[v[rem]]);
    dfs(rem - 1);
    swap(p[u[rem]], p[v[rem]]);
}

void work() {
    scanf("%d%d%d", &n, &k, &q);
    ans = 0;
    Rep (i, k) scanf("%d%d", u + i, v + i);    
    
    Rep (i, n) p[i] = i;
    dfs(k);
    
    for (int i = 1; i < n; i++) {
        swap(p[i], p[i+1]);
        dfs(k);
        swap(p[i], p[i+1]);
    }

    for (int i = 1; i < n; i++) {
        for (int j = i + 3; j <= n + 1; j++) {
            Rep (i, n) p[i] = i;
            rotate(p + i, p + i + 1, p + j);
            dfs(k);
            Rep (i, n) p[i] = i;
            rotate(p + i, p + j - 1, p + j);
            dfs(k);
        }
    }

    printf("%d\n", ans % q);
}

int main() {
    int T; scanf("%d", &T);
    while (T--) work();
    return 0;
}
