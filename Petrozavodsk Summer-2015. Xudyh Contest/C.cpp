#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define MAXM 200005
#define INF 1000000000
#define MOD 1000000007
#define lc t[x].ch[0]
#define rc t[x].ch[1]
#define pa t[x].fa
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n;
ll ans;
vector<int> pool;
P edges[MAXN];
namespace lct
{
    struct meow{int ch[2],fa,rev,mx,mxp,w;} t[2*MAXN];
    inline int wh(int x) {return t[pa].ch[1]==x;}
    inline int isr(int x) {return t[pa].ch[0]!=x&&t[pa].ch[1]!=x;}
    inline void update(int x)
    {
        t[x].mx=t[x].w; t[x].mxp=x;
        if(t[lc].mx<t[x].mx) {t[x].mx=t[lc].mx; t[x].mxp=t[lc].mxp;}
        if(t[rc].mx<t[x].mx) {t[x].mx=t[rc].mx; t[x].mxp=t[rc].mxp;}
    }
    inline void rever(int x) {t[x].rev^=1; swap(lc,rc);}
    inline void pushdown(int x)
    {
        if(t[x].rev)
        {
            if(lc) rever(lc);
            if(rc) rever(rc);
            t[x].rev=0;
        }
    }
    void pd(int x) {if(!isr(x)) pd(pa); pushdown(x);}
    inline void rotate(int x)
    {
        int f=t[x].fa,g=t[f].fa,c=wh(x);
        if(!isr(f)) t[g].ch[wh(f)]=x;
        t[x].fa=g;
        t[f].ch[c]=t[x].ch[c^1]; t[t[f].ch[c]].fa=f;
        t[x].ch[c^1]=f; t[f].fa=x;
        update(f); update(x);
    }
    inline void splay(int x)
    {
        pd(x);
        for(;!isr(x);rotate(x))
        if(!isr(pa)) rotate(wh(pa)==wh(x)?pa:x);
    }
    inline void access(int x)
    {
        for(int y=0;x;y=x,x=pa) splay(x),rc=y,update(x);
    }
    inline void maker(int x)
    {
        access(x); splay(x); rever(x);
    }
    inline int findr(int x)
    {
        access(x); splay(x);
        while(lc) pushdown(x),x=lc;
        return x;
    }
    inline void link(int x,int y)
    {
        maker(x);
        if(findr(y)!=x) t[x].fa=y;
    }
    inline void cut(int x,int y)
    {
        maker(x);
        if(findr(y)==x&&t[x].fa==y&&t[y].ch[0]==x&&!t[y].ch[1])
        {
            t[x].fa=t[y].ch[0]=0;
            update(y);
        }
    }
    inline void split(int x,int y)
    {
        maker(x); access(y); splay(y);
    }
}using lct::findr;
int query[MAXN];
int p[MAXN],r[MAXN];
void init(int n)
{
    for(int i=1;i<=n;i++)
    {
        p[i]=i;
        r[i]=0;
    }
}
int find(int x)
{
    if(p[x]==x) return x;
    return p[x]=find(p[x]);
}
void unite(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x==y) return;
    if(r[x]<r[y]) p[x]=y;
    else
    {
        p[y]=x;
        if(r[x]==r[y]) r[x]++;
    }
}
bool same(int x,int y)
{
    return find(x)==find(y);
}
vector<int> divisors[MAXN];
int get_id()
{
    assert(pool.size());
    int x=pool.back();
    pool.pop_back();
    return x;
}
void add_edge(int u,int v,int w)
{
    if(!same(u,v))
    {
        int id=get_id();
        edges[id]=P(u,v);
        lct::t[100000+id].w=lct::t[100000+id].mx=w;
        unite(u,v);
        lct::link(u,100000+id); lct::link(v,100000+id); ans+=w;
        lct::splay(100000+id);
    }
    else
    {
        lct::split(u,v);
        if(w>lct::t[v].mx)
        {
            ans-=lct::t[v].mx; ans+=w;
            int p=lct::t[v].mxp;
            lct::cut(p,edges[p-100000].F); lct::cut(p,edges[p-100000].S);
            lct::t[p].w=lct::t[p].mx=w;
            lct::link(u,p); lct::link(v,p);
            edges[p-100000]=P(u,v);
        }
    }
}
ll res[MAXN];
int main()
{
    for(int i=1;i<=100000;i++)
        for(int j=2*i;j<=100000;j+=i)
            divisors[j].push_back(i);
    for(int i=1;i<=100000-1;i++) pool.push_back(i);
    for(int i=0;i<=199999;i++)
    {
        lct::t[i].w=lct::t[i].mx=100001;
        lct::t[i].mxp=i;
    }
    scanf("%d",&T);
    for(int t=1;t<=T;t++)
    {
        int x;
        scanf("%d",&x);
        query[x]=t;
    }
    init(100000);
    ans=0;
    for(int i=1;i<=100000;i++)
    {
        for(auto j:divisors[i]) add_edge(i,j,j);
        if(query[i]!=0) res[query[i]]=ans;
    }
    for(int i=1;i<=T;i++) printf("%lld\n",res[i]);
    return 0;
}
