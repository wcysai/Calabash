#include<bits/stdc++.h>
#define MAXN 100005
#define INF 8000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,N;
ll X,Y;
mt19937 wcy(time(NULL));
ll mul_mod(ll a,ll i,ll p)
{
    return (__int128)a*i%p;
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
ll pollard_rho(ll n)
{
    ll c,x,y,d=n;
    if(~n&1) return 2;
    while(d==n)
    {
        x=y=2;
        d=1;
        c=wcy()%(n-1)+1;
        while(d==1)
        {
            x=(mul_mod(x,x,n)+c)%n;
            y=(mul_mod(y,y,n)+c)%n;
            y=(mul_mod(y,y,n)+c)%n;
            d=__gcd(x>=y?x-y:y-x,n);
        }
    }
    return d;
}
bool isPrime(ll n)
{
    if(n<2) return false;
    ll a[]={2,325,9375,28178,450775,9780504,1795265022LL,LLONG_MAX};
    ll r=0,d=n-1,x;
    while(~d&1) d>>=1,r++;
    for(int i=0;a[i]<n;i++)
    {
        x=pow_mod(a[i],d,n);
        if(x==1||x==n-1) goto next;
        for(int i=0;i<r;i++)
        {
            x=mul_mod(x,x,n);
            if(x==n-1) goto next;
        }
        return false;
next:;
    }
    return true;
}
map<ll,int> fact;
ll a[MAXN];
void factorize(ll n)
{
    if(n==1) return;
    if(isPrime(n)) {fact[n]++; return;}
    ll d=pollard_rho(n);
    factorize(d); factorize(n/d);
    return;
}
ll get_expo(ll n,ll pr)
{
    ll ret=0;
    while(n)
    {
        ret+=n/pr;
        n/=pr;
    }
    return ret;
}
int main()
{
    ll X;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%lld%lld",&N,&X,&Y);
        fact.clear();
        factorize(X);
        for(int i=1;i<=N;i++) scanf("%lld",&a[i]);
        ll ans=INF;
        for(auto p:fact)
        {
            ll pr=p.F;
            ll res=get_expo(Y,pr);
            for(int i=1;i<=N;i++) res-=get_expo(a[i],pr);
            ans=min(ans,res/p.S);
        }
        printf("%lld\n",ans);
    }
    return 0;
}