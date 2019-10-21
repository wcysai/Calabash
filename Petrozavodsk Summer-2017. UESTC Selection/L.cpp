#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 110119
#define MAXP 1200005
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
int T;
ll n,m;
int t,r;
vector<P> obstacles;
int dp[MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int extgcd(int a,int b,int &x,int &y)
{
    int d=a;
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
    int x,y;
    extgcd(a,m,x,y);
    return (m+x%m)%m;
}
int fact[MAXP];
int mod_fact(ll n,int p,int &e)
{
    e=0;
    if(n==0) return 1;
    int res=mod_fact(n/p,p,e);
    e+=n/p;
    if(n/p%2!=0) return 1LL*res*(p-fact[n%p])%p;
    return 1LL*res*fact[n%p]%p;
}
int mod_comb(ll n,ll k,int p)
{
    if(n<0||k<0||n<k) return 0;
    int e1,e2,e3;
    int a1=mod_fact(n,p,e1),a2=mod_fact(k,p,e2),a3=mod_fact(n-k,p,e3);
    if(e1>e2+e3) return 0;
    return 1LL*a1*mod_inverse(1LL*a2*a3%p,p)%p;
}
int solve(ll n,ll m)
{
    if(n<0||m<0) return 0;
    if((n+m)%3) return 0;
    ll x=m-(n+m)/3,y=n-(n+m)/3;
    if(x<0||y<0) return 0;
    return mod_comb(x+y,x,MOD);
}
int main()
{
    fact[0]=1;
    for(int i=1;i<MOD;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%lld%lld%d",&n,&m,&r);
        obstacles.clear();
        for(int i=0;i<r;i++)
        {
            ll x,y;
            scanf("%lld%lld",&x,&y);
            obstacles.push_back(P(x,y));
        }
        obstacles.push_back(P(n,m));
        sort(obstacles.begin(),obstacles.end());
        dp[0]=1;
        for(int i=0;i<(int)obstacles.size();i++)
        {
            ll x=obstacles[i].F,y=obstacles[i].S;
            dp[i+1]=solve(x-1,y-1);
            for(int j=0;j<i;j++)  dec(dp[i+1],1LL*dp[j+1]*solve(x-obstacles[j].F,y-obstacles[j].S)%MOD);
        }
        printf("%d\n",dp[(int)obstacles.size()]);
    }
    return 0;
}
