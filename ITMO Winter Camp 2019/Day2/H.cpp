#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll n,k,a[MAXN];
ll count(ll x)
{
    ll ans=0,mult=1;
    x/=k;
    while(x)
    {
        ans+=mult*x;
        mult=-mult;
        x/=k;
    }
    return ans;
}
int main()
{
    freopen("numbers.in","r",stdin);
    freopen("numbers.out","w",stdout);
    scanf("%lld%lld",&n,&k);
    ll l=0,r=INF;
    while(r-l>1)
    {
        ll mid=(l+r)/2;
        if(count(mid)>=n) r=mid; else l=mid; 
    }
    printf("%lld\n",r);
    return 0;
}

