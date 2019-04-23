#include<bits/stdc++.h>
#define MAXN 60005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef double db;
const db eps=1e-10;
int n,a[MAXN];
vector<int> v[MAXN];
db sum[MAXN];
struct segtree
{
    db mini[4*MAXN],lazy[4*MAXN];
    void pushup(int k)
    {
        mini[k]=min(mini[k*2],mini[k*2+1]);
    }
    void pushdown(int k)
    {
        for(int i=k*2;i<=k*2+1;i++)
        {
            mini[i]+=lazy[k];
            lazy[i]+=lazy[k];
        }
        lazy[k]=0;
    }
    void build(int k,int l,int r)
    {
        lazy[k]=0;
        if(l==r) 
        {
            mini[k]=sum[l];
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    void add(int k,int l,int r,int x,int y,db v)
    {
        if(x>r||l>y) return;
        if(l>=x&&r<=y)
        {
            lazy[k]+=v; mini[k]+=v;
            return;
        }
        pushdown(k);
        int mid=(l+r)/2;
        add(k*2,l,mid,x,y,v); add(k*2+1,mid+1,r,x,y,v);
        pushup(k);
    }
    db query(int k,int l,int r,int x,int y)
    {
        if(x>r||l>y) return INF;
        if(l>=x&&r<=y) return mini[k];
        pushdown(k);
        int mid=(l+r)/2;
        return min(query(k*2,l,mid,x,y),query(k*2+1,mid+1,r,x,y));
    }
}seg;
bool check(db x)
{
    for(int i=1;i<=n;i++) v[a[i]].push_back(i);
    for(int i=1;i<=n;i++) reverse(v[i].begin(),v[i].end());
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+(i==v[a[i]].back()?1-x:-x);
    seg.build(1,1,n);
    db ans=INF;
    for(int i=1;i<=n;i++)
    {
        ans=min(ans,seg.query(1,1,n,i,n));
        seg.add(1,1,n,i+1,n,x-1);
        v[a[i]].pop_back();
        if(v[a[i]].size())
        {
            int pos=v[a[i]].back();
            seg.add(1,1,n,pos,n,1);
        }
    }
    return ans<eps;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    db l=0.0,r=1.0;
    while(r-l>eps)
    {
        db mid=(l+r)/2;
        if(check(mid)) r=mid; else l=mid;
    }
    printf("%.10f\n",r);
}
