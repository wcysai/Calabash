/*************************************************************************
    > File Name: 7.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-10-15 22:18:53
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
vector<P> G[MAXN];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++)
    {
        int x;scanf("%d",&x);
        for(int j=0;j<x;j++)
        {
            P p;
            scanf("%d%d",&p.S,&p.F);
            G[i].push_back(p);
        }
        sort(G[i].begin(),G[i].end());
    }
    return 0;
}

