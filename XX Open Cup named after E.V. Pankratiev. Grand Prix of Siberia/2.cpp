#include<bits/stdc++.h>
#define MAXN 19
#define MAXM 19
#define MAXK (1<<18)
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
char str[MAXN][MAXM];
int dp[MAXN+1][MAXK];
int save[MAXN][MAXK];
int last[MAXN][MAXK];
char res[MAXN][MAXM];
//0: notin
//1: started
//2: done
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++) scanf("%s",str[i]);
    if(str[0][0]=='X') {puts("-1"); return 0;}
    /*
    for(int mask=0;mask<(1<<n);mask++)
    {
        for(int i=0;i<n;i++)
        {
            int cur=(mask>>i)&1;
            if(i==0) {pre[cur][mask][i]=0; pre[cur^1][mask][i]=-1;}
            else
            {
                pre[cur][mask][i]=i; pre[cur^1][mask][i]=pre[cur^1][mask][i-1];
            }
        }
    }
    */
    memset(dp,-1,sizeof(dp));
    dp[0][0]=0;
    for(int i=0;i<m;i++)
    {
        for(int j=1;j<=n;j++)
            for(int mask=0;mask<(1<<n);mask++) dp[j][mask]=-1;
        for(int j=0;j<n;j++)
        {
            for(int mask=0;mask<(1<<n);mask++)
            {
                if(dp[j][mask]==-1) continue;
                bool can1=(str[j][i]!='X'),can2=(str[j][i]!='.');
                int up=(j==0?0:(mask>>(j-1))&1),left=(mask>>j)&1;
                if((i!=0||j!=0)&&(!(up^left))) can1=false;
                if(can1)
                {
                    if(dp[j+1][mask|(1<<j)]<dp[j][mask]+1)
                    {
                        dp[j+1][mask|(1<<j)]=dp[j][mask]+1;
                        save[j+1][mask|(1<<j)]=mask;
                    }
                }
                if(j!=n-1)
                {
                    if(((mask>>j)&1)&&(!((mask>>(j+1))&1))) can2=false;
                }
                if(can2)
                {
                    if(dp[j+1][mask&(~(1<<j))]<dp[j][mask])
                    {
                        dp[j+1][mask&(~(1<<j))]=dp[j][mask];
                        save[j+1][mask&(~(1<<j))]=mask;
                    }
                }
            }
        }
        for(int mask=0;mask<(1<<n);mask++)
        {
            int curmask=mask;
            for(int j=n;j>=1;j--) curmask=save[j][curmask];
            last[i+1][mask]=curmask;
        }
        for(int mask=0;mask<(1<<n);mask++) dp[0][mask]=dp[n][mask];
    }
    int ans=0;
    int curmask=0;
    for(int mask=0;mask<(1<<n);mask++)
    {
        if(dp[0][mask]>ans)
        {
            ans=dp[0][mask];
            curmask=mask;
        }
    }
    if(ans<=0) {puts("-1"); return 0;}
    printf("%d\n",ans);
    for(int i=m;i>=1;i--)
    {
        for(int j=0;j<n;j++)
        {
            if((curmask>>j)&1) res[j][i-1]='.'; el
