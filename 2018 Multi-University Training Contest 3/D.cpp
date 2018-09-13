/*************************************************************************
    > File Name: D.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-07-30 12:07:25
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,k;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&k);
        if(k==1) puts("5");
        else if(k==2) puts("7");
        else printf("%d\n",k+5);
    }
    return 0;
}

