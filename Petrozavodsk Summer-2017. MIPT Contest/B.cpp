#include<bits/stdc++.h>
#define MAXN (1<<20)
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN];
int dp[MAXN];
int query(int x,int t)
{
    int mask=0;
    for(int i=19;i>=0;i--)
    {
        if(!((x>>i)&1))
        {
            if(dp[mask^(1<<i)]<=t) mask^=(1<<i);
        }
    }
    return (x^mask)+mask;
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<(1<<20);i++) dp[i]=n+1;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);a[i]^=a[i-1];
        dp[a[i]]=min(dp[a[i]],i);
    }
    for(int i=0;i<20;i++)
        for(int j=(1<<20)-1;j>=0;j--)
            if(!((j>>i)&1)) dp[j]=min(dp[j^(1<<i)],dp[j]);
    //assert(0);
    //for(int i=1;i<=n;i++) query(a[i],i);
    for(int i=1;i<=n;i++) printf("%d%c",query(a[i],i),i==n?'\n':' ');
    return 0;
}
