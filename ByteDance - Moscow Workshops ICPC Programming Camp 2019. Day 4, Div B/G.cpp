#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll n,m;
namespace ZL
{
    const ll N=10010,M=100010,inf=1000000000000LL; 
    struct edge
    {
        int u,v,w,use,id;
    }b[M],a[12001000];
    ll n,m,ans,pre[N],id[N],vis[N],root,In[N],h[N],len,way[M];
    void init(ll _n,ll _root)
    {
        n=_n; m=0; b[0].w=inf; root=_root; ans=0;
    }
    void add(ll u,ll v,ll w)
    {
        b[++m]=(edge){u,v,w,0,m};
        a[m]=b[m];
    }
    ll work()
    {
        len=m;
        for (;;)
        {
            for (ll i=1;i<=n;i++){pre[i]=0; In[i]=inf; id[i]=0; vis[i]=0; h[i]=0;}
            for (ll i=1;i<=m;i++)
                if (b[i].u!=b[i].v&&b[i].w<In[b[i].v])
                {
                    pre[b[i].v]=b[i].u; In[b[i].v]=b[i].w; h[b[i].v]=b[i].id;
                }
            for (ll i=1;i<=n;i++) if (pre[i]==0&&i!=root) return 0;
            ll cnt=0; In[root]=0;
            for (ll i=1;i<=n;i++)
            {
                if (i!=root) a[h[i]].use++; 
                ll now=i; ans+=In[i];
                while (vis[now]==0&&now!=root)
                {
                    vis[now]=i; now=pre[now];
                }
                if (now!=root&&vis[now]==i)
                {
                    cnt++; ll kk=now;
                    while (1)
                    {
                        id[now]=cnt; now=pre[now];
                        if (now==kk) break;
                    }
                }
            }
            if (cnt==0) return 1;
            for (ll i=1;i<=n;i++) if (id[i]==0) id[i]=++cnt;
            for (ll i=1;i<=m;i++)
            {
                ll k1=In[b[i].v]; ll k2=b[i].v;
                b[i].u=id[b[i].u]; b[i].v=id[b[i].v];       
                if (b[i].u!=b[i].v)
                {
                    b[i].w-=k1; a[++len].u=b[i].id; a[len].v=h[k2];
                    b[i].id=len;
                }
            }
            n=cnt;
            root=id[root];
        }
        return 1;
    }
    void getway()
    {
        for (ll i=1;i<=m;i++) way[i]=0;
        for (ll i=len;i>m;i--)
        {
            a[a[i].u].use+=a[i].use; a[a[i].v].use-=a[i].use;
        }
        for (ll i=1;i<=m;i++) way[i]=a[i].use;
    }
};
int main()
{
    scanf("%lld%lld",&n,&m);
    ZL::init(n,1);
    for(ll i=0;i<m;i++)
    {
        ll u,v,w;
        scanf("%lld%lld%lld",&u,&v,&w);
        w+=1e9;
        if(u!=v)ZL::add(u,v,w);
    }
    if(!ZL::work()) puts("NO");
    else
    {
        puts("YES");
        printf("%lld\n",ZL::ans-1LL*(n-1)*1000000000);
    }
    return 0;
}

