/*************************************************************************
    > File Name: E.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-09-02 14:09:43
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
ll n,k,a[MAXN];
int main()
{
    scanf("%lld",&n);
    for(ll i=0;i<n;i++) scanf("%lld",&a[i]);
    sort(a,a+n);
    ll cur=0,ans=0;
    for(ll i=0;i<n;i++)
    {
        if(a[i]>cur)
        {
            cur+=a[i];
            ans++;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
