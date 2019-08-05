#include<bits/stdc++.h>
#define MAXN 100005
#define INF 8000000000000000000LL
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,N,x,y;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
int dp[MAXN];
int main()
{
    dp[0]=dp[1]=dp[2]=1;
    for(int i=3;i<=100000;i++)
    {
        dp[i]=dp[i-1];
        add(dp[i],dp[i-3]);
    }
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&N,&x,&y);
        int dif=y-x;
        if(x!=1) dif--;
        if(y!=N) dif--;
        printf("%d\n",dp[dif]);
    }
    return 0;
}
