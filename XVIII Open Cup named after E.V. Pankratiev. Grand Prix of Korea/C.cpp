#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef long double db;
int n,k[MAXN];
int q[MAXN][MAXN];
db dp[MAXN];
struct bridge
{
    db p,E;
}b[MAXN];
bool cmp2(bridge x,bridge y)
{
    return x.E+(1-x.p)*y.E<y.E+(1-y.p)*x.E;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&k[i]);
        for(int j=1;j<=k[i];j++)
            scanf("%d",&q[i][j]);
        sort(q[i]+1,q[i]+k[i]+1);
        for(int j=1;j<=k[i]+1;j++) dp[j]=0;
        for(int j=k[i];j>=1;j--) dp[j]=(db)(1000-q[i][j])/1000+(db)q[i][j]/1000*(1+dp[j+1]);
        b[i].E=dp[1];b[i].p=1;
        for(int j=1;j<=k[i];j++) b[i].p*=(db)q[i][j]/1000;
    }
    sort(b+1,b+n+1,cmp2);
    db pp=1.0,ans=0;
    for(int i=1;i<=n;i++)
    {
        //printf("%.10Lf %.10Lf\n",b[i].p,b[i].E);
        ans+=pp*b[i].E;
        pp*=(1-b[i].p);
    }
    printf("%.10Lf\n",ans);
}
