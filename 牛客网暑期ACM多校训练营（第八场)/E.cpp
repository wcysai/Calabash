/*************************************************************************
    > File Name: E.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-08-11 15:26:44
 ************************************************************************/
 
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 15
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,m,K;
P a[MAXN],b[MAXN];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&K);
        for(int i=1;i<=K;i++)
            scanf("%d%d%d%d",&a[i].F,&a[i].S,&b[i].F,&b[i].S);
        if(n%2==0||m%2==0) { printf("%d\n",n*m); continue;}
        int ans=n*m+1;
        for(int i=1;i<=K;i++)
        {
            if(a[i].F==b[i].F&&a[i].S==b[i].S) continue;
            if((a[i].F+a[i].S)%2==0&&(b[i].F+b[i].S)%2==0) {ans--; break;}
        }
        printf("%d\n",ans);
    }
    return 0;
}
