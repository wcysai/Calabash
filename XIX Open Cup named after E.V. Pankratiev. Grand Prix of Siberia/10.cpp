#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 20
#define MAXLEN 100005
#define MAXM (1<<20)
#define MAXC 27
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
char str[MAXN][MAXLEN];
//vector<int> v;
int trans[MAXN][MAXC];
int go(int now,char ch)
{
    if(now==0) return ch-'a'+1;
    else if(ch-'a'+1==now) return 0;
    return now;
}
ll dp[MAXM][MAXC];
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++) 
    {
        scanf("%s",str[i]);
        int len=strlen(str[i]);
        for(int j=0;j<=26;j++)
        {
            int now=j;
            for(int k=0;k<len;k++) now=go(now,str[i][k]);
            trans[i][j]=now;
        }
    }    
    memset(dp,0,sizeof(dp));
    dp[0][0]=1;
    for(int mask=0;mask<(1<<n);mask++)
    {
        for(int i=0;i<=26;i++)
        {
            if(!dp[mask][i]) continue;
            int dummy=(1<<n)-1-mask;
            while(dummy)
            {
                int j=__builtin_ctz(dummy);
                int newmask=mask|(1<<j);
                int to=trans[j][i];
                dp[newmask][to]+=dp[mask][i];
                dummy&=(dummy-1);
            }
        }
    }
    ll ans=0;
    for(int i=1;i<=26;i++) ans+=dp[(1<<n)-1][i];
    printf("%lld\n",ans);
}
