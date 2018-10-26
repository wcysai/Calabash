/*************************************************************************
    > File Name: F.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-10-26 14:36:44
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 2005
#define MAXM 12
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,MOD,a[MAXN];
int dp[MAXN][MAXM];
void cnn(vector<int> &a)
{
    map<int,int> mp;mp.clear();int tot=0;
    for(auto it:a) 
        if(it!=0) 
        {
            if(mp.find(it)!=mp.end()) mp[it]=++tot;
        }
    for(int i=0;i<(int)a.size();i++)
        if(a[i]!=0) a[i]=mp[a[i]];
}
int main()
{
    scanf("%d%d%d",&n,&m,&MOD);
    return 0;
}

