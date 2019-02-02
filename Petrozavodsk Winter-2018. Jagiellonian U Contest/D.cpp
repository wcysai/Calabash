#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 205
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,a;
int fact[MAXN];
int dp[MAXN][MAXN];
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
int main()
{
    fact[0]=1;
    for(int i=1;i<=200;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&a);
        memset(dp,0,sizeof(dp));
        dp[0][0]=1;
        for(int i=1;i<=a;i++)
        {
            for(int j=0;j<=i;j++)
            {
                add(dp[i][j],dp[i-1][j]);
                if(j>0) add(dp[i][j],1LL*dp[i-1][j-1]*(i-j+1)%MOD);
            }
        }
        int ans=0;
        for(int i=0;i<=a;i++)
        {
            int res=1LL*pow_mod(a-i,n-a)*fact[a-i]%MOD;
            if(i&1) dec(ans,1LL*dp[a][i]*res%MOD); else add(ans,1LL*dp[a][i]*res%MOD);
        }
        printf("%d\n",ans);
    }
    return 0;
}

