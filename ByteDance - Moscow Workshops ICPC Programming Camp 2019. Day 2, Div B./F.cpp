/*************************************************************************
    > File Name: E.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-10-03 19:07:03
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 2005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
int a[MAXN];
ll sum[MAXN];
ll dp[MAXN][MAXN];
int A[MAXN][MAXN];
string str[MAXN];
void solve(int l,int r)
{
    if(l==r) return;
    int mid=A[l][r];
    for(int i=l;i<=mid;i++) str[i]=str[i]+'0';
    for(int i=mid+1;i<=r;i++) str[i]=str[i]+'1';
    solve(l,mid);solve(mid+1,r);
}
int main()
{
    scanf("%d",&n);for(ll i=1;i<=n;i++) scanf("%d",&a[i]);
    for(ll i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
    for(ll i=1;i<=n-1;i++)
    {
        dp[i][i+1]=a[i]+a[i+1];
        A[i][i+1]=i;
    }
    for(ll l=3;l<=n;l++)
    {
        for(ll i=1;i+l-1<=n;i++)
        {
            ll j=i+l-1;
            ll lp=A[i][j-1],rp=A[i+1][j];
            int opt=lp-1;
            ll ans=INF;
            for(ll k=lp;k<=rp;k++)
            {
                if(sum[j]-sum[i-1]+dp[i][k]+dp[k+1][j]<ans)
                {
                    ans=sum[j]-sum[i-1]+dp[i][k]+dp[k+1][j];
                    opt=k;
                }
            }
            A[i][j]=opt;dp[i][j]=ans;
        }
    }
    solve(1,n);
    for(int i=1;i<=n;i++) cout<<str[i]<<endl;
    return 0;
}

