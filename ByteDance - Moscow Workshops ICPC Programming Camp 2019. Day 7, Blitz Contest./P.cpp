#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAXN 2000005
#define INF 1000000001
#define MOD 998244353
#define F first
using namespace std;
typedef long long ll;
bool is_prime_small[MAXN];
bool is_prime[MAXN];
ll phi[MAXN],rem[MAXN];
ll segment_sieve(ll a,ll b)
{

    for(int i=0;i<b-a;i++) phi[i]=rem[i]=a+i;
    for(ll i=0;(ll)i*i<=b;i++) is_prime_small[i]=true;
    for(ll i=0;i<b-a;i++) is_prime[i]=true;
    for(ll i=2;(ll)i*i<=b;i++)
    {
        if(is_prime_small[i])
        {
            for(ll j=2*i;(ll)j*j<=b;j+=i) is_prime_small[j]=false;
            for(ll j=max(2LL,(a+i-1)/i)*i;j<b;j+=i)
            {
                phi[j - a] = phi[j - a] / i * (i - 1);
                while(rem[j-a]%i==0)  rem[j - a] /= i ;
            }
        }
    }
    ll ans=0;
    for(ll j=0;j<b-a;j++) if(rem[j]==1) ans+=phi[j]; else ans+=phi[j]/rem[j]*(rem[j]-1);
    return ans;
}
ll l,r;
int main()
{
    scanf("%lld%lld",&l,&r);
    printf("%lld\n",segment_sieve(l,r+1));
    return 0;
}
