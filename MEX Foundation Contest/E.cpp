#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 19
#define MAXM 100005
#define MAXK (1<<18)
#define MAXS 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,s;
int u[MAXM],v[MAXM];
int cnt[MAXN][MAXN];
int val[MAXK];
int dp[MAXK][MAXS];
P pre[MAXK][MAXS];
int ans[MAXN];
int lowbit(int mask)
{
    return mask&-mask;
}
void upd(int &x,int y) {x=max(x,y);}
int main()
{
    scanf("%d%d%d",&n,&m,&s);
    for(int i=0;i<m;i++)
    {
        scanf("%d%d",&u[i],&v[i]);
        cnt[u[i]][v[i]]++; cnt[v[i]][u[i]]++;
    }
    for(int mask=1;mask<(1<<n);mask++)
    {
        int v=31-__builtin_clz(lowbit(mask));
        val[mask]=val[mask^lowbit(mask)];
        for(int j=0;j<n;j++)
            if(mask&(1<<j)) val[mask]+=cnt[j+1][v+1];
    }
    memset(dp,-1,sizeof(dp));
    dp[0][s]=0;
    for(int mask=0;mask<(1<<n);mask++)
    {
        int cnt=__builtin_popcount(mask);
        for(int curs=s;curs>=0;curs--)
        {
            if(dp[mask][curs]==-1) continue;
            for(int i=0;i<n;i++)
            {
                if(mask&(1<<i)) continue;
                if(dp[mask^(1<<i)][curs]<dp[mask][curs])
                {
                    dp[mask^(1<<i)][curs]=dp[mask][curs];
                    pre[mask^(1<<i)][curs]=P(mask,curs);
                }
            }
            if(curs>=n-cnt)
            {
                if(dp[mask][curs-(n-cnt)]<dp[mask][curs]+val[(1<<n)-1-mask])
                {
                    dp[mask][curs-(n-cnt)]=dp[mask][curs]+val[(1<<n)-1-mask];
                    pre[mask][curs-(n-cnt)]=P(mask,curs);
                }
            }
        }
    }
    int curmask=(1<<n)-1,cursum=0,t=0;
    while(curmask!=0||cursum!=s)
    {
        P p=pre[curmask][cursum];
        if(p.F==curmask) 
            for(int j=0;j<n;j++) 
                if(!(curmask&(1<<j))) ans[j]++;   
        curmask=p.F; cursum=p.S;
    }
    assert(cursum==s);
    for(int i=0;i<n;i++) printf("%d%c",ans[i],i==n-1?'\n':' ');
    return 0;
}