#include<bits/stdc++.h>
#define MAXN 1000005
#define MAXM 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll n,k;
bool isprime[MAXN];
int m;
ll r[MAXM][MAXM],x[MAXM];
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
int mod_inverse(int a,int m)
{
    ll x,y;
    extgcd(a,m,x,y);
    return (m+x%m)%m;
}
int solve(vector<P> &v)
{
    int n=(int)v.size();
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            r[i][j]=mod_inverse(v[i].S,v[j].S);
    int ans=0;
    for(int i=0;i<n;i++)
    {
        x[i]=v[i].F;
        for(int j=0;j<i;j++) x[i]=(1LL*r[j][i]*(x[i]-x[j])%v[i].S+v[i].S)%v[i].S;
    }
    int base=1;
    for(int i=0;i<n;i++)
    {
        ans=(ans+1LL*base*x[i])%m;
        base=1LL*base*v[i].S%m;
    }
    return ans;
}
int pow_mod(ll a,ll i,int m)
{
    a%=m;
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%m;
        a=a*a%m;
        i>>=1;
    }
    return s;
}
int get_mod(ll n,int p,int pk)
{
    if(n==0) return 1;
    int ans=1;
    for(int i=1;i<=pk;i++) if(i%p) ans=1LL*ans*i%pk;
    ans=pow_mod(ans,n/pk,pk);
    for(int i=1;i<=n%pk;i++) if(i%p) ans=1LL*ans*i%pk;
    ans=1LL*ans*get_mod(n/p,p,pk)%pk;
    return ans;
}
int comb(ll n,ll k,int p,int pk)
{
    if(n<k) return 0;
    int res1=get_mod(n,p,pk),res2=get_mod(k,p,pk),res3=get_mod(n-k,p,pk);
    int cnt=0;
    ll x=n;
    while(x) cnt+=x/p,x/=p;
    x=k;
    while(x) cnt-=x/p,x/=p;
    x=n-k;
    while(x) cnt-=x/p,x/=p;
    int ans=1LL*res1*mod_inverse(res2,pk)%pk*mod_inverse(res3,pk)%pk*pow_mod(p,cnt,pk)%pk;
    return ans;
}
vector<P> v;
int main()
{
    scanf("%lld%lld%d",&n,&k,&m);
    memset(isprime,true,sizeof(isprime));
    for(int i=2;i<=1000000;i++)
        for(int j=2*i;j<=1000000;j+=i)
            isprime[j]=false;
    int tmp=m;
    for(int i=2;i<=1000000;i++)
    {
        if(!isprime[i]) continue;
        if(tmp%i) continue;
        int p=i,pk=1;
        while(tmp%i==0) tmp/=i,pk*=i;
        v.push_back(make_pair(comb(n,k,p,pk),pk));
    }
    printf("%d\n",solve(v));
    return 0;
}
