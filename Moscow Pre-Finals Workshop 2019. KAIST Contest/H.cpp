#include<bits/stdc++.h>
#define MAXN 80005
#define MAXM 10000005
#define MAXT 1000000001
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q,lson[MAXM],rson[MAXM],root[MAXN];
bool has[MAXM];
P ans[MAXM];
int tot,a[MAXN],b[MAXN],c[MAXN];
vector<int> G[MAXN];
void add_edge(int u,int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}
ll f(P p,int x)
{
    return 1LL*p.F*(x-1)+p.S;
}
void insert(int &k,int last,int l,int r,int x,int y,P p)
{
    if(l>y||x>r) return;
    k=++tot;
    has[k]=false;
    if(last)
    {
        has[k]=has[last];
        ans[k]=ans[last];
        lson[k]=lson[last];
        rson[k]=rson[last];
    }
    if(l>=x&&r<=y)
    {
        if(!has[k])
        {
            has[k]=true;
            ans[k]=p;
            return;
        }
        ll trl=f(ans[k],l),trr=f(ans[k],r);
        ll vl=f(p,l),vr=f(p,r);
        if(trl<=vl&&trr<=vr) return;
        if(trl>=vl&&trr>=vr) {ans[k]=p; return;}
        int mid=(l+r)/2;
        if(trl>=vl) swap(ans[k],p);
        if(f(ans[k],mid)<=f(p,mid)) insert(rson[k],rson[last],mid+1,r,x,y,p);
        else swap(ans[k],p),insert(lson[k],lson[last],l,mid,x,y,p);
        return;
    }
    int mid=(l+r)/2;
    insert(lson[k],lson[last],l,mid,x,y,p); insert(rson[k],rson[last],mid+1,r,x,y,p);
}
ll query(int &k,int l,int r,int x)
{
    if(!k) return INF;
    ll res=(!has[k]?INF:f(ans[k],x));
    if(l==r) return res;
    int mid=(l+r)/2;
    if(x<=mid) return min(res,query(lson[k],l,mid,x));
    else return min(res,query(rson[k],mid+1,r,x));
}
void dfs(int v,int p)
{
    insert(root[v],root[p],1,MAXT,1,c[v],P(b[v],a[v]));
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v);
    }
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) scanf("%d",&b[i]);
    for(int i=1;i<=n;i++) scanf("%d",&c[i]);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add_edge(u,v);
    }
    root[0]=1; tot=1;
    dfs(1,0);
    for(int i=0;i<q;i++)
    {
        int v,t;
        scanf("%d%d",&v,&t);
        printf("%lld\n",query(root[v],1,MAXT,t+1));
    }
    return 0;
}
