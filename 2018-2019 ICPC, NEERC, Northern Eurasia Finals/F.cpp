#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll n;
ll prime[MAXN];
bool is_prime[MAXN];
ll extgcd(ll a,ll b,ll &x,ll &y)
{
    ll d=a;
    if(b!=0)
    {
        d=extgcd(b,a%b,y,x);
        y-=(a/b)*x;
    }
    else
    {
        x=1;
        y=0;
    }
    return d;
}
ll sieve(ll n)
{
    ll p=0;
    memset(is_prime,true,sizeof(is_prime));
    is_prime[0]=is_prime[1]=false;
    for(ll i=2;i<=n;i++)
    {
        if(is_prime[i]) prime[p++]=i;
        for(ll j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            if(i%prime[j]==0) break;
        }
    }
    return p;
}
int main()
{
    ll p=sieve(100000);
    scanf("%lld",&n);
    ll cnt=0,dummy=n,pr=-1;
    for(ll i=0;i<p;i++)
    {
        if(n%prime[i]==0)
        {
            cnt++;pr=1;
            while(dummy%prime[i]==0) {dummy/=prime[i]; pr*=prime[i];}
        }
    }
    if(dummy!=1) cnt++;
    if(cnt<2) {puts("NO"); return 0;}
    puts("YES\n2");
    ll a,b,q;
    p=pr;q=n/pr;
    extgcd(q,p,a,b);
    b=(b*((p*q-1)%q)%q+q)%q;a=(n-1-b*p)/q;
    printf("%lld %lld\n%lld %lld\n",a,p,b,q);
    return 0;
}
