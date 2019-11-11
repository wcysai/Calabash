#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,h[MAXN];
int st[MAXN],t;
int fa[MAXN],ls[MAXN],rs[MAXN],root;
int sz[MAXN];
ll f[MAXN],g[MAXN];
void dfs(int v)
{
    sz[v]=1; f[v]=g[v]=0;
    ll tmp=0;
    if(ls[v]) {dfs(ls[v]); sz[v]+=sz[ls[v]]; f[v]+=f[ls[v]]; tmp+=g[ls[v]];}
    if(rs[v]) {dfs(rs[v]); sz[v]+=sz[rs[v]]; f[v]+=f[rs[v]]; tmp+=g[rs[v]];}
    ll need=1LL*sz[v]*(h[v]-h[fa[v]])-tmp;
    ll cnt=max(0LL,(need+m-1)/m);
    f[v]+=cnt; g[v]=1LL*cnt*m-need;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&h[i]);
    for(int i=1;i<=n;i++)
    {
        while(t&&h[st[t-1]]>h[i]) ls[i]=st[--t];
        if(t) rs[st[t-1]]=i;
        st[t++]=i;
    }
    for(int i=1;i<=n;i++) fa[ls[i]]=fa[rs[i]]=i;
    for(int i=1;i<=n;i++) if(!fa[i]) root=i;
    dfs(root);
    //for(int i=1;i<=n;i++) printf("%d %d %lld %lld %d %d %d\n",i,h[i],f[i],g[i],fa[i],ls[i],rs[i]);
    printf("%lld\n",f[root]);
    return 0;
}
