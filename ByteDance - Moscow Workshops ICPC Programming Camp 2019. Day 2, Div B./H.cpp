#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 20
#define INF 2000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
int a[MAXN][MAXN];
int dp[(1<<MAXN)][MAXN];
int last[(1<<MAXN)][MAXN];
void update(int &a,int b) {a=min(a,b);}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%d",&a[i][j]);
    for(int i=0;i<(1<<n);i++)
        for(int j=0;j<n;j++)
            dp[i][j]=INF;
    for(int i=0;i<n;i++) dp[(1<<i)][i]=0;
    for(int mask=1;mask<(1<<n);mask++)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(i==j) continue;
                if(mask&(1<<j)) continue;
                if(dp[mask^(1<<j)][j]>dp[mask][i]+a[i][j])
                {
                    dp[mask^(1<<j)][j]=dp[mask][i]+a[i][j];
                    last[mask^(1<<j)][j]=i;
                }
            }
        }
    }
    int ans=INF,id=-1;
    for(int i=0;i<n;i++) 
    {
        if(dp[(1<<n)-1][i]<ans)
        {
            ans=dp[(1<<n)-1][i];
            id=i;
        }
    }
    printf("%d\n",ans);
    vector<int> order;
    int state=(1<<n)-1;
    while(state)
    {
        order.push_back(id+1);
        int v=last[state][id];
        state^=(1<<id);
        id=v;
    }
    reverse(order.begin(),order.end());
    for(auto x:order) printf("%d ",x);
    return 0;
}

