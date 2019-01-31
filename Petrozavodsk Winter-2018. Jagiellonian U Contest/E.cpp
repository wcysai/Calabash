#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1600000
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,k;
int p3[15];
int dp[MAXN],cnt[MAXN];
char str[15];
int get(int x,int y) {return (x/p3[y])%3;}
//0: asked and not set 1: asked and set 2: not asked
int main()
{
    scanf("%d",&T);
    p3[0]=1;
    for(int i=1;i<=13;i++) p3[i]=3*p3[i-1];
    while(T--)
    {
        scanf("%d%d",&k,&n);
        int m=p3[n];
        memset(cnt,0,sizeof(cnt));
        for(int i=0;i<k;i++)
        {
            scanf("%s",str);
            int mask=0;
            for(int j=0;j<n;j++) mask=mask*3+(str[j]-'0');
            cnt[mask]=1;
        }
        for(int j=0;j<n;j++)
            for(int mask=0;mask<m;mask++)
                if(get(mask,j)==2) cnt[mask]+=cnt[mask-p3[j]]+cnt[mask-2*p3[j]];
        for(int mask=0;mask<m;mask++)
        {
            if(cnt[mask]<=1) dp[mask]=0;
            else
            {
                dp[mask]=INF;
                for(int j=0;j<n;j++)
                    if(get(mask,j)==2)
                        dp[mask]=min(dp[mask],1+max(dp[mask-p3[j]],dp[mask-2*p3[j]]));
            }
        }
        printf("%d\n",dp[m-1]);
    }
    return 0;
}

