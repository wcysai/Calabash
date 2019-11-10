#include<bits/stdc++.h>
#define MAXN 21
#define MAXM (1<<20)
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int m,tot;
string str;
map<char,int> mp;
vector<int> G[MAXN];
vector<int> GG[MAXN];
set<P> s;
int dfn[MAXN],low[MAXN],sta[MAXN],vis[MAXN],cmp[MAXN],cnt,t,tt;
int res[MAXN];
int w[MAXN][MAXN];
int mask[MAXN];
ll dp[MAXM],allmask[MAXM];
vector<P> edges;
int lowbit(int x)
{
    return x&-x;
}
int getid(char ch)
{
    if(mp.find(ch)==mp.end()) mp[ch]=++tot;
    return mp[ch];
}
void add_edge(int u,int v)
{
    G[u].push_back(v);
    edges.push_back(P(u,v));
}
void dfs(int v)
{
    dfn[v]=low[v]=++tt;
    vis[v]=1;
    sta[t++]=v;
    for(auto to:G[v])
    {
        if(!vis[to])
        {
            dfs(to);
            low[v]=min(low[v],low[to]);
        }
        else if(vis[to]==1) low[v]=min(low[v],dfn[to]);
    }
    if(dfn[v]==low[v])
    {
        int u;
        do
        {
            u=sta[t-1]; t--;
            cmp[u]=cnt;
            vis[u]=2;
        }while(u!=v);
        cnt++;
    }
}
void tarjan()
{
    t=tt=cnt=0;
    memset(vis,0,sizeof(vis));
    for(int i=1;i<=tot;i++) if(!dfn[i]) dfs(i);
}
ll fact[21];
int main()
{
    freopen("fygon20.in","r",stdin);
    freopen("fygon20.out","w",stdout);
    fact[0]=1;
    for(int i=1;i<=20;i++) fact[i]=fact[i-1]*i;
    scanf("%d ",&m);
    tot=0;
    for(int i=0;i<m;i++)
    {
        getline(cin,str);
        bool islag=false;
        int st=0;
        for(int j=0;j<(int)str.size();j++)
        {
            if(str[j]!=' ')
            {
                st=j;
                if(str[j]=='l') islag=true;
                break;
            }
        }
        if(islag) break;
        int id=getid(str[st+4]);
        if(str[st+15]!='1')
        {
            int toid=getid(str[st+15]);
            add_edge(id,toid);
        }
        if(str[st+18]!='n')
        {
            int fromid=getid(str[st+18]);
            add_edge(fromid,id);
        }
    }
    tarjan();
    printf("%d ",cnt);
    for(auto p:edges)
    {
        int x=cmp[p.F],y=cmp[p.S];
        if(x==y) continue;
        if(!s.count(P(x,y)))
        {
            s.insert(P(x,y));
            GG[x].push_back(y);
            w[x][y]=1;
        }
    }
    for(int i=0;i<cnt;i++) w[i][i]=1;
    for(int k=0;k<cnt;k++)
        for(int i=0;i<cnt;i++)
            for(int j=0;j<cnt;j++)
                w[i][j]|=(w[i][k]&w[k][j]);
    for(int i=0;i<cnt;i++)
    {
        mask[i]=0;
        for(int j=0;j<cnt;j++) if(w[i][j]) mask[i]|=(1<<j);
    }
    dp[0]=1;
    for(int msk=0;msk<(1<<cnt);msk++)
    {
        for(int i=0;i<cnt;i++)
        {
            allmask[msk|(1<<i)]|=mask[i];
            if(!(allmask[msk]&(1<<i)))
            {
                dp[msk|(1<<i)]+=dp[msk];
            }
        }
    }
    ll p=dp[(1<<cnt)-1],q=fact[cnt],g=__gcd(p,q);
    p/=g; q/=g;
    printf("%lld/%lld\n",p,q);
    return 0;
}
