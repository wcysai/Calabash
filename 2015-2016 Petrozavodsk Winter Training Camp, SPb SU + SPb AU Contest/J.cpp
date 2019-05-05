#include<bits/stdc++.h>
#define MAXN 2005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,p[MAXN];
int bit[MAXN][MAXN];
int fact[MAXN],invf[MAXN];
int dp[MAXN][MAXN];
int s[MAXN];
int f[MAXN];
void ad(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int comb(int n,int k)
{
    if(n<k) return 0;
    return 1LL*fact[n]*invf[k]%MOD*invf[n-k]%MOD;
}
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
int sum(int id,int i)
{
    int s=0;
    while(i>0)
    {
        ad(s,bit[id][i]);
        i-=i&-i;
    }
    return s;
}
void add(int id,int i,int x)
{
    while(i<=n)
    {
        ad(bit[id][i],x);
        i+=i&-i;
    }
}
int main()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<=2000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[2000]=pow_mod(fact[2000],MOD-2);
    for(int i=1999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&p[i]);
    for(int i=1;i<=n;i++)
    {
        for(int j=2;j<=i;j++) ad(dp[i][j],sum(j-1,p[i]));
        dp[i][1]=1;
        for(int j=1;j<=i;j++) add(j,p[i],dp[i][j]);
    }
    for(int i=1;i<=n;i++)
    {
        f[i]=pow_mod(i,n);
        for(int j=1;j<i;j++) dec(f[i],1LL*comb(i,j)*f[j]%MOD);
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            ad(s[j],dp[i][j]);
    int ans=0;
    for(int i=1;i<=n;i++) ad(ans,1LL*s[i]*f[i]%MOD);
    printf("%d\n",ans);
    return 0;
}
