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
LL m;
LL a[100005], b[100005];
LL pa[100005], pb[100005]; 
int cnt[100005];
pair<LL, int> sufmax[1000005];

int main() {
    scanf("%d%lld", &n, &m);
    Rep (i, n) scanf("%lld", a+i);
    Rep (i, n) scanf("%lld", b+i);
    partial_sum(a, a+1+n, pa);
    partial_sum(b, b+1+n, pb);
    {
        int nd = 0;
        while (nd < n and pa[nd+1] <= m) nd++;
        n = nd;
    }
    _debug("nd=%d", n);
    sufmax[n+1] = {0, 0};
    for (int i = n; i > 0; i--) { 
        sufmax[i] = max(sufmax[i+1], make_pair(b[i], i));
        _debug("i=%d, sufmax=%lld", i, sufmax[i].first);
    }

    LL delay = 0;
    vector<LL> ans;
    int bptr = 1;
    Rep (i, n) {
        for (int i = 0; i < cnt[bptr]; i++) {
            ans.push_back(pb[bptr] + delay);
            delay += b[bptr];
        } 
        cnt[bptr] = 0;
        while (bptr <= n and pb[bptr] + delay < pa[i]) {
            bptr++; if (bptr > n) break;
            for (int i = 0; i < cnt[bptr]; i++) {
                ans.push_back(pb[bptr] + delay);
                delay += b[bptr];
            }
            cnt[bptr] = 0;
        }
        int x = sufmax[bptr].second;
        _debug("bptr=%d, i=%d, delay=%lld, decison=%d", bptr, i, delay, x);
        if (x) cnt[x]++;
    }
    
    for (int i = 0; i < cnt[bptr]; i++) {
        ans.push_back(pb[bptr] + delay);
        delay += b[bptr];
    } 
    cnt[bptr] = 0;
    while (bptr < n) {
        bptr++;
        for (int i = 0; i < cnt[bptr]; i++) {
            ans.push_back(pb[bptr] + delay);
            delay += b[bptr];
        }
        cnt[bptr] = 0;
    } 
    
    _debug("delay=%lld", delay);
    if (delay + pb[n] > m) {
        vector<LL> ans2;
        for (LL x : ans) 
            if (x <= m) ans2.push_back(x);
        printf("%d\n", int(ans2.size()));
        for (LL t : ans2) 
            printf("%lld ", t);
        puts("");
    } else {
        cout << -1 << endl;
    }
    return 0;
}
close
