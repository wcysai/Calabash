#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000001
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,int> P;
ll n;
int prime[MAXN],phi[MAXN];
bool is_prime[MAXN];
int T;
ll add_mod(ll a,ll b,ll mod)
{
    ll s=a+b;
    while(s>=mod) s-=mod;
    return s;
}
ll mul_mod(ll a,ll i,ll mod)
{
    ll s=0;
    while(i)
    {
        if(i&1) s=add_mod(s,a,mod);
        a=add_mod(a,a,mod);
        i>>=1;
    }
    return s;
}
ll pow_mod(ll a,ll i,ll mod)
{
    ll s=1;
    while(i)
    {
        if(i&1) s=mul_mod(s,a,mod);
        a=mul_mod(a,a,mod);
        i>>=1;
    }
    return s;
}
ll p_mod(int a,int i,int mod)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%mod;
        a=1LL*a*a%mod;
        i>>=1;
    }
    return s;
}
bool test(ll n)
{
    if(n<3) return n==2;
    const ll a[]={2,7,61,LLONG_MAX};
    ll r=0,d=n-1,x;
    while(~d&1) d>>=1,r++;
    for(int i=0;a[i]<n;i++)
    {
        x=p_mod(a[i],d,n);
        if(x==1||x==n-1) goto next;
        for(int j=0;j<r;j++)
        {
            x=mul_mod(x,x,n);
            if(x==n-1) goto next;
        }
        return false;
        next:;
    }
    return true;
}
int sieve(int n)
{
    int p=0;
    memset(is_prime,true,sizeof(is_prime));
    memset(phi,0,sizeof(phi));
    is_prime[0]=is_prime[1]=false;
    phi[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) {prime[p++]=i; phi[i]=i-1;}
        for(int j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            phi[prime[j]*i]=(i%prime[j]==0?phi[i]*prime[j]:phi[i]*(prime[j]-1));
            if(i%prime[j]==0) break;
        }
    }
    return p;
}
ll find(ll n)
{
    ll x=sqrt(n);
    for(int i=max(1LL,x-10);i<=x+10;i++)
    {
        if(1LL*i*(i-1)==n) return i;
    }
    return -1;
}
int main()
{
    int p=sieve(1000000);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld",&n);
        n*=2;
        vector<P> v;v.clear();
        bool flag=false;
        for(int i=1;i<=4000;i++)
        {
            int s=i*phi[i];
            if(n%s) continue;
            ll res=find(n/s);
            if(res==-1) continue;
            if(!test(res)) continue;
            if(__gcd(res,(ll)i)!=1) continue;
            flag=true;
            printf("%lld\n",1LL*res*i);
            break;
        }
        if(flag) continue;
        for(int i=0;i<p;i++)
        {
            if(n==1) break;
            if(n<=1000000&&is_prime[n])
            {
                v.push_back(P(n,1));
                n=1;
                break;
            }
            if(n%prime[i]==0)
            {
                int cnt=0;
                while(n%prime[i]==0) {cnt++; n/=prime[i];}
                v.push_back(P(prime[i],cnt));
            }
        }
        if(n>1) v.push_back(P(n,1));
        if(flag) continue;
        priority_queue<ll> pque;
        while(pque.size()) pque.pop();
        ll ans=1;
        int sz=(int)v.size();
        for(int i=sz-1;i>=0;i--)
        {
            while(pque.size()&&pque.top()==v[i].F)
            {
                pque.pop();
                v[i].S--;
            }
            if(v[i].S)
            {
                assert(v[i].S&1);
                int a=(v[i].S+1)/2;
                for(int j=0;j<a;j++) ans*=v[i].F;
                ll d=v[i].F-1;
                for(int j=0;j<p;j++)
                {
                    if(d==1) break;
                    if(d<=1000000&&is_prime[d]) {pque.push(d); d=1; break;}
                    if(d%prime[j]==0)
                    {
                        while(d%prime[j]==0) {pque.push(prime[j]); d/=prime[j];}
                    }
                }
                if(d>1) pque.push(d);
            }
        }
        printf("%lld\n",ans);
    }
}
