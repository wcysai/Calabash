//
// Created by calabash_boy on 18-5-11.
//
#include<bits/stdc++.h>
#define MAXN 15
#define MAXM 15
#define MAXD 105
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,N,M,C[MAXN],D[MAXN],a[MAXN][3],b[MAXN][3];
vector<int> cover[MAXN];
int cnt[MAXD];
int cntnum[2000],dp[20][1500];
int solve(int x)
{
    if(cntnum[x]!=-1) return cntnum[x];
    return cntnum[x]=solve(x/2)+(x&1);
}
int main()
{
    scanf("%d",&T);
    memset(cntnum,-1,sizeof(cntnum));
    cntnum[0]=0;
    for(int i=1;i<=1023;i++) solve(i);
    int kase=0;
    while(T--)
    {
        scanf("%d%d",&N,&M);
        kase++;
        for(int i=0;i<10;i++) cover[i].clear();
        for(int i=0;i<N;i++)
        {
            scanf("%d",&C[i]);
            for(int j=0;j<C[i];j++)
                scanf("%d",&a[i][j]);
        }
        for(int i=0;i<M;i++)
        {
            scanf("%d",&D[i]);
            for (int j=0;j<D[i];j++)
                scanf("%d",&b[i][j]);
        }
        //puts("0");
        for(int i=0;i<(1<<M);i++)
        {
            memset(cnt,0,sizeof(cnt));
            if(cntnum[i]>3) continue;
            for(int j=0;j<M;j++)
            {
                if((i>>j)&1)
                    for(int k=0;k<D[j];k++) cnt[b[j][k]]++;
            }
            for(int j=0;j<N;j++)
            {
                bool f=true;
                for(int k=0;k<C[j];k++) if(cnt[a[j][k]]==0) {f=false; break;}
                if(f) cover[j].push_back(i);
            }
        }
        memset(dp,0,sizeof(dp));
        for(int i=0;i<N;i++)
        {
            for (int j = 0; j < (1 << M); j++)
            {
                dp[i + 1][j] = dp[i][j];
                for (int k = 0; k < cover[i].size(); k++)
                {
                    if ((j | cover[i][k]) != j) continue;
                    dp[i + 1][j] = max(dp[i + 1][j], dp[i][j & (~cover[i][k])] + 1);
                }
            }
        }
        printf("Case #%d: %d\n",kase,dp[N][(1<<M)-1]);
    }
    return 0;
}
