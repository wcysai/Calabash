#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__);
#else
#define _debug(...) ((void) 0)
#endif
typedef long long LL;
typedef unsigned long long ULL; 

int m, n;
int p[1 << 18], cnt[1 << 18];

const LL mod = 1'000'000'007;
LL ans = 1;

int disjoint(int *l1, int *r1, int *l2, int *r2) {
    for (int *ptr = l1; ptr != r1; ptr++) cnt[*ptr]++;
    bool flag = true;
    for (int *ptr = l2; ptr != r2; ptr++) flag &= (cnt[*ptr] == 0);
    for (int *ptr = l1; ptr != r1; ptr++) cnt[*ptr] = 0;
    return flag;
}

void dc(int l, int r) {
    if (l == r - 1) return;
    int mid = (l + r) / 2;
    if (equal(p + l, p + mid, p + mid)) {
        ans = ans * 2 % mod;
        dc(l, mid);
    } else {
        if (!disjoint(p + l, p + mid, p + mid, p + r)) ans = 0;
        dc(l, mid); dc(mid, r);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    rep (i, (1 << n)) scanf("%d", p + i), cnt[--p[i]]++;
    if (count(cnt, cnt + m, 0)) {
        puts("0");
        return 0;
    }
    rep (i, (1 << n)) cnt[p[i]] = 0; 
    dc(0, 1 << n);
    cout << ans << endl;
    return 0;
}
