//
// Created by bytedance on 19-2-16.
//
#include <bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k;
struct segtree
{
    int minv[4*MAXN],maxv[4*MAXN],lazy[4*MAXN];
    ll sum[4*MAXN];
    void pushup(int k)
    {
        minv[k]=min(minv[k*2],minv[k*2+1]);
        maxv[k]=max(maxv[k*2],maxv[k*2+1]);
        sum[k]=sum[k*2]+sum[k*2+1];
    }
    void pushdown(int k,int l,int r)
    {
        if(!lazy[k]) return;
        int mid=(l+r)/2;
        int len1=mid-l+1,len2=r-mid;
        minv[k*2]=maxv[k*2]=minv[k*2+1]=maxv[k*2+1]=lazy[k];
        sum[k*2]=1LL*len1*lazy[k];sum[k*2+1]=1LL*len2*lazy[k];
        lazy[k*2]=lazy[k*2+1]=lazy[k];
        lazy[k]=0;
    }
    void build(int k,int l,int r)
    {
        lazy[k]=0;
        if(l==r)
        {
            minv[k]=maxv[k]=sum[k]=0;
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid);build(k*2+1,mid+1,r);
        pushup(k);
    }
    void update(int k,int l,int r,int x,int y,int v)
    {
        if(x>r||l>y||minv[k]>=v) return;
        if(l>=x&&r<=y&&maxv[k]<=v)
        {
            minv[k]=maxv[k]=v;
            lazy[k]=v;
            sum[k]=1LL*v*(r-l+1);
            return;
        }
        pushdown(k,l,r);
        int mid=(l+r)/2;
        update(k*2,l,mid,x,y,v);update(k*2+1,mid+1,r,x,y,v);
        pushup(k);
    }
    ll query(int k,int l,int r,int x,int y)
    {
        if(x>r||l>y) return 0;
        if(l>=x&&r<=y) return sum[k];
        pushdown(k,l,r);
        int mid=(l+r)/2;
        return query(k*2,l,mid,x,y)+query(k*2+1,mid+1,r,x,y);
    }
}seg;
char str[5];
int main()
{
    while(scanf("%d%d",&n,&k)==2)
    {
        if(!n&&!k) break;
        seg.build(1,1,n);
        for(int i=0;i<k;i++)
        {
            int x,y,v;
            scanf("%s",str);
            if(str[0]=='^')
            {
                scanf("%d%d%d",&x,&y,&v);
                seg.update(1,1,n,x,y,v);
            }
            else {
                scanf("%d%d",&x,&y);
                ll res=seg.query(1,1,n,x,y),q=y-x+1;
                ll g=__gcd(res,q);
                res/=g;q/=g;
                if(q==1) printf("%lld\n",res);
                else printf("%lld/%lld\n",res,q);
            }
        }
    }
    return 0;
}
