#include<bits/stdc++.h>
#define MAXN 305
#define INF 1000000000
#define MOD 1000000007
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
string str[MAXN];
int dp[MAXN][MAXN*MAXN];
struct node
{
    int F,S,len;
};
node a[MAXN];
bool cmp(node x,node y)
{
    int min1=min(x.S,x.F+y.S),min2=min(y.S,y.F+x.S);
    if(min1!=min2) return min1>min2;
    if(x.S!=y.S) x.S<y.S;
    if(x.F!=y.F) return x.F>y.F;
    return x.len>y.len;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        cin>>str[i];
        int cnt1=0,cnt2=0;
        for(int j=0;j<str[i].size();j++)
        {
            if(str[i][j]=='(') cnt2++; else cnt2--;
            cnt1=min(cnt1,cnt2);
        }
        a[i]=(node){cnt2,cnt1,str[i].size()};
    }
    sort(a+1,a+n+1,cmp);
    for(int i=0;i<=n;i++)
        for(int j=0;j<=300*300;j++)
            dp[i][j]=-INF;
    dp[0][0]=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<=300*300;j++)
        {
            if(dp[i][j]==-INF) continue;
            dp[i+1][j]=max(dp[i+1][j],dp[i][j]);
            if(j+a[i+1].S>=0) dp[i+1][j+a[i+1].F]=max(dp[i+1][j+a[i+1].F],dp[i][j]+a[i+1].len);
        }
    }
    printf("%d\n",dp[n][0]);
}
