#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,p;
ll ans;
mt19937 wcy(time(NULL));
vector<ll> fact;
vector<ll> g;
int prime[MAXN];
bool is_prime[MAXN];
int sieve(int n)
{
    memset(is_prime,true,sizeof(is_prime));
    is_prime[0]=is_prime[1]=false;
    int p=0;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) prime[p++]=i;
        for(int j=0;j<p;j++)
        {
            if(i*prime[j]>n) break;
            is_prime[i*prime[j]]=false;
            if(i%prime[j]==0) break;
        }
    }
    return p;
}
void factorize(ll x)
{
    fact.clear();
    for(int i=0;i<p;i++)
    {
        if(1LL*prime[i]*prime[i]>x) break;
        if(x%prime[i]) continue;
        fact.push_back(prime[i]);
        while(x%prime[i]==0) x/=prime[i];
    }
    if(x>1) fact.push_back(x);
}
void solve(ll x)
{
    factorize(x);
    g.clear();
    for(int i=1;i<=n;i++)
    {
        ll y=__gcd(a[i],x);
        if(y<fact.back()&&fact.back()%y==0)
        {
            ll pr=fact.back();
            fact.push_back(pr/y); fact.push_back(y);
        }
        g.push_back(y);
    }
}
int main()
{
    p=sieve(1000000);
    scanf("%d%d",&n,&k);
}
