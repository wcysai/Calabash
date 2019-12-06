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
vector<int> G[MAXN];
int n,q,all,tot,counter;
ll alldep;
bool centroid[MAXN];
int pa[MAXN],dep[MAXN],sz[MAXN],wson[MAXN],top[MAXN],bot[MAXN],spos[MAXN],tpos[MAXN];
multiset<P> ms[MAXN];
struct segtree
{
    int sz[4*MAXN],len[4*MAXN],lazy[4*MAXN],leaf[MAXN];
    ll sum[4*MAXN];
    void pushup(int k)
    {
        sz[k]=max(sz[k*2],sz[k*2+1]);
        sum[k]=sum[k*2]+sum[k*2+1];
    }
    void add(int k,int v)
    {
        sz[k]+=v;  sum[k]+=len[k]*v;
        lazy[k]+=v;
    }
    void pushdown(int k)
    {
        if(!lazy[k]) return;
        add(k*2,lazy[k]); add(k*2+1,lazy[k]);
        lazy[k]=0;
    }
    void build(int k,int l,int r)
    {
        lazy[k]=0; len[k]=r-l+1;
        if(l==r) 
        {
            leaf[l]=k;
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    void update(int k,int l,int r,int x,int y,int v)
    {
        if(l>y||x>r) return;
        if(l>=x&&r<=y) 
        {
            add(k,v);
            return;
        }
        pushdown(k);
        int mid=(l+r)/2;
        update(k*2,l,mid,x,y,v); update(k*2+1,mid+1,r,x,y,v);
        pushup(k);
    }
    int query_max(int k,int l,int r,int x,int y)
    {
        if(l>y||x>r) return -1;
        if(l>=x&&r<=y) return sz[k];
        pushdown(k);
        int mid=(l+r)/2;
        return max(query_max(k*2,l,mid,x,y),query_max(k*2+1,mid+1,r,x,y));
    }
    ll query_sum(int k,int l,int r,int x,int y)
    {
        if(l>y||x>r) return 0;
        if(l>=x&&r<=y) return sum[k];
        pushdown(k);
        int mid=(l+r)/2;
        return query_sum(k*2,l,mid,x,y)+query_sum(k*2+1,mid+1,r,x,y);
    }
    int find_pos(int k,int l,int r,int x,int y)
    {
        if(l>y||x>r) return -1;
        if(l>=x&&r<=y)
        {
            if(2*sz[k]<all) return -1;
            if(l==r) return l;
            pushdown(k);
            int mid=(l+r)/2;
            if(2*sz[k*2+1]>=all) return find_pos(k*2+1,mid+1,r,x,y);
            else return find_pos(k*2,l,mid,x,y);
        }
        pushdown(k);
        int mid=(l+r)/2;
        int lans,rans=find_pos(k*2+1,mid+1,r,x,y);
        if(rans!=-1) return rans;
        else
        {
            lans=find_pos(k*2,l,mid,x,y);
            if(lans!=-1) return lans;
        }
        return -1;
    }
}seg;
void dfs1(int v,int p,int d)
{
    dep[v]=d; pa[v]=p; sz[v]=1;
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs1(to,v,d+1);
        if(sz[to]>sz[wson[v]]) wson[v]=to;
        sz[v]+=sz[to];
    }
}
void dfs2(int v,int p,int num)
{
    top[v]=num; bot[num]=v;
    spos[v]=++tot;
    tpos[tot]=v;
    if(wson[v]) dfs2(wson[v],v,num);
    for(auto to:G[v])
    {
        if(to==p||to==wson[v]) continue;
        ms[v].insert(P(0,to));
        dfs2(to,v,to);
    }
}
void init()
{
    tot=0;
    memset(wson,0,sizeof(wson));
    dfs1(1,1,1);
    dfs2(1,0,1);
    seg.build(1,1,n);
}
void update(int v,int delta)
{
    all+=delta;
    alldep+=delta*dep[v];
    while(top[v])
    {
        if(top[v]!=1) 
        {
            int s=seg.query_max(1,1,n,spos[top[v]],spos[top[v]]);
            ms[pa[top[v]]].erase(ms[pa[top[v]]].find(P(s,top[v])));
            ms[pa[top[v]]].insert(P(s+delta,top[v]));
        }   
        seg.update(1,1,n,spos[top[v]],spos[v],delta);
        if(top[v]==1) break;
        v=pa[top[v]];
    }
}
int get_pos()
{
    int v=1,sum=0;
    do
    {
        int maxi=(ms[v].size()?(*(--ms[v].end())).F:0);
        if(maxi*2>=all) v=(*(--ms[v].end())).S;
        else if(wson[v])
        {
            counter=0;
            int nxt=tpos[seg.find_pos(1,1,n,spos[v],spos[bot[top[v]]])];
            if(v==nxt) break; else v=nxt;
        }
        else break;
    }while(true);
    return v;
}
ll get_ans(int v)
{
    ll ans=alldep+1LL*dep[v]*all;
    while(top[v])
    {
        ans-=2*seg.query_sum(1,1,n,spos[top[v]],spos[v]);
        if(top[v]==1) break;
        v=pa[top[v]];
    }
    return ans;
}
string str;
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v); G[v].push_back(u);
    }
    init();
    scanf("%d",&q);
    for(int i=0;i<q;i++)
    {
        cin>>str;
        int v;
        scanf("%d",&v);
        if(str[0]=='+') update(v,1);
        else update(v,-1);
        int pos=get_pos();
        printf("%lld\n",get_ans(pos));
    }
    return 0;
}