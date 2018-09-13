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

int ans;

pair<int, int> getone() {
    static char buf[100005];
    scanf("%s", buf);
    int r = 0, stk = 0;
    for (int i = 0; buf[i]; i++) {
        if (buf[i] == '(') {
            stk++;
        } else if (buf[i] == ')') {
            if (stk) {
                stk--;
                ans += 2;
            } else {
                r++;
            }
        }
    }
//  _debug("ans=%d", ans);
    return {r,stk};
}

int n;
int calc(vector<pair<int,int>> &p){
    int Ans =0;
    int stk = 0;
    for (auto& l : p) {
       // cout<<"right:"<<l.first<<" left:"<<l.second<<endl;
        Ans += 2 * min(stk, l.first);
        stk -= min(stk, l.first);
        stk += l.second;
    }
    return Ans;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        ans = 0;
        vector<pair<int, int>> p(n);
        rep (i, n) { p[i] = getone(); }
        sort(range(p), [] (pair<int, int> l, pair<int, int> r) -> bool {
            int lfirst = min(l.second,r.first);
            int rfirst = min(r.second,l.first);
            if (lfirst!=rfirst){
                return lfirst>rfirst;
            }else{
                if (l.first!=r.first){
                    return l.first<r.first;
                }else{
                    return l.second>r.second;
                }
            }
        });
        int X = ans;
        ans = max(ans,calc(p)+X);
        printf("%d\n", ans);
    }
    return 0;
}
