#include<bits/stdc++.h>
#define MAXN 3005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,k,a[MAXN];
vector<int> G[MAXN];
int sz[MAXN],dp[MAXN],fact[MAXN],invf[MAXN];
int choose[MAXN];
vector<int> cnt[MAXN];
bool has[MAXN];
int ans,res;
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
int comb(int n,int k)
{
    if(n<k) return 0;
    return 1LL*fact[n]*invf[k]%MOD*invf[n-k]%MOD;
}
void dfs(int v)
{
    sz[v]=1;
    dp[v]=1;
    for(auto to:G[v])
    {
        dfs(to);
        sz[v]+=sz[to];
        dp[v]=1LL*dp[to]*dp[v]%MOD;
    }
    int sum=sz[v]-1;
    for(auto to:G[v])
    {
        dp[v]=1LL*dp[v]*comb(sum,sz[to])%MOD;
        sum-=sz[to];
    }
}
int now;
void dfs2(int v,int p)
{
    if(now==v)
    {
        res=1LL*res*dp[v]%MOD;
        cnt[a[now]].push_back(sz[v]);
        return;
    }
    if(choose[v]==-1)
    {
        res=1LL*res*dp[v]%MOD;
        cnt[choose[p]].push_back(sz[v]);
        return;
    }
    for(auto to:G[v]) dfs2(to,v);
}
int solve()
{
    res=1;
    dfs2(1,0);
    int tot=0;
    for(int i=n;i>=1;i--)
    {
        if(!has[i]) tot++;
        for(auto x:cnt[i])
        {
            res=1LL*res*comb(tot,x)%MOD;
            tot-=x;
        }
        cnt[i].clear();
    }
    return res;
}
int main()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<=3000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[3000]=pow_mod(fact[3000],MOD-2);
    for(int i=2999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    scanf("%d",&T);
    for(int t=1;t<=T;t++)
    {
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=0;i<=n-1;i++)
            for(int j=k*i+1;j<=min(k*i+k,n-1);j++)
                G[i+1].push_back(j+1);
        dfs(1);
        ans=1;
        memset(choose,-1,sizeof(choose));
        choose[0]=1;
        memset(has,false,sizeof(has));
        for(int i=1;i<=n;i++)
        {
            now=-1;
            add(ans,solve());
            now=i;
            dec(ans,solve());
            has[a[i]]=true; choose[i]=a[i];
        }
        printf("Case #%d: %d\n",t,ans);
    }
    return 0;
}
