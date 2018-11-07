#include <bits/stdc++.h>
using namespace std;
const int maxn = 100+5;
vector<int> E[maxn];
int dp[maxn][maxn];
int g[maxn];
int black[maxn];
int n,m;
inline void Max(int & x,int y){
    x = max(x,y);
}
void dfs(int u,int fa,int limit){
    if (black[u])
    dp[u][0] = 1;
    for (int v : E[u]){
        if (v == fa)continue;
        dfs(v,u,limit);
        memcpy(g,dp[u],sizeof dp[u]);
        for (int du = 0;du<=limit;du++)for (int dv = 0;dv <=limit;dv++){
            int max_len = du + dv +1;
            if (max_len >limit)break;
            int max_dep = max(du,dv+1);
            Max(g[max_dep],dp[u][du]+ dp[v][dv]);
        }
        memcpy(dp[u],g,sizeof dp[u]);
    }
    for (int i=0;i<=limit;i++){
        if (dp[u][i] >= m)throw 1;
    }
}
bool check(int limit){
    memset(dp,0,sizeof dp);
    try{
        dfs(1,0,limit);
        return 0;
    }catch(int err_code){
        return 1;
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++){
        scanf("%d",black+i);
    }
    for (int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        E[u].push_back(v);
        E[v].push_back(u);
    }
    if (m == 1){
        puts("0");
        return 0;
    }
    int l = 1,r = n;
    while (r-l>1){
        int mid = l+r >>1;
        if (check(mid)){
            r = mid;
        }else{
            l = mid;
        }
    }
    if (check(l)){
        printf("%d\n",l);
    }else{
        printf("%d\n",r);
    }
    return 0;
}
/*
6 3
 1 1 0 1 1 1
1 2
 1 3
 1 4
 3 5
 3 6


 9 4
 1 0 1 0 1 0 0 1 1
 1 2
 2 4
 2 3
 4 5
 1 6
 6 7
 6 8
 7 9
 */
