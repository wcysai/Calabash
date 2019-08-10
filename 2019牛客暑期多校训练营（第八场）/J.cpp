#include<bits/stdc++.h>
#define MAXN 3005
#define MAXM 10000005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int fact[MAXM],invf[MAXM];
int res[MAXM],sum[MAXM];
int L,d,m;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
int comb(int n,int k)
{
    return 1LL*fact[n]*invf[k]%MOD*invf[n-k]%MOD;
}
int solve(int dis,int jumps)
{
    if(dis<0||jumps<0) return 0;
    if(jumps==0) return (dis==0?1:0);
    if(dis<1LL*jumps*d) return 0;
    int sum=dis-jumps*d;
    return comb(sum+jumps-1,jumps-1);
}
vector<P> v;
int dp[MAXN];
int main()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<=10000000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[10000000]=pow_mod(fact[10000000],MOD-2);
    for(int i=9999999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    scanf("%d%d%d",&L,&d,&m);
    res[L]=sum[L]=1;
    for(int i=L-1;i>=0;i--)
    {
        if(i+d>L) res[i]=0; else res[i]=sum[i+d];
        sum[i]=sum[i+1];
        add(sum[i],res[i]);
    }
    for(int i=0;i<m;i++)
    {
        int t,p;
        scanf("%d%d",&t,&p);
        v.push_back(P(t,p));
    }
    sort(v.begin(),v.end());
    for(int i=0;i<(int)v.size();i++)
    {
        int t=v[i].F,p=v[i].S;
        dp[i]=solve(p,t);
        for(int j=0;j<i;j++) dec(dp[i],1LL*dp[j]*solve(p-v[j].S,t-v[j].F)%MOD);
    }
    int ans=res[0];
    for(int i=0;i<(int)v.size();i++) dec(ans,1LL*dp[i]*res[v[i].S]%MOD);
    printf("%d\n",ans);
    return 0;
}
