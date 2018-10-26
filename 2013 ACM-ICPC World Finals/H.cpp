#include<bits/stdc++.h>
#define MAXN 505
#define INF 100000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN];
int cnt[MAXN][MAXN][MAXN];
bool ok[MAXN][MAXN],comp[MAXN][MAXN];
int minn[MAXN][MAXN],f[MAXN][MAXN],dp[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    memset(ok,false,sizeof(ok));memset(comp,false,sizeof(comp));memset(cnt,0,sizeof(cnt));
    for(int i=1;i<=n;i++)
    {
        comp[i][i]=true;
        if(a[i]==1) ok[i][i]=true; else ok[i][i]=false;
        int minx=a[i],maxx=a[i];cnt[i][i][a[i]]++;minn[i][i]=a[i];
        for(int j=i+1;j<=n;j++)
        {
            for(int k=1;k<=500;k++) cnt[i][j][k]=cnt[i][j-1][k];
            cnt[i][j][a[j]]++;
            minx=min(minx,a[j]);maxx=max(maxx,a[j]);
            minn[i][j]=minx;
            if(!comp[i][j-1]) comp[i][j]=false;
            else
            {
                if(cnt[i][j][a[j]]>2) comp[i][j]=false; else comp[i][j]=true;
            }
            if(!comp[i][j]) {ok[i][j]=false;  continue;}
            if(maxx-minx==j-i&&minx==1) ok[i][j]=true; else ok[i][j]=false;
            //printf("%d %d %d %d %d\n",i,j,ok[i][j]?1:0,comp[i][j],minn[i][j]);
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            for(int k=1;k<=500;k++)
                cnt[i][j][k]+=cnt[i][j][k-1];
    for(int len=1;len<=n;len++) {
        for (int i = 1; i + len - 1 <= n; i++) {
            int j = i + len - 1;
            f[i][j] = INF;
            if (!comp[i][j]) continue;
            if(i==j) {f[i][j]=0; continue;}
            for (int k = i; k < j; k++) {
                if (!comp[i][k] || !comp[k + 1][j]) continue;
                int cur = INF;
                //if(i==1&&j==2) printf("%d\n",cnt[1][1][2]);
                if (minn[i][k] < minn[k + 1][j]) cur = len - cnt[i][k][minn[k + 1][j] - 1];
                else cur=len-cnt[k+1][j][minn[i][k]-1];
                f[i][j] = min(f[i][j], cur + f[i][k] + f[k + 1][j]);
            }
            //printf("%d %d %d\n",i,j,f[i][j]);
        }
    }
    dp[0]=0;
    for(int i=1;i<=n;i++)
    {
        dp[i]=INF;
        for(int j=i;j>=1;j--)
            if(ok[j][i]) dp[i]=min(dp[i],dp[j-1]+f[j][i]);
            //printf("%d %d\n",i,dp[i]);
    }
    if(dp[n]==INF) puts("impossible"); else printf("%d\n",dp[n]);
    return 0;
}
/*
 * 7
1 2 3 2 4 1 3
1 2 1 1 1
1 3 1 1 1
1 4 1 1 1
1 5 1 1 1
1 6 1 1 1
1 7 1 1 1
2 3 1 1 2
2 4 1 1 2
2 5 1 1 2
2 6 1 1 1
2 7 1 1 1
3 4 1 1 2
3 5 1 1 2
3 6 1 1 1
3 7 1 1 1
4 5 1 1 2
4 6 1 1 1
4 7 1 1 1
5 6 1 1 1
5 7 1 1 1
6 7 1 1 1
1
1 2 1
2 3 1
3 4 100000000
4 5 1
5 6 100000000
6 7 1
1 3 2
2 4 100000000
3 5 100000000
4 6 100000000
5 7 100000000
1 4 5
2 5 100000000
3 6 100000000
4 7 100000000
1 5 6
2 6 100000000
3 7 100000000
1 6 100000000
2 7 100000000
1 7 100000000
3
 */
