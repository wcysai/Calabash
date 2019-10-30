#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
vector<int> G[MAXN];
int n,dp[MAXN][3];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
//0: can't extend
//1: can extend
//2: must extend
void dfs(int v,int p)
{
    vector<int> id,pre,suf;
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v);
        id.push_back(to);
    }
    if(!id.size()) 
    {
        dp[v][1]=1;
        //printf("%d %d %d %d\n",v,dp[v][0],dp[v][1],dp[v][2]); 
        return;
    }
    pre.resize(id.size()+1); suf.resize(id.size()+1);
    pre[0]=1;
    for(int i=0;i<(int)id.size();i++) 
    {
        int to=id[i];
        pre[i+1]=1LL*pre[i]*(dp[to][0]+dp[to][1])%MOD;
    }
    suf[(int)id.size()]=1;
    for(int i=(int)id.size()-1;i>=0;i--) 
    {
        int to=id[i];
        suf[i]=1LL*suf[i+1]*(dp[to][0]+dp[to][1])%MOD;
    }
    for(int i=0;i<(int)id.size();i++)
    {
        int cur=id[i];
        int res=1LL*(dp[cur][1]+dp[cur][2])*pre[i]%MOD*suf[i+1]%MOD;
        add(dp[v][2],res);
    }
    pre[0]=1;
    for(int i=0;i<(int)id.size();i++) 
    {
        int to=id[i];
        pre[i+1]=1LL*pre[i]*dp[to][0]%MOD;
    }
    suf[(int)id.size()]=1;
    for(int i=(int)id.size()-1;i>=0;i--) 
    {
        int to=id[i];
        suf[i]=1LL*suf[i+1]*dp[to][0]%MOD;
    }
    for(int i=0;i<(int)id.size();i++)
    {
        int cur=id[i];
        int res=1LL*(dp[cur][1]+dp[cur][2])*pre[i]%MOD*suf[i+1]%MOD;
        add(dp[v][1],res);
    }
    dec(dp[v][2],dp[v][1]);
    int tmp=1;
    for(int i=0;i<(int)id.size();i++) 
    {
        int to=id[i];
        tmp=1LL*tmp*dp[to][0]%MOD;
    }
    add(dp[v][1],tmp);
    vector<int> a,b;
    a.resize(id.size()); b.resize(id.size());
    for(int i=0;i<(int)id.size();i++)
    {
        int to=id[i];
        a[i]=dp[to][1]; add(a[i],dp[to][2]);
        b[i]=dp[to][1]; add(b[i],dp[to][0]);
    }
    suf[(int)id.size()]=1;
    for(int i=(int)id.size()-1;i>=0;i--) suf[i]=1LL*suf[i+1]*b[i]%MOD;
    pre[0]=0;
    tmp=1;
    for(int i=0;i<(int)id.size();i++)
    {
        pre[i+1]=1LL*tmp*a[i]%MOD;
        add(pre[i+1],1LL*pre[i]*b[i]%MOD);
        tmp=1LL*tmp*b[i]%MOD;   
    }
    for(int i=0;i<(int)id.size();i++) add(dp[v][0],1LL*pre[i]*a[i]%MOD*suf[i+1]%MOD);
    //printf("%d %d %d %d\n",v,dp[v][0],dp[v][1],dp[v][2]);
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
    dfs(1,0);
    int ans=0;
    add(ans,dp[1][0]); add(ans,dp[1][1]);
    printf("%d\n",ans);
    return 0;
}

