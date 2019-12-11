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
 
int cnt = 0;
int fa[100005], cost[100005];
 
int construct(int k, int rt) {
    _debug("%d %d", k, rt);
    int sqrtk = sqrt(k);
    if (k == 1) {
        fa[++cnt] = rt;
        cost[cnt] = 1;
        return 1;
    } else if (sqrtk * sqrtk == k and rt > 0) {
        return construct(sqrtk, rt) + construct(sqrtk, rt);
    } else {
        fa[++cnt] = rt;
        int ccnt = cnt;
        return cost[ccnt] = construct(k - 1, ccnt);
    }
}
 
int main() { 
    int k; scanf("%d", &k);
    if (k == 1) {
        puts("2");
        puts("1");
        puts("1 2");
        return 0;
    }
    construct(k, 0);
    printf("%d\n", cnt);
    for (int i = 2 ; i <= cnt; i++) printf("%d ", fa[i]); puts("");
    Rep (i, cnt) printf("%d ", cost[i]); puts("");
    return 0;
}