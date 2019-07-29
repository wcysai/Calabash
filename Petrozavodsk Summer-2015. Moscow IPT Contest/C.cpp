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
int n,m;
int x[MAXN],l[MAXN],r[MAXN],y[MAXN];
vector<int> v;
int id[4*MAXN];
int dis[8*MAXN];
struct edge
{
    int to,cost;
};
vector<edge> G[8*MAXN];
void add_edge(int u,int v,int cost)
{
    G[u].push_back((edge){v,cost});
}
void build(int k,int l,int r)
{
    if(l==r) {id[l]=k; return;}
    int mid=(l+r)/2;
    build(k*2,l,mid);build(k*2+1,mid+1,r);
    add_edge(k,k*2,0);add_edge(k,k*2+1,0);
}
void Add_edge(int u,int k,int l,int r,int x,int y,int cost)
{
    if(x>r||l>y) return;
    if(l>=x&&r<=y) {add_edge(id[u],k,cost); return;}
    int mid=(l+r)/2;
    Add_edge(u,k*2,l,mid,x,y,cost);Add_edge(u,k*2+1,mid+1,r,x,y,cost);
}
deque<P> deq;
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d%d%d",&x[i],&l[i],&r[i]);
        v.push_back(x[i]);
    }
    scanf("%d",&m);
    for(int i=0;i<m;i++) {scanf("%d",&y[i]); v.push_back(y[i]);}
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    int sz=(int)v.size();
    build(1,1,sz);
    for(int i=0;i<n;i++)
    {
        int now=lower_bound(v.begin(),v.end(),x[i])-v.begin()+1;
        int lb=lower_bound(v.begin(),v.end(),x[i]+l[i])-v.begin()+1;
        int rb=upper_bound(v.begin(),v.end(),x[i]+r[i])-v.begin();
        Add_edge(now,1,1,sz,lb,rb,1);
        rb=upper_bound(v.begin(),v.end(),x[i]-l[i])-v.begin();
        lb=lower_bound(v.begin(),v.end(),x[i]-r[i])-v.begin()+1;
        Add_edge(now,1,1,sz,lb,rb,1);
    }
    int pos=lower_bound(v.begin(),v.end(),x[0])-v.begin()+1;
    int s=id[pos];
    for(int i=1;i<=4*sz;i++) dis[i]=INF;
    dis[s]=0;
    deq.push_front(P(s,0));
    while(deq.size())
    {
        auto p=deq.front();deq.pop_front();
        int v=p.F,d=p.S;
        if(d>dis[v]) continue;
        for(auto e:G[v])
        {
            if(dis[e.to]<=d+e.cost) continue;
            dis[e.to]=d+e.cost;
            if(e.cost==0) deq.push_front(P(e.to,dis[e.to]));
            else deq.push_back(P(e.to,dis[e.to]));
        }
    }
    for(int i=0;i<m;i++)
    {
        int pos=lower_bound(v.begin(),v.end(),y[i])-v.begin()+1;
        int v=id[pos];
        if(dis[v]==INF) printf("%d%c",-1,i==m-1?'\n':' ');
        else printf("%d%c",dis[v],i==m-1?'\n':' ');
    }
    return 0;
}
