#include<bits/stdc++.h>
#define MAXN 100005
#define INF 2000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
ll n,M,p[MAXN],c[MAXN];
bool check(ll x)
{
    ll sum=0;
    for(int i=1;i<=n;i++)
    {
        ll earn=p[i]*x-c[i];
        if(earn>0) sum+=earn;
        if(sum>=M) return true;
    }
    return false;
}
int main()
{
    scanf("%lld%lld",&n,&M);
    for(int i=1;i<=n;i++) scanf("%lld%lld",&p[i],&c[i]);
    ll l=0,r=INF+100;
    while(r-l>1)
    {
        ll mid=(l+r)/2;
        if(check(mid)) r=mid; else l=mid;
    }
    printf("%lld\n",r);
    return 0;
}
