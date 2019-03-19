#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
char s[MAXN],t[MAXM];
int n,m;
int dp[MAXN][MAXM];
int go(int pos,int x)
{
    if(pos==n+1) return n+1;
    if(dp[pos][x]!=-1) return dp[pos][x];
    if(s[pos]=='a'+x) return dp[pos][x]=pos; else return dp[pos][x]=go(pos+1,x);
}  
int main()
{
    scanf("%s",s+1);scanf("%s",t+1);
    n=strlen(s+1);m=strlen(t+1);
    memset(dp,-1,sizeof(dp));
    ll ans=0;
    for(int i=1;i<=n;i++)
    {
        int pos=i-1;
        for(int j=1;j<=m;j++)
        {
            pos=go(pos+1,t[j]-'a');
            if(pos==n+1) break;
        }
        ans+=n-pos+1;
    }
    printf("%lld\n",ans);
    return 0;
}
