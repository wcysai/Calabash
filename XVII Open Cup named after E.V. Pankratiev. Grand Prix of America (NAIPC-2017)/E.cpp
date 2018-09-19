
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 500005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef long double db;
int n,m,k,w,cnt;
int p[MAXN],r[MAXN];
ll ans;
void init(int N)
{
    for(int i=1;i<=N;i++)
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
bool same(int x,int y)
{
    x=find(x);y=find(y);
    return (x==y);
}
void unite(int x,int y)
{
    x=find(x);y=find(y);
    if(x==y) return;
    if(r[x]<=r[y])
    {
        p[x]=y;
        if(r[x]==r[y]) r[y]++;
    }
    else p[y]=x;
}
int spe[MAXN];
struct Edge
{
    int u,v;
    int cost;
    int is_special;
}E[MAXM];
bool cmp1(Edge x,Edge y)
{
    if(x.cost!=y.cost) return x.cost<y.cost;
    return x.is_special<y.is_special;
}
bool cmp2(Edge x,Edge y)
{
    if(x.cost!=y.cost) return x.cost<y.cost;
    return x.is_special>y.is_special;
}
P C(db x)
{
    init(n);
    int num=0;P ret;
    ans=0;
    for(int i=0;i<m;i++) if(E[i].is_special) E[i].cost+=x;
    sort(E,E+m,cmp1);
    cnt=0;
    for(int i=0;i<m;i++)
    {
        if(same(E[i].u,E[i].v)) continue;
        ans+=E[i].cost;
        if(E[i].is_special) cnt++;
        unite(E[i].u,E[i].v);
        num++;
    }
    if(num!=n-1) return P(INF,-INF);
    ret.F=cnt;
    init(n);
    sort(E,E+m,cmp2);
    cnt=0;
    for(int i=0;i<m;i++)
    {
        if(same(E[i].u,E[i].v)) continue;
        if(E[i].is_special) cnt++;
        unite(E[i].u,E[i].v);
        num++;
    }
    for(int i=0;i<m;i++) if(E[i].is_special) E[i].cost-=x;
    ret.S=cnt;
    return ret;
}
int main()
{
    //freopen("test.in","r",stdin);
    scanf("%d%d%d%d",&n,&m,&k,&w);
    memset(spe,0,sizeof(spe));
    for(int i=1;i<=k;i++)
    {
        int x;scanf("%d",&x);
        spe[x]=1;
    }
    for(int i=0;i<m;i++)
    {
        scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].cost);
        E[i].is_special=spe[E[i].u]^spe[E[i].v];
    }
    int l=-100001,r=100001,mid;
    P res;
    while(r-l>1)
    {
        mid=(l+r)/2;
        res=C(mid);
        //printf("%d %d %d\n",mid,res.F,res.S);
        if(w>=res.F&&w<=res.S) break;
        if(w<res.F) l=mid; else r=mid;
    }
    res=C(mid);
    if(w>=res.F&&w<=res.S) printf("%lld\n",ans-1LL*w*mid); else puts("-1");
    return 0;
}
