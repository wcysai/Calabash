#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 2005
#define MAXM 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
mt19937 wcy(time(NULL));
ll myrand()
{
    ll now=0;
    for(int i=0;i<4;i++)
    {
        ll w=wcy()%(1LL<<16);
        now=(now<<16)|w;
    }
    return now;
}
int n,m;
struct edge
{
    int to,id;
};
vector<edge> G[MAXN];
bool vis[MAXN];
int fa[MAXN];
ll save[MAXN];
ll val[MAXM];
bool tree[MAXM];
int u[MAXM],v[MAXM];
void dfs(int v,int p)
{
    vis[v]=true;fa[v]=p;
    for(auto e:G[v])
    {
        if(p==e.to) continue;
        if(!vis[e.to]) 
        {
            tree[e.id]=true;
            dfs(e.to,v);
        }
    }
}
void dfs2(int v,int p)
{
    vis[v]=true;
    for(auto e:G[v])
    {
        if(p==e.to) continue;
        if(vis[e.to]) continue;
        dfs2(e.to,v);
        val[e.id]^=save[e.to];
        save[v]^=save[e.to];
    }
}
unordered_map <ll,int> mp;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        scanf("%d%d",&u[i],&v[i]);
        G[u[i]].push_back((edge){v[i],i});G[v[i]].push_back((edge){u[i],i});
    }
    memset(vis,false,sizeof(vis));
    dfs(1,0);
    for(int i=0;i<m;i++)
    {
        if(!tree[i])
        {
            ll w=myrand();
            val[i]^=w;
            save[u[i]]^=w;save[v[i]]^=w;
        }
    }
    memset(vis,false,sizeof(vis));
    dfs2(1,0);
    for(int i=0;i<m;i++) mp[val[i]]++;
    ll ans=0;
    for(auto v:mp)
    {
        ans+=1LL*v.S*(v.S-1)/2;
        if(v.F==0) ans+=v.S*(m-v.S);
    }
    printf("%lld\n",ans);
    return 0;
}

