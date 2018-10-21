/*************************************************************************
    > File Name: C.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-10-20 16:58:29
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll n,k,m;
struct event
{
    ll id,c,p;
};
vector<event> E[MAXN];
struct segtree
{
    ll sum[4*MAXN],cnt[4*MAXN];
    void pushup(ll k)
    {
        sum[k]=sum[k*2]+sum[k*2+1];
        cnt[k]=cnt[k*2]+cnt[k*2+1];
    }
    void update(ll k,ll l,ll r,ll p,ll num)
    {
        if(l==r) {cnt[k]+=num; sum[k]+=p*num; return;}
        ll mid=(l+r)/2;
        if(p<=mid) update(k*2,l,mid,p,num);
        else update(k*2+1,mid+1,r,p,num);
        pushup(k);
    }
    ll query(ll k,ll l,ll r,ll need)
    {
        if(l==r) {return min(cnt[k],need)*l;}
        ll mid=(l+r)/2;
        if(cnt[k*2]>need) return query(k*2,l,mid,need);
        return sum[k*2]+query(k*2+1,mid+1,r,need-cnt[k*2]);
    }
}seg;
int main()
{
    scanf("%lld%lld%lld",&n,&k,&m);
    for(ll i=0;i<m;i++)
    {
        ll l,r,c,p;
        scanf("%lld%lld%lld%lld",&l,&r,&c,&p);
        E[l].push_back((event){0,c,p});
        E[r+1].push_back((event){1,c,p});
    }
    ll ans=0;
    for(ll i=1;i<=n;i++)
    {
        for(auto it:E[i])
        {
            if(it.id==0) seg.update(1,1,1000000,it.p,it.c);
            else seg.update(1,1,1000000,it.p,-it.c);
        }
        ans+=seg.query(1,1,1000000,k);
        //printf("%lld\n",ans);
    }
    printf("%lld\n",ans);
    return 0;
}
