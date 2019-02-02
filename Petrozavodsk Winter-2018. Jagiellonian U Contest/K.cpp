#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,k,dep[MAXN],son[MAXN],mx[MAXN];
ll ans;
vector<int> G[MAXN];
void dfs1(int v,int p,int d)
{
    dep[v]=d;mx[v]=d;
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i];
        if(to==p) continue;
        dfs1(to,v,d+1);mx[v]=max(mx[v],mx[to]);
        if(mx[to]>mx[son[v]]) son[v]=to;
    }
}
struct state
{
    deque<ll> *f;//number of vertices with depth i
    deque<ll> *g;//number of pairs with i needed to form a triple
    int sz()
    {
        return f->size();
    }
    void clear()
    {
        (*f).clear();(*g).clear();
    }
}s[MAXN];
state merge(state a,state b)
{
    int bs=b.sz();
    for(int i=0;i<bs+1;i++)
    {
        if(i!=0) ans+=(*(b.f))[i-1]*(*(a.g))[i];
        if(i!=0&&i<bs) ans+=(*(a.f))[i-1]*(*(b.g))[i];
    }
    for(int i=0;i<bs+1;i++) 
    {
        if(i!=0) (*(a.g))[i]+=(*(a.f))[i]*(*(b.f))[i-1];
        if(i!=0) (*(a.f))[i]+=(*(b.f))[i-1];
        if(i<bs-1) (*(a.g))[i]+=(*(b.g))[i+1];
    }
    return a;
}
void dfs2(int v,int p)
{
    if(!son[v])
    {
        s[v].f=new deque<ll>(1,1);
        s[v].g=new deque<ll>(1,0);
        return;
    }
    dfs2(son[v],v);
    s[v].f=new deque<ll>(0); s[v].g=new deque<ll>(0);
    swap(s[son[v]],s[v]);
    s[v].f->push_front(1);
    s[v].g->push_back(0);s[v].g->push_back(0); s[v].g->pop_front();
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i];
        if(to==p||to==son[v]) continue;
        dfs2(to,v);
        s[v]=merge(s[v],s[to]);
        s[to].clear();
    }
    ans+=(*(s[v].g))[0];
    /*printf("%lld\n",v);
    for(auto x:(*(s[v].f))) printf("%lld ",x); 
    puts("");
    for(auto x:(*(s[v].g))) printf("%lld ",x); 
    puts("");*/
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) G[i].clear();
        memset(son,0,sizeof(son));
        for(int i=0;i<n-1;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            G[u].push_back(v);G[v].push_back(u);
        }
        ans=0;
        dfs1(1,0,0);dfs2(1,0);
        for(int i=1;i<=n;i++) s[i].clear();
        printf("%lld\n",ans);
    }
    return 0;
}

