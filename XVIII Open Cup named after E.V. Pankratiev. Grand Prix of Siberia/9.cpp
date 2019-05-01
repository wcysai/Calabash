#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 10000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
int q,n;
int prime[MAXN],fact[MAXN];
bool is_prime[MAXN];
int sieve(int n)
{
    int p=0;
    memset(is_prime,true,sizeof(is_prime));
    is_prime[0]=is_prime[1]=false;
    fact[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) {prime[p++]=i; fact[i]=i;}
        for(int j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            fact[prime[j]*i]=prime[j];
            if(i%prime[j]==0) break;
        }
    }
    return p;
}
int pow_mod(int a,int i,int mod)
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
bool check(int x)
{
    int phi=x-1,ans=phi;
    for(int i=1;i*i<=phi;i++)
    {
        if(phi%i) continue;
        if(pow_mod(q,i,x)==1) ans=min(ans,i);
        if(pow_mod(q,phi/i,x)==1) ans=min(ans,phi/i);
    }
    return ans==n;
}
vector<int> v;
int main()
{
    scanf("%d%d",&q,&n);
    int p=sieve(10000000);
    for(int i=0;i<p;i++)
    {
        if(pow_mod(q,n,prime[i])!=1) continue;
        if(check(prime[i])) v.push_back(prime[i]);
    }   
    printf("%d\n",(int)v.size());
    for(auto x:v) printf("%d ",x);
    return 0;
}

