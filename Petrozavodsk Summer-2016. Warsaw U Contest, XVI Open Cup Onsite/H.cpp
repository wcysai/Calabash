#include<bits/stdc++.h>
#define MAXN 500005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,a[MAXN];
ll s[MAXN];
struct segtree
{
    ll max1[4*MAXN],sum[4*MAXN];
    ll lazy1[4*MAXN],lazy2[4*MAXN];
    void pushup(int k)
    {
        max1[k]=max(max1[k*2],max1[k*2+1]);
        sum[k]=sum[k*2]+sum[k*2+1];
    }
    void add(int k,int l,int r,ll v)
    {
        lazy2[k]+=v;
        max1[k]+=1LL*a[r]*v;
        sum[k]+=1LL*(s[r]-s[l-1])*v;
    }
    void st(int k,int l,int r,ll v)
    {
        lazy1[k]=v; max1[k]=v; lazy2[k]=0;
        sum[k]=1LL*(r-l+1)*v;
    }
    void pushdown(int k,int l,int r)
    {
        int mid=(l+r)/2;
        if(lazy1[k]!=-1) 
        {
            st(k*2,l,mid,lazy1[k]); st(k*2+1,mid+1,r,lazy1[k]);
            lazy1[k]=-1;
        }
        if(lazy2[k])
        {
            add(k*2,l,mid,lazy2[k]); add(k*2+1,mid+1,r,lazy2[k]);
            lazy2[k]=0;
        }
    }
    void build(int k,int l,int r)
    {
        lazy1[k]=-1; lazy2[k]=0;
        if(l==r)
        {
            max1[k]=0;
            sum[k]=0;
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);  
    }
    int query(int k,int l,int r,ll b)
    {
        if(l==r) return l;
        pushdown(k,l,r);
        int mid=(l+r)/2;
        if(max1[k*2]>=b) return query(k*2,l,mid,b); else return query(k*2+1,mid+1,r,b);
    }
    ll get_sum(int k,int l,int r,int x,int y)
    {
        if(l>y||x>r) return 0;
        if(l>=x&&r<=y) return sum[k];
        pushdown(k,l,r);
        int mid=(l+r)/2;
        return get_sum(k*2,l,mid,x,y)+get_sum(k*2+1,mid+1,r,x,y);
    }
    void add(int k,int l,int r,int x,int y,ll v)
    { 
        if(l>y||x>r) return;
        if(l>=x&&r<=y)
        {
            add(k,l,r,v);
            return;
        }
        pushdown(k,l,r);
        int mid=(l+r)/2;
        add(k*2,l,mid,x,y,v); add(k*2+1,mid+1,r,x,y,v);
        pushup(k);
    }
    void st(int k,int l,int r,int x,int y,ll b)
    {
        if(l>y||x>r) return;
        if(l>=x&&r<=y)
        {
            st(k,l,r,b);
            return;
        }
        pushdown(k,l,r);
        int mid=(l+r)/2;
        st(k*2,l,mid,x,y,b); st(k*2+1,mid+1,r,x,y,b);
        pushup(k);
    }
}seg;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
    seg.build(1,1,n);
    ll last=0,lastsum=0;
    for(int i=0;i<m;i++)
    {
        ll d,b;
        scanf("%lld%lld",&d,&b);
        //printf("maxi=%lld\n",seg.max1[1]);
        seg.add(1,1,n,1,n,d-last);
        if(seg.max1[1]>b) 
        {
            int pos=seg.query(1,1,n,b);
            //printf("pos=%d\n",pos);
            seg.st(1,1,n,pos,n,b);
        }
        printf("%lld\n",lastsum+s[n]*(d-last)-seg.get_sum(1,1,n,1,n));
        last=d; lastsum=seg.get_sum(1,1,n,1,n);
    }
    return 0;
}

