#include<bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 200005
#define INF 10000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
struct node
{
	ll l,r,res;
}seg[4*MAXN];
ll n,id[MAXN],dp[MAXN];
P a[MAXN];
vector<P> res;
void build(ll k,ll l,ll r)
{
	seg[k].l=l;seg[k].r=r;
	if(l==r){seg[k].res=INF; id[l]=k; return;}
	ll mid=(l+r)/2;
	build(k*2,l,mid);
	build(k*2+1,mid+1,r);
	seg[k].res=min(seg[k*2].res,seg[k*2+1].res);
}
void update(ll k,ll x)
{
	k=id[k];
	seg[k].res=x;
	while(k>1)
	{
		k=k/2;
		seg[k].res=min(seg[k*2].res,seg[k*2+1].res);
	}
}
ll query(ll k,ll l,ll r)
{
	if(seg[k].l>r||seg[k].r<l) return INF;
	if(seg[k].l>=l&&seg[k].r<=r) return seg[k].res;
	return min(query(k*2,l,r),query(k*2+1,l,r));
}
int main()
{
	while(scanf("%I64d",&n)!=EOF)
	{
		res.clear();
		for(ll i=1;i<=n;i++)
			scanf("%I64d%I64d",&a[i].F,&a[i].S);
		res.push_back(a[n]);
		for(ll i=n-1;i>=1;i--)
			if(a[i].S>res.back().S) res.push_back(a[i]);
		ll t=res.size();
		for(ll i=1;i<=t;i++)
			a[i]=res[t-i];
		build(1,1,t);
		for(ll i=1;i<=t;i++)
		{
			if(i==1) dp[i]=a[i].F+2*a[i].S;
			else
			{
				dp[i]=INF;
				ll id=upper_bound(dp+1,dp+i+1,a[i].F)-dp,res=INF;
				//printf("%I64d\n",id);
				 res=min(res,a[i].F+2*a[id].S);
				if(id!=i) res=min(res,query(1,id,i-1));
				dp[i]=res;
			}
			if(i!=t) update(i,dp[i]+a[i+1].S*2);
			//printf("%I64d %I64d\n",i,dp[i]);
		}
		printf("%I64d\n",dp[t]);
	}
	return 0;
}
