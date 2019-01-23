#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x)  begin(x), end(x)
#define PROBLEM "gems"

int n, k;
vector<int> pre[32];
int occ[32];
char str[1 << 20];
typedef long long LL;
int main() {
    freopen(PROBLEM ".in","r",stdin);
    freopen(PROBLEM ".out","w",stdout);
    scanf("%d%d", &n, &k);
    scanf("%s", str);
    rep (i, k) {
        char buf[8]; scanf("%s", buf);
        pre[buf[1]-'a'].push_back(buf[0]-'a');
    }
    rep (i, 26) {
        sort(range(pre[i]));
        pre[i].erase(unique(range(pre[i])), pre[i].end());
    }
    rep (i, n) str[i] -= 'a';
    LL ans = 0;
    rep (i, n) {
        for (int x : pre[str[i]]) ans += occ[x];
        occ[str[i]] ++;
    }
    cout << ans  << endl;
    return 0;
}
