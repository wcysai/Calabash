/*************************************************************************
    > File Name: KK.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-12-25 23:00:13
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll mul_mod(ll a,ll i,ll n)
{
    ll s=0;
    while(i)
    {
        if(i&1) s=(s+a)%n;
        a=(a+a)%n;
        i>>=1;
    }
    return s;
}
ll pow_mod(ll a,ll i,ll n)
{
    ll s=1;
    while(i)
    {
        if(i&1) s=mul_mod(s,a,n);
        a=mul_mod(a,a,n);
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
    return(t==n-1||(d&1)==1);
}
bool isPrime(ll n)
{
    if(n<2) return false;
    ll a[]={2,3,5,7,11,13,17,19,23,29,31,37};
    for(ll i=0;i<=11;++i) if(!test(n,a[i],n-1)) return false;
    return true;
}
ll n;
int prime[MAXN];
bool is_prime[MAXN];
ll p3[20];
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
vector<int> fact;
void solve()
{
    int sz=(int)fact.size();
    int ans=0;
    for(ll mask=0;mask<p3[sz];mask++)
    {
        int multiplier=1,sgn=1,res=1;
        for(int i=0;i<sz;i++)
        {
            int cur=(mask/p3[i])%3;
            if(cur==1) {multiplier=2LL*multiplier%MOD; sgn=-sgn;}
            if(cur==2&&fact[i]==1) {res=0; break;}
            if(cur==0) res=1LL*res*(fact[i]+1)%(MOD-1);
            else if(cur==1) res=1LL*res*fact[i]%(MOD-1);
            else res=1LL*res*(fact[i]-1)%(MOD-1);
        }
        ans=(ans+1LL*multiplier*sgn*(pow_mod(2,res,MOD)-1))%MOD;
        if(ans>=MOD) ans-=MOD; 
        if(ans<0) ans+=MOD;
    }
    printf("%d\n",ans);
}
int main()
{
    p3[0]=1;
    for(int i=1;i<=18;i++) p3[i]=3LL*p3[i-1];
    int p=sieve(1000000);
    scanf("%lld",&n);
    for(int i=0;i<p;i++)
    {
        int cnt=0;
        while(n%prime[i]==0) {cnt++; n/=prime[i];}
        if(cnt) fact.push_back(cnt);
    }
    if(n>1)
    {
        if(isPrime(n)) fact.push_back(1);
        else 
        {
            int r=(int)sqrt(n);
            bool f=false;
            for(int i=r-10;i<=r+10;i++)
            {
                if(1LL*i*i==n)
                {
                    f=true;
                    fact.push_back(2); break;
                }
            }
            if(!f) {fact.push_back(1); fact.push_back(1);}
        }
    }
    solve();
    return 0;
}

