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
int a[1 << 20], b[1 << 20];
const int maxn = 1 << 20;
 
struct st {
    pair<int, int> st[maxn][30];
     
    void init(int n, int a[]) {
        int l = log2(n);
        rep (i, n) st[i][0] = {a[i], i};
        rep (j, l) rep (i, 1+n-(1<<j))
            st[i][j+1] = min(st[i][j], st[i+(1<<j)][j]);
    }
 
    int rmq(int l, int r) {
        int k = log2(r - l);
        return min(st[l][k], st[r-(1<<k)][k]).second;
    }
} sa, sb;
 
bool check(int l, int r) {
    if (l >= r) return true;
    int m1 = sa.rmq(l, r), m2 = sb.rmq(l, r);
    if (m1 != m2) return false;
    return check(l, m1) && check(m1 + 1, r);
}
 
int main() {
    while (~scanf("%d", &n)) {
        rep (i, n) scanf("%d", a + i);
        rep (i, n) scanf("%d", b + i);
        sa.init(n, a); sb.init(n, b);
        int l = 1, r = n + 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (check(0, mid)) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        printf("%d\n", r - 1);
    }
    return 0;
}
