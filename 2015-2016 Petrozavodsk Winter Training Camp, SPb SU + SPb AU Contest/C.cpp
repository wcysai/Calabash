#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 5005
#define MAXM 1000005
#define INF 8000000000000000000LL
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int prime[MAXM];
bool is_prime[MAXM];
ll n,m,k,da[MAXN],db[MAXN],a[MAXN],b[MAXM];
int sieve(int n)
{
    int p=0;
    memset(is_prime,true,sizeof(is_prime));
    is_prime[0]=is_prime[1]=false;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) prime[p++]=i;
        for(int j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            if(i%prime[j]==0) break;
        }
    }
    return p;
}
ll mul_mod(ll a,ll i,ll p)
{
    if(i==0) return 0;
    if(INF/i>a) return a*i%p;
    if(a<i) swap(a,i);
    ll s=0;
    while(i)
    {
        if(i&1) s=(s+a)%p;
        a=(a+a)%p;
        i>>=1;
    }
    return s;
}
ll pow_mod(ll a,ll i,ll p)
{
    ll s=1;
    while(i)
    {
        if(i&1) s=mul_mod(s,a,p);
        a=mul_mod(a,a,p);
        i>>=1;
    }
    return s;
}
bool test(ll n,ll a,ll d)
{
    if(n==2) return true;
    if(n==a) return true;
    if((n&1)==0) return false;
    while(!(d&1)) d=d>>1;
    ll t=pow_mod(a,d,n);
    while((d!=n-1)&&(t!=1)&&(t!=n-1))
    {
        t=mul_mod(t,t,n);
        d=d<<1;
    }
    return (t==n-1||(d&1)==1);
}
bool isPrime(ll n)
{
    if(n<2) return false;
    ll a[]={2,325,9375,28178,450775,9780504,1795265022};
    for(int i=0;i<=6;i++) if(!test(n,a[i],n-1)) return false;
    return true;
}
mt19937_64 wcy(time(NULL));
ll pollard_rho(ll n)
{
    ll a=wcy()%(n-1)+1;
    ll x=2,y=2,d=1,k=0,i=1;
    while(d==1)
    {
        ++k;
        x=mul_mod(x,x,n)+a;
        d=__gcd(x>=y?x-y:y-x,n);
        if(k==i)
        {
            y=x;
            i<<=1;
        }
    }
    if(d==n) return pollard_rho(n);
    return d;
}
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
ll mod_inverse(ll a,ll m)
{
    ll x,y;
    extgcd(a,m,x,y);
    return (m+x%m)%m;
}
vector<ll> pr;
vector<int> expa,expb;
int main()
{
    int p=sieve(1000000);
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++) {scanf("%lld",&a[i]); da[i]=a[i];}
    for(int i=1;i<=m;i++) {scanf("%lld",&b[i]); db[i]=b[i];}
    scanf("%lld",&k);
    for(int i=0;i<k;i++)
    {
        for(int j=1;j<=n;j++) a[j]=da[j];
        for(int j=1;j<=m;j++) b[j]=db[j];
        ll mod;
        scanf("%lld",&mod);
        pr.clear();expa.clear();expb.clear();
        ll dummy=mod;
        for(int j=0;j<p;j++)
        {
            if(dummy==1) break;
            if(dummy%prime[j]==0)
            {
                pr.push_back(prime[j]);
                while(dummy%prime[j]==0) dummy/=prime[j];
            }
        }
        if(dummy>1)
        {
            for(int j=1;j<=n;j++)
            {
                if(dummy==1) break;
                ll g=__gcd(dummy,a[j]);
                if(g>1&&g<dummy) {dummy/=g; pr.push_back(g);}
            }
        }
        if(dummy>1)
        {
            for(int j=1;j<=m;j++)
            {
                if(dummy==1) break;
                ll g=__gcd(dummy,b[j]);
                if(g>1&&g<dummy) {dummy/=g; pr.push_back(g);}
            }
        }
        if(dummy>1) pr.push_back(dummy);
        int sz=(int)pr.size();
        expa.resize(sz); expb.resize(sz);
        for(int j=1;j<=n;j++)
        {
            for(int cnt=0;cnt<sz;cnt++)
            {
                while(a[j]%pr[cnt]==0)
                {
                    expa[cnt]++;
                    a[j]/=pr[cnt];
                }
            }
        }
        for(int j=1;j<=m;j++)
        {
            for(int cnt=0;cnt<sz;cnt++)
            {
                while(b[j]%pr[cnt]==0)
                {
                    expb[cnt]++;
                    b[j]/=pr[cnt];
                }
            }
        }
        ll res=1;
        bool f=true;
        for(int j=0;j<sz;j++)
        {
            if(expa[j]<expb[j])
            {
                f=false;
                break;
            }
            for(int l=0;l<expa[j]-expb[j];l++) res=mul_mod(res,pr[j],mod);
        }
        if(!f)
        {
            puts("DIVISION BY ZERO");
            continue;
        }
        ll inv=1;
        for(int j=1;j<=n;j++) res=mul_mod(res,a[j],mod);
        for(int j=1;j<=m;j++) inv=mul_mod(inv,b[j],mod);
        res=mul_mod(res,mod_inverse(inv,mod),mod);
        printf("%lld\n",res);
    }
    return 0;
}
