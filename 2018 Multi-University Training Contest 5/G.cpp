#include <bits/stdc++.h>
#pragma optimize("-O3")
using namespace std;
#define rep(i,a,n) for(int i=(a);i<(n);++i)
typedef long long ll;
unsigned x, y, z, w;
int n, m;
inline unsigned int gen() {
    x = x ^ (x << 11);
    x = x ^ (x >> 4);
    x = x ^ (x << 5);
    x = x ^ (x >> 14);
    w = x ^ (y ^ z);
    x = y;
    y = z;
    z = w;
    return z;
}
const int md = 1 << 30;
const int N = 1e5+100;
ll mi[N << 2];
int L, R, v;
void update(int l, int r, int rt) {
    if (mi[rt] >= v)
        return;
    if (l == r) {
        mi[rt] = v;
        return;
    }
    int mid = l + r >> 1;
    if (L <= mid)
        update(l, mid, rt << 1);
    if (R > mid)
        update(mid + 1, r, rt << 1 | 1);
    mi[rt] = min(mi[rt << 1], mi[rt << 1 | 1]);
}
int pos;
int query(int l, int r, int rt) {
    if (l == r)
        return mi[rt];
    int mid = l + r >> 1;
    if (pos <= mid)
        return query(l, mid, rt << 1);
    else
        return query(mid + 1, r, rt << 1 | 1);
}
void solve(){

    scanf("%d%d",&n,&m);
    scanf("%u%u%u", &x, &y, &z);
    memset(mi, 0, sizeof(mi));
    rep(i, 0, m) {
        L = gen() % n + 1;
        R = gen() % n + 1;
        v = gen() % md;
        if(L > R){
            swap(L, R);
        }
        update(1,n,1);
    }
    long long ans = 0;
    for(int i = 1; i <= n; i++) {
        pos = i;
        ans ^= 1ll*i*query(1,n,1);
    }
    printf("%lld\n",ans);
}
int main() {
    int T;
    for (scanf("%d", &T); T;T--) {
        solve();
    }
    return 0;
}
