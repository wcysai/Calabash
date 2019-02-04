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
int n,q,type,l,r,x;
//form: (x+a)/b+c, a<b
struct segtree
{
    ll a[4*MAXN],b[4*MAXN],c[4*MAXN],ans[4*MAXN];
    void pushup(int k)
    {
        ans[k]=max(ans[k*2],ans[k*2+1]);
    }
    void pushdown(int k)
    {
        for(int i=k*2;i<=k*2+1;i++)
        {
            ans[i]+=a[k];
            ans[i]/=b[k];
            ans[i]+=c[k];
            a[i]=a[i]+b[i]*c[i]+b[i]*a[k];
            b[i]=b[i]*b[k];
            c[i]=c[k];
            adjust(i);
        }
        a[k]=0;b[k]=1;c[k]=0;
    }
    void adjust(int k)
    {
        c[k]+=a[k]/b[k];
        a[k]%=b[k];
        if(b[k]>INF)
        {
            if(b[k]-a[k]>=INF)
            {
                a[k]=0;
                b[k]=INF;
            }
            else
            {
                ll z=b[k]-INF;
                a[k]-=z;
                b[k]-=z;
            }
        }
    }
    void build(int k,int l,int r)
    {
        a[k]=c[k]=0; b[k]=1;
        if(l==r)
        {
            scanf("%lld",&ans[k]);
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid);build(k*2+1,mid+1,r);
        pushup(k);
    }
    void add(int k,int l,int r,int x,int y,int v)
    {
        if(x>r||l>y) return;
        if(l>=x&&r<=y)
        {
            c[k]+=v;ans[k]+=v;
            return;
        }
        pushdown(k);
        int mid=(l+r)/2;
        add(k*2,l,mid,x,y,v);add(k*2+1,mid+1,r,x,y,v);
        pushup(k);
    }
    void div(int k,int l,int r,int x,int y,int v)
    {
        if(x>r||l>y) return;
        if(l>=x&&r<=y)
        {
            a[k]+=b[k]*c[k];
            b[k]*=v;c[k]=0;
            ans[k]/=v;
            adjust(k);
            return;
        }
        pushdown(k);
        int mid=(l+r)/2;
        div(k*2,l,mid,x,y,v);div(k*2+1,mid+1,r,x,y,v);
        pushup(k);
    }
    ll query(int k,int l,int r,int x,int y)
    {
        if(x>r||l>y) return LONG_LONG_MIN;
        if(l>=x&&r<=y) return ans[k];
        pushdown(k);
        int mid=(l+r)/2;
        return max(query(k*2,l,mid,x,y),query(k*2+1,mid+1,r,x,y));
    }
}seg;
int main()
{
    scanf("%d%d",&n,&q);
    seg.build(1,1,n);
    for(int i=0;i<q;i++)
    {
        scanf("%d%d%d%d",&type,&l,&r,&x);l++;r++;
        if(type==0) seg.add(1,1,n,l,r,x);
        else if(type==1) seg.div(1,1,n,l,r,x);
        else printf("%lld\n",seg.query(1,1,n,l,r));
    }
    return 0;
}

