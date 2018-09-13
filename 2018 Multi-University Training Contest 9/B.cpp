#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e3+100;
typedef long long LL;
char a[maxn][maxn];
typedef pair<int,int> pii;
const LL MOD = 998244353;
int n,m,k;
struct BIT{
    LL val[maxn];
    void clear(){
        for (int i=0;i<=n;i++){
            val[i] = 0;
        }
    }
    int lowbit(int x){
        return x&(-x);
    }
    void add(int x,LL delta){
        while (x<=n){
            val[x] = (val[x] + delta)%MOD;
            x += lowbit(x);
        }
    }
    LL query(int x){
        LL ret = 0;
        while (x){
            ret = (ret+val[x])%MOD;
            x -= lowbit(x);
        }
        return ret;
    }
    LL query(int L,int R){
        return (query(R) - query(L-1)+MOD)%MOD;
    }
};
LL gg[maxn][maxn];
LL g[maxn][maxn];
LL dp[maxn][maxn];
vector<pii> seg[maxn];
void pre_proc(int x){
    seg[x].clear();
    for (int i=1;i<=m;){
        int j=i;
        while (j <=m && a[x][j] == a[x][i]) j ++;
        seg[x].push_back({i,j-1});
        i = j;
    }
}
inline void add(LL &x,LL y){
    x = (x+y+MOD)%MOD;
}
void work(int x,int y){
    int L = max(1,y-k);
    int R = min(m,y+k);
    add(dp[x][y],gg[x-1][R] - gg[x-1][L-1]);
    add(dp[x][y],g[x-1][R]-g[x-1][L-1]);
    if (a[x-1][L] == a[x-1][L-1]){
        add(dp[x][y],dp[x-1][L] - g[x-1][L] + g[x-1][L-1]);
    }
    int preR = min(m,y+k-1);
    if (R != preR){
        if (a[x-1][R] == a[x-1][preR]){
            g[x][y] = g[x-1][R] - g[x-1][R-1];
        }else{
            g[x][y] = dp[x-1][R] ;
        }
    }
    if (a[x][y] != a[x][y-1]){
        g[x][y] = g[x][y-1];
    }else{
        add(g[x][y],g[x][y-1]);
    }
    gg[x][y] = gg[x][y-1];
    if (a[x][y] != a[x][y-1]){
        add(gg[x][y],dp[x][y] - (g[x][y] - g[x][y-1]));
    }
}
void solve(){
    scanf("%d%d%d",&n,&m,&k);
    for (int i=1;i<=n;i++){
        scanf("%s",&a[i][1]);
       // pre_proc(i);
    }
    for (int i=1;i<=n;i++){
        for (int j=1;j<=m;j++){
            gg[i][j] = g[i][j] = dp[i][j] = 0;
        }
    }
    for (int j=1;j<=m;j++){
        dp[1][j] = 1;
        g[1][j] = 0;
        gg[1][j] = gg[1][j-1];
        if (a[1][j] != a[1][j-1]){
            gg[1][j] += dp[1][j] - g[1][j];
        }
    }
    for (int i=2;i<=n;i++){
        for (int j=1;j<=m;j++){
            work(i,j);
        }

    }
    LL ans =0;
    for (int i=1;i<=m;i++){
        if (a[n][i] == a[n][i-1]){
            add(ans,g[n][i] - g[n][i-1]);
        }else{
            add(ans,dp[n][i]);
        }
    }

    printf("%lld\n",ans);
}
int main(){
    int T;
    for (scanf("%d",&T);T;T--){
        solve();
    }
    return 0;
}
