/*************************************************************************
    > File Name: D.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-07-28 13:00:06
 ************************************************************************/
 
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 205
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,t,a[MAXN][MAXN];
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        memset(a,0,sizeof(a));
        scanf("%d",&n);
        if(n&1) {puts("impossible"); continue;}
        puts("possible");
        for(int i=1;i<=n/2;i++)
            for(int j=1;j<=n+1-i;j++)
                a[i][j]=1;
        for(int i=n/2+1;i<=n;i++)
        {
            int num=i-n/2;
            for(int j=n;j>=num+1;j--)
                a[i][j]=-1;
        }
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
                printf("%d ",a[i][j]);
            puts("");
        }
    }
    return 0;
}
