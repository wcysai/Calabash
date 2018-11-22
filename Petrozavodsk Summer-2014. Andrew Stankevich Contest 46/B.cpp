#include<bits/stdc++.h>
#define MAXN 105
#define INF 1000000000
#define MOD 175781251
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int fact[2*MAXN],invf[2*MAXN];
void add(int &a,int b){a+=b; if(a>=MOD) a-=MOD;}
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
    if(n<k) return 0;
    return 1LL*fact[n]*invf[k]%MOD*invf[n-k]%MOD;
}
int n,bp[MAXN][MAXN],dp[MAXN][MAXN],ans[MAXN];
// bp[i][j]:bipartite graph with two parts i and j
// dp[i][j]:connected bipartite graph with two parts i and j
int main()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<=200;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[200]=pow_mod(fact[200],MOD-2);
    for(int i=199;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    for(int i=0;i<=100;i++)
        for(int j=0;i+j<=100;j++)
            bp[i][j]=pow_mod(3,i*j);
    for(int i=1;i<=100;i++)
    {
        for(int j=0;i+j<=100;j++)
        {
            dp[i][j]=bp[i][j];
            int s=i+j;
            for(int p=1;p<=i&&p<s;p++)
                for(int q=0;q<=j&&p+q<s;q++)
                {
                    int ways=1LL*comb(i-1,p-1)*comb(j,q)%MOD*bp[i-p][j-q]%MOD;
                    dp[i][j]-=1LL*ways*dp[p][q]%MOD;
                    if(dp[i][j]<0) dp[i][j]+=MOD;
                }
        }
    }
    ans[0]=1;
    for(int i=1;i<=100;i++)
    {
        ans[i]=0;
        for(int j=1;j<=i;j++)
        {
            for(int p=1;p<=j;p++)
            {
                int q=j-p;
                int ways=1LL*dp[p][q]*comb(i-1,j-1)%MOD*comb(j-1,p-1)%MOD;
                add(ans[i],1LL*ans[i-j]*ways%MOD);
            }
        }
    }
    while(scanf("%d",&n)==1)
    {
        if(!n) break;
        printf("%d\n",ans[n]);
    }
    return 0;
}
