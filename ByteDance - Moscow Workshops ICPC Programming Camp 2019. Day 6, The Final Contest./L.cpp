#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 405
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,MOD;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int fact[MAXN],invf[MAXN];
int p2[100005];
int f[MAXN][MAXN];
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
int comb(int n,int k)
{
    if(n<k) return 0;
    return 1LL*fact[n]*invf[k]%MOD*invf[n-k]%MOD;
}
int ways[MAXN][MAXN],dp[MAXN][MAXN];
int main()
{
    scanf("%d%d",&n,&MOD);
    fact[0]=invf[0]=p2[0]=1;
    for(int i=1;i<=400;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[400]=pow_mod(fact[400],MOD-2,MOD);
    for(int i=399;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    for(int i=1;i<=100000;i++) p2[i]=2LL*p2[i-1]%MOD;
    for(int i=1;i<=400;i++)
        for(int j=1;j<=400;j++)
            f[i][j]=pow_mod(p2[i]-1,j,MOD);
    ways[1][1]=1;dp[1][1]=0;
    for(int i=2;i<=n;i++)
    {
        for(int j=1;j<i;j++)
        {
            for(int last=1;last<=i-j;last++)
            {
                int cnt2=p2[j*(j-1)/2];
                add(ways[i][j],1LL*ways[i-j][last]*f[last][j]%MOD*cnt2%MOD*comb(n-(i-j),j)%MOD);
                add(dp[i][j],1LL*dp[i-j][last]*f[last][j]%MOD*cnt2%MOD*comb(n-(i-j),j)%MOD);
            }
            add(dp[i][j],1LL*ways[i][j]*(n-i+j)%MOD);
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++) add(ans,dp[n][i]);
    ans=1LL*ans*pow_mod(n-1,MOD-2,MOD)%MOD;
    printf("%d\n",ans);
    return 0;
}

