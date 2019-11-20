#include<bits/stdc++.h>
#define MAXN 55
#define INF 1000000000000000001LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
ll k;
ll prod[MAXN][MAXN];
ll dp[MAXN][MAXN][MAXN];
void add(ll &a,ll b) {a+=b; if(a>=INF) a=INF;}
void mult(ll &a,ll b) {if(a==0) return; if(INF/a<b) a=INF; else a*=b;}
bool used[MAXN];
int ans[MAXN];
int main()
{
    scanf("%d%d%lld",&n,&m,&k);
    for(int i=1;i<=50;i++)
    {
        prod[i][i-1]=1;
        for(int j=i;j<=50;j++)
        {
            prod[i][j]=prod[i][j-1];
            mult(prod[i][j],j);
        }
    }
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=i;j++)
        {
            for(int k=0;k<=j;k++)
            {
                if(j==0) dp[i][j][k]=(k>0?0:prod[1][i]);
                else
                {
                    if(k) dp[i][j][k]=dp[i-1][j-1][k-1]; else dp[i][j][k]=0;
                    if(j>=2)
                    {
                        ll tmp=dp[i-1][j-2][k]; mult(tmp,j-1);
                        add(dp[i][j][k],tmp);
                    }
                    ll tmp=dp[i-1][j-1][k]; mult(tmp,i-j);
                    add(dp[i][j][k],tmp);
                }
            }
        }
    }
    memset(used,false,sizeof(used));
    int fixed=m;
    int canuse=n;
    if(k>dp[n][n][m]) {puts("-1"); return 0;}
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(used[j]) continue;
            int rem=n-i,rfixed=fixed-(i==j);
            int rcanuse=canuse;
            if(!used[i]) rcanuse--;
            if(j>i) rcanuse--;
            if(rcanuse<0) continue;
            if(rfixed<0) continue;
            ll need=dp[rem][rcanuse][rfixed];
            if(need>=k)
            {
                ans[i]=j;
                fixed=rfixed; canuse=rcanuse;
                used[j]=true;
                break;
            }
            else k-=need;
        }
    }
    for(int i=1;i<=n;i++) printf("%d%c",ans[i],i==n?'\n':' ');
    return 0;
}
