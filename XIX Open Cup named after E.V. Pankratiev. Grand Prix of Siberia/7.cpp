#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 300005
#define MAXQ 100005
#define MAXM 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
int T,n,k,x,y;
char str[2];
vector<P> edges[4*MAXM];
P ask[MAXM];
int W[MAXQ],M[MAXQ];
int p[MAXN],r[MAXN],sz[MAXN];
bool ans[MAXM];
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};
int num;
struct update
{
    int x,y;
    bool addrk;
};
update st[MAXN];
int t;
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
   while(p[x]!=x) x=p[x];
   return x;
}
bool unite(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x==y) return false;
    num--;
    if(r[x]<r[y]) 
    {
        p[x]=y; 
        st[t++]=(update){x,y,false};
    }
    else
    {
        p[y]=x;
        st[t++]=(update){y,x,r[x]==r[y]};
        if(r[x]==r[y]) r[x]++;
    }
    return true;
}
void undo()
{
    assert(t);
    int x=st[t-1].x,y=st[t-1].y;
    //printf("undo %d %d %d\n",x,y,st[t-1].addrk);
    p[x]=x;p[y]=y;
    if(st[t-1].addrk) r[y]--;
    t--;num++;
}
bool same(int x,int y)
{
    return find(x)==find(y);
}
void add_edge(int k,int l,int r,int x,int y,int u,int v)
{
    if(x>r||l>y) return;
    if(l>=x&&r<=y)
    {
        edges[k].push_back(P(u,v));
        return;
    }
    int mid=(l+r)/2;
    add_edge(k*2,l,mid,x,y,u,v);add_edge(k*2+1,mid+1,r,x,y,u,v);
}
void solve(int k,int l,int r)
{
    if(l>r) return;
    int cnt=0;
    for(auto e:edges[k]) if(unite(e.F,e.S)) cnt++;  
    if(l==r)
    {
        if(ask[l].F) ans[l]=!same(ask[l].F,ask[l].S);
        for(int i=0;i<cnt;i++) undo();
        return;
    }
    int mid=(l+r)/2;
    solve(k*2,l,mid);solve(k*2+1,mid+1,r);
    //printf("cnt %d %d %d\n",l,r,cnt);
    for(int i=0;i<cnt;i++) undo();
}
struct pe//pe for potential edge
{
    int u,v,l,r;
};
vector<pe> save;
map<P,int> id,mp;
int main()
{
    scanf("%d",&n);
    init(n);
    k=1;
    for(int i=1;i<=n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        id[P(x,y)]=i;
        for(int j=0;j<4;j++)
        {
            if(id[P(x+dx[j],y+dy[j])])
            {
                int u=id[P(x+dx[j],y+dy[j])],v=id[P(x,y)];
                if(u>v) swap(u,v);
                mp[P(u,v)]=1;          
            }
        }
    }
    scanf("%d",&T);
    for(int i=0;i<T;i++)
    {
        scanf("%d%d",&M[i],&W[i]);
        int x,y;
        scanf("%d%d",&x,&y);
        int v=id[P(x,y)];
        vector<int> u;
        vector<P> del;
        u.clear();del.clear();
        for(int j=0;j<M[i];j++)
        {
            scanf("%d%d",&x,&y);
            u.push_back(id[P(x,y)]);
        }
        for(int j=0;j<W[i];j++)
        {
            scanf("%d%d",&x,&y);
            for(int l=0;l<4;l++)
            {
                int u=id[P(x,y)];
                if(id[P(x+dx[l],y+dy[l])])
                {
                    int v=id[P(x+dx[l],y+dy[l])];
                    if(u>v) swap(u,v);
                    if(mp[P(u,v)]<0) continue;
                    ++k;
                    save.push_back((pe){u,v,mp[P(u,v)],k-1});
                    mp[P(u,v)]=-1;
                    del.push_back(P(u,v));
                }
            }
        }
        for(auto x:u)
        {
            ++k;
            if(x>v) ask[k]=P(v,x); else ask[k]=P(x,v);
        }
        for(auto p:del) mp[p]=k+1;
        k++;
    }
    for(auto e:save) add_edge(1,1,k,e.l,e.r,e.u,e.v);
    for(auto p:mp) if(p.S!=-1) add_edge(1,1,k,p.S,k,p.F.F,p.F.S);
    solve(1,1,k);
    int now=0;
    bool f=true;
    for(int i=1;i<=k+1;i++) 
    {
        while(now<T&&M[now]==0) 
        {
            if(f) puts("ok"); else puts("fail");
            now++;
            f=true;
        }
        if(ask[i].F)
        {
            if(!ans[i]) f=false;
            M[now]--;
        }
    }
    return 0;
}
