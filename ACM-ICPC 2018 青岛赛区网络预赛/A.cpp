/*************************************************************************
    > File Name: A.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-09-16 12:05:59
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
int T,n,m;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        if(n==m) printf("%d %d\n",n,n);
        else if(m==0) printf("%d %d\n",0,0);
        else printf("%d %d\n",m,(m-1)/(n-m+1)+1);
    }
    return 0;
}

