/*************************************************************************
    > File Name: A.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-12-06 15:57:45
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef double db;
const db PI=acos(-1.0);
db a1[MAXN],a2[MAXN],a3[MAXN],b1[MAXN],b2[MAXN],b3[MAXN];
ll cnt[MAXN],tmp[MAXN];
struct node
{
    double ang;
    ll type;
};
node st[MAXN];
bool cmp(const node &a,const node &b)
{
    return a.ang<b.ang;
}
ll n,m,t;
int main()
{
    freopen("ambitious.in","r",stdin);
    freopen("ambitious.out","w",stdout);
    while(scanf("%lld",&n)==1)
    {
        if(!n) break;
        for(ll i=1;i<=n;i++) scanf("%lf%lf",&a1[i],&b1[i]);
        scanf("%lld",&m);
        for(ll i=1;i<=m;i++) scanf("%lf%lf",&a2[i],&b2[i]);
        scanf("%lld",&t);
        for(ll i=1;i<=t;i++) scanf("%lf%lf",&a3[i],&b3[i]);
        ll ans=0,sum=0;
        for(ll i=1;i<=m;i++)
        {
            ll tot=0;
            for(ll j=1;j<=n;j++)
            {
                db d=atan2(b1[j]-b2[i],a1[j]-a2[i]);
                st[++tot].ang=d;st[tot].type=0;
            }
            for(ll j=1;j<=t;j++)
            {
                db d=atan2(b3[j]-b2[i],a3[j]-a2[i]);
                st[++tot].ang=d-2*PI;st[tot].type=1;
                st[++tot].ang=d;st[tot].type=1;
                st[++tot].ang=d+2*PI;st[tot].type=1;
            }
            sort(st+1,st+tot+1,cmp);
            for(ll j=1;j<=tot;j++) cnt[j]=tmp[j]=0;
            ll k=tot,l=0;
            for(ll j=tot;j>=1;j--)
            {
                if(st[j].type)
                {
                    ++l;
                    for(;st[j].ang+PI<st[k].ang;--k) l-=st[k].type;
                    ++cnt[k]; --cnt[j]; tmp[j]=l-1;
                }
            }
            cnt[tot+1]=0;
            for(ll j=tot;j>=1;j--)
            {
                cnt[j]+=cnt[j+1];
                if(st[j].type) sum+=cnt[j],sum-=tmp[j];
                else ans+=sum;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}

