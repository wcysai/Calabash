#include<bits/stdc++.h>
#define MAXN 4005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
int n,m;
int dp[MAXN][MAXN];
int main()
{
    while(scanf("%d%d",&n,&m)==2)
    {
        for(int i=0;i<=2*(n+m);i++)
            for(int j=0;j<=2*(n+m);j++)
                dp[i][j]=0;
        dp[0][n+m]=1;
        for(int i=0;i<2*(n+m);i++)
            for(int j=0;j<=2*(n+m);j++)
            {
                if(!dp[i][j]) continue;
                int shift=j-(n+m);
                if(shift<n) add(dp[i+1][j+1],dp[i][j]);
                if(shift>-m) add(dp[i+1][j-1],dp[i][j]);
            } 
        printf("%d\n",dp[2*(n+m)][n+m]);
    }
    return 0;
}
