//
// Created by calabash_boy on 18-5-9.
//

#include<bits/stdc++.h>
#define MAXN 500005
#pragma GCC optimize("O3")
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll d,na,nb,nc,a[MAXN],b[MAXN],c[MAXN];
ll l1[MAXN],r1[MAXN],l2[MAXN],r2[MAXN],l3[MAXN],r3[MAXN];
struct node
{
    ll l,r,sum,lazy;
}seg[4*MAXN];
void build(ll k,ll l,ll r)
{
    seg[k].l=l;seg[k].r=r;
    seg[k].sum=seg[k].lazy=0;
    if(l==r) return;
    ll mid=(l+r)/2;
    build(k*2,l,mid);build(k*2+1,mid+1,r);
}
void Lazy(ll k)
{
    if(seg[k].l!=seg[k].r)
    {
        ll x=seg[k].lazy;
        seg[k*2].sum+=(seg[k*2].r-seg[k*2].l+1)*x;
        seg[k*2+1].sum+=(seg[k*2+1].r-seg[k*2+1].l+1)*x;
        seg[k*2].lazy+=x;seg[k*2+1].lazy+=x;
    }
    seg[k].lazy=0;
}
void update(ll k,ll l,ll r,ll x)
{
    if(seg[k].l>r||seg[k].r<l) return;
    if(seg[k].l>=l&&seg[k].r<=r)
    {
        seg[k].sum+=(seg[k].r-seg[k].l+1)*x;
        seg[k].lazy+=x;
        return;
    }
    Lazy(k);
    update(k*2,l,r,x);
    update(k*2+1,l,r,x);
    seg[k].sum=seg[k*2].sum+seg[k*2+1].sum;
}
ll query(ll k,ll l,ll r)
{
    if(seg[k].l>r||seg[k].r<l) return 0;
    if(seg[k].l>=l&&seg[k].r<=r) return seg[k].sum;
    Lazy(k);
    return query(k*2,l,r)+query(k*2+1,l,r);
}
int main()
{
    while(scanf("%I64d",&d)==1)
    {
        scanf("%I64d%I64d%I64d",&na,&nb,&nc);
        for(ll i=1;i<=na;i++) scanf("%I64d",&a[i]);
        for(ll i=1;i<=nb;i++) scanf("%I64d",&b[i]);
        for(ll i=1;i<=nc;i++) scanf("%I64d",&c[i]);
        build(1,1,nc);
        ll lb=1,rb=1;
        for(ll i=1;i<=na;i++)
        {
            while(rb<=nb&&b[rb]<=a[i]+d) rb++;
            while(lb<=nb&&b[lb]<a[i]-d) lb++;
            l1[i]=lb;r1[i]=rb-1;
            //printf("%I64d %I64d\n",l1[i],r1[i]);
        }
        lb=1,rb=1;
        for(ll i=1;i<=na;i++)
        {
            while(rb<=nc&&c[rb]<=a[i]+d) rb++;
            while(lb<=nc&&c[lb]<a[i]-d) lb++;
            l2[i]=lb;r2[i]=rb-1;
            //printf("%I64d %I64d\n",l2[i],r2[i]);
        }
        lb=1,rb=1;
        for(ll i=1;i<=nb;i++)
        {
            while(rb<=nc&&c[rb]<=b[i]+d) rb++;
            while(lb<=nc&&c[lb]<b[i]-d) lb++;
            l3[i]=lb;r3[i]=rb-1;
            //printf("%I64d %I64d\n",l3[i],r3[i]);
        }
        ll ans=0;
        lb=1,rb=0;
        for(ll i=1;i<=na;i++)
        {
            while(rb<r1[i])
            {
                rb++;
                update(1,l3[rb],r3[rb],1);
            }
            while(lb<l1[i])
            {
                update(1,l3[lb],r3[lb],-1);
                lb++;
            }
            ans+=query(1,l2[i],r2[i]);
            //printf("%I64d\n",ans);
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
