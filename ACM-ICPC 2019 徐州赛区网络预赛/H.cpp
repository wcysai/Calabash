#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 998244353
#define INV 499122177
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll n,m;
int prime[MAXN],p;
bool is_prime[MAXN];
int f[MAXN],g[MAXN],fsum[MAXN],gsum[MAXN];
int addf[MAXN],addg[MAXN],addfsum[MAXN],addgsum[MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int sieve(int n)
{
    int p=0;
    for(int i=0;i<=n;i++) is_prime[i]=true;
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
int sum(ll n)
{
    int x=n%MOD;
    return 1LL*(x+1)*x%MOD*INV%MOD;
}
void PrimeCount(ll n)
{
    ll i,j;
    m=0;
    for(m=1;m*m<=n;m++) f[m]=(n/m-1)%MOD;
    for(i=2;i<=m;i++) g[i]=i-1;
    for(i=2;i<=m;i++)
    {
        if(g[i]==g[i-1]) continue;
        for(j=1;j<=min(m-1,n/i/i);++j)
        {
            if(i*j<m)dec(f[j],(f[i*j]-g[i-1]+MOD)%MOD);
            else dec(f[j],(g[n/i/j]-g[i-1]+MOD)%MOD);
        }
        for(j=m;j>=i*i;j--) dec(g[j],(g[j/i]-g[i-1]+MOD)%MOD);
    }
}
void PrimeSum(ll n)
{
	ll i,j;
    m=0;
    for(m=1;m*m<=n;m++) fsum[m]=sum(n/m),dec(fsum[m],1);
    for(i=2;i<=m;i++) gsum[i]=sum(i),dec(gsum[i],1);
    for(i=2;i<=m;i++)
    {
        if(gsum[i]==gsum[i-1]) continue;
        for(j=1;j<=min(m-1,n/i/i);++j)
        {
            if(i*j<m) dec(fsum[j],1LL*i*(fsum[i*j]-gsum[i-1]+MOD)%MOD);
            else dec(fsum[j],1LL*i*(gsum[n/i/j]-gsum[i-1]+MOD)%MOD);
        }
        for(j=m;j>=i*i;j--) dec(gsum[j],1LL*i*(gsum[j/i]-gsum[i-1]+MOD)%MOD);
    }
}
int getcnt(ll x)
{
    if(x<=m) return g[x];
    return f[n/x];
}
int getsum(ll x)
{
    if(x<=m) return gsum[x];
    return fsum[n/x];
}
int sumd(ll n)
{
    int ans=0;
    for(ll i=1,r;i<=n;i=r+1)
    {
        r=n/(n/i);
        add(ans,1LL*(getcnt(r)-getcnt(i-1)+MOD)*((n/i)%MOD)%MOD);
    }
    return ans;
}
int sumdi(ll n)
{
    int ans=0;
    for(ll i=1,r;i<=n;i=r+1)
    {
        r=n/(n/i);
        add(ans,1LL*(getsum(r)-getsum(i-1)+MOD)*((n/i)%MOD+1)%MOD*((n/i)%MOD)%MOD*INV%MOD);
    }
    return ans;
}
int main()
{
    int p=sieve(100000);
    memset(addf,0,sizeof(addf));
    memset(addg,0,sizeof(addg));
    memset(addfsum,0,sizeof(addfsum));
    memset(addgsum,0,sizeof(addgsum));
    scanf("%lld",&n);
    PrimeCount(n); PrimeSum(n);
    for(int i=0;i<p;i++)
    {
        ll x=1LL*prime[i]*prime[i];
        while(x<=n)
        {
            if(x<=m)
            {
                add(addg[x],1); add(addgsum[x],x%MOD);
            }
            else
            {
                add(addf[n/x],1); add(addfsum[n/x],x%MOD);
            }
            x*=prime[i];
        }
    }
    for(int i=1;i<=m;i++)
    {
        add(addg[i],addg[i-1]); add(addgsum[i],addgsum[i-1]);
        add(g[i],addg[i]); add(gsum[i],addgsum[i]);
    }
    add(addf[m-1],addg[m]); add(addfsum[m-1],addgsum[m]);
    for(int i=m-1;i>=1;i--)
    {
        add(addf[i],addf[i+1]); add(addfsum[i],addfsum[i+1]);
        add(f[i],addf[i]); add(fsum[i],addfsum[i]);
    }
    int ans=1LL*((n+1)%MOD)*sumd(n)%MOD;
    dec(ans,sumdi(n));
    printf("%d\n",ans);
    return 0;
}
