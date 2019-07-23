/*************************************************************************
    > File Name: G.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-08-02 12:07:12
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
ll c,n;
int main()
{
    scanf("%lld%lld",&c,&n);
    if(c>n) {puts("-1"); return 0;}
    if(n/c==1) {printf("%lld\n",c*c); return 0;}
    ll ans=c*c*(n/c)*(n/c-1);
    printf("%lld\n",ans);
    return 0;
}
