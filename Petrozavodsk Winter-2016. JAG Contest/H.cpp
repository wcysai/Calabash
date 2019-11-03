#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,t;
void madd(int &a,int b,int m) {a+=b; if(a>=m) a-=m;}
template <int _MOD, int _BASE>
struct segtree
{
    static const int MOD = _MOD, BASE = _BASE;
    int mod[4*MAXN],mult[4*MAXN],add[4*MAXN];
    void change(int k,int x,int y)
    {
        mod[k]=mod[k]*x+y;
        mult[k]=mult[k]*x; add[k]=add[k]*x+y;
    }
    void pushdown(int k)
    {
        if(mult[k]==1&&add[k]==0) return;
        int x=mult[k],y=add[k];
        change(k*2,x,y); change(k*2+1,x,y);
        mult[k]=1; add[k]=0;
    }
    void build(int k,int l,int r)
    {
        mod[k]=0; mult[k]=1; add[k]=0;
        if(l==r) return;
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
    }
    void update(int k,int l,int r,int x,int y,int v)
    {
        if(x>r||l>y) return;
        if(l>=x&&r<=y)
        {
            change(k,BASE,v);
            return;
        }
        pushdown(k);
        int mid=(l+r)/2;
        update(k*2,l,mid,x,y,v); update(k*2+1,mid+1,r,x,y,v);
    }
    int query(int k,int l,int r,int p)
    {
        if(l==r) return mod[k];
        pushdown(k);
        int mid=(l+r)/2;
        if(p<=mid) return query(k*2,l,mid,p); else return query(k*2+1,mid+1,r,p);
    }
};
segtree<998244353, 19260817> seg0;
segtree<993244853, 2333333> seg1;
int main()
{
    scanf("%d%d",&n,&k);
    seg0.build(1,1,n); seg1.build(1,1,n);
    scanf("%d",&t);
    for(int i=0;i<t;i++)
    {
        int l,r,x;
        scanf("%d%d%d",&l,&r,&x);
        seg0.update(1,1,n,l,r,x); seg1.update(1,1,n,l,r,x);
    }
    int ans0=0,ans1=0;
    for(int i=1;i<=k;i++)
    {
        ans0=ans0*seg0.BASE+i;
        ans1=ans1*seg1.BASE+i;
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        if(seg0.query(1,1,n,i)==ans0&&seg1.query(1,1,n,i)==ans1) ans++;
    printf("%d\n",ans);
    return 0;
}
