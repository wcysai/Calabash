#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define INV 500000004
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll fact[MAXN],invf[MAXN],p2[MAXN];
ll pow_mod(ll a,ll i)
{
    ll s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
ll comb(ll n,ll k)
{
    if(n<k) return 0;
    return 1LL*fact[n]*invf[k]%MOD*invf[n-k]%MOD;
}
void add(ll &a,ll b) {a+=b; if(a>=MOD) a-=MOD;}
ll T,n,m;
int main()
{
    scanf("%lld",&T);
    fact[0]=invf[0]=1;
    for(ll i=1;i<=100000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[100000]=pow_mod(fact[100000],MOD-2);
    for(ll i=99999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    p2[0]=1;
    for(ll i=1;i<=100000;i++) p2[i]=1LL*INV*p2[i-1]%MOD;
    while(T--)
    {
        scanf("%lld%lld",&n,&m);
        if(m==0) puts("1");
        else if(m>n) puts("0");
        else if(m==n) printf("%lld\n",1LL*fact[n-1]*INV%MOD);
        else
        {
            ll ans=1LL*invf[n-m]*fact[n]%MOD;
            ll s=0;
            for(ll i=0;i<=n-m-1;i++)
                add(s,1LL*p2[n-m-i]*comb(m-1,n-m-i-1)%MOD*comb(n-m,i)%MOD);
            //printf("%lld %lld\n",ans,s);
            ans=1LL*ans*s%MOD;
            printf("%lld\n",ans);
        }
    }
    return 0;
}