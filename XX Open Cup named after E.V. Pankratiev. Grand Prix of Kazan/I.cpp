#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
vector<int> G[MAXN];
bool centroid[MAXN];
int sz[MAXN];
P getroot(int v,int p,int t)
{
    P res=P(INT_MAX,-1);
    int m=0;
    sz[v]=1;
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i];
        if(to==p||centroid[to]) continue;
        res=min(res,getroot(to,v,t));
        m=max(m,sz[to]);
        sz[v]+=sz[to];
    }
    m=max(m,t-sz[v]);
    res=min(res,P(m,v));
    return res;
}
void getsz(int v,int p)
{
    sz[v]=1;
    for(auto to:G[v])
    {
        if(to==p) continue;
        if(centroid[to]) continue;
        getsz(to,v);
        sz[v]+=sz[to];
    }
}
vector<P> cur;
vector<int> query;
int get_ans()
{
    int x;
    scanf("%d",&x);
    return x;
}
int ask(int x)
{
    int k=(int)query.size();
    printf("? %d ",k);
    printf("%d",x);
    for(auto v:query) printf(" %d",v);
    printf("\n");
    fflush(stdout);
    return get_ans();
}
void answer(int x)
{
    printf("! %d\n",x);
    fflush(stdout);
    exit(0);
}
void construct(int l,int r)
{
    query.clear();
    for(int i=l;i<=r;i++) query.push_back(cur[i].S);
}
void solve(int v)
{
    getsz(v,0); cur.clear();
    for(auto to:G[v])
    {
        if(centroid[to]) continue;
        cur.push_back(P(sz[to],to));
    }
    if(!cur.size()) answer(v);
    random_shuffle(cur.begin(),cur.end());
    int l=0,r=(int)cur.size()-1;
    construct(l,r);
    if(ask(v)) answer(v);
    while(l!=r)
    {
        int sum=0,sum2=0,mid=0;
        for(int i=l;i<=r;i++) sum+=cur[i].F;
        for(int i=l;i<r;i++)
        {
            sum2+=cur[i].F;
            mid=i;
            if(sum2*2>=sum) break;
        }
        construct(l,mid);
        if(!ask(v)) r=mid; else l=mid+1;
    }
    assert(l==r);
    centroid[v]=true;
    int x=getroot(cur[l].S,v,sz[cur[l].S]).S;
    solve(x);
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
    int v=getroot(1,0,n).S;
    solve(v);
    return 0;
}
