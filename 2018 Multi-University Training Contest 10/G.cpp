/*************************************************************************
    > File Name: G.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-08-22 12:26:46
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n;
int a[MAXN];
int main()
{
    a[1]=a[2]=0;
    a[3]=a[4]=1;
    int now=1;
    for(int i=5;i<=100000;i++)
    {
        a[i]=(1LL*(i-2)*a[i-1]+1LL*(i-1)*a[i-2]+now)%MOD;
        now=-now;
    }
    scanf("%d",&T);
    for(int i=0;i<T;i++)
    {
        scanf("%d",&n);
        printf("%d\n",a[n]);
    }
    return 0;
}
