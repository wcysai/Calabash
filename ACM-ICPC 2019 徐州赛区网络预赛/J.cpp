
#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,d[MAXN],dp[MAXN],dis;
vector<int> G[MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
void dfs(int v,int p,int dd)
{
    d[v]=dd;
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v,dd+1);
    }
}
void dfs2(int v,int p)
{
    if(d[v]==dis) dp[v]=1; else dp[v]=0;
    int cnt=0;
    int sum=0;
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs2(to,v);
        add(sum,1); dec(sum,dp[to]);
        add(cnt,1);
    }
    if(dp[v]) return;
    dp[v]=pow_mod(sum,cnt);
    cnt=pow_mod(cnt,cnt);
    dp[v]=1LL*dp[v]*pow_mod(cnt,MOD-2)%MOD;
    dp[v]=1-dp[v]; if(dp[v]<0) dp[v]+=MOD;
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v); G[v].push_back(u);
    }
    dfs(1,0,1);
    dis=0;
    for(int i=1;i<=n;i++) dis=max(dis,d[i]);
    dfs2(1,0);
    printf("%d\n",dp[1]);
    return 0;
}
