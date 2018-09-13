/*************************************************************************
    > File Name: B.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-08-31 12:24:16
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
string s[55];
int a[55][25];
int dp[22][55][55][30]; //dp[i][l][r][cur]: string [l,r), at pos i, filling char>=cur
void _mod(int &x,int y) {x+=y; if(x>=MOD) x-=MOD;}
int solve(int p,int l,int r,int ch)
{
    if(p==m) return l+1==r;
    if(l==r) return 1;
    if(ch==27) return 0;
    if(dp[p][l][r][ch]!=-1) return dp[p][l][r][ch];
    for(int i=l;i<r;i++)
        if(a[i][p]!=-1&&a[i][p]<ch) return dp[p][l][r][ch]=0;
    int ans=solve(p,l,r,ch+1);
    for(int i=l;i<r;i++)
    {
        if(a[i][p]==-1&&ch==0) break;
        if(a[i][p]!=-1&&a[i][p]>ch) break;
        _mod(ans,1LL*solve(p+1,l,i+1,0)*solve(p,i+1,r,ch+1)%MOD);
    }
    return dp[p][l][r][ch]=ans;
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++) 
    {
        cin>>s[i]; m=max(m,(int)s[i].size());
        for(int j=0;j<(int)s[i].size();j++)
        {
            if(s[i][j]=='?') a[i][j]=-1;
            else a[i][j]=s[i][j]-'a'+1;
        }
    }
    memset(dp,-1,sizeof(dp));
    printf("%d\n",solve(0,0,n,0));
    return 0;
}
