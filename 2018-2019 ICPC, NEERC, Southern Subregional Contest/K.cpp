/*************************************************************************
    > File Name: K.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-10-20 16:33:50
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
vector<ll> ans;
int main()
{
    scanf("%lld%lld",&n,&k);
    ll s=0;
    for(ll i=0;i<n;i++)
    {
        scanf("%lld",&a[i]);
        s+=a[i];
    }
    if(s%k) {puts("No"); return 0;}
    s/=k;
    ll cur=0,cnt=0;
    for(ll i=0;i<n;i++)
    {
        cur+=a[i];cnt++;
        if(cur>s) {puts("No"); return 0;}
        if(cur==s) {ans.push_back(cnt); cur=0;cnt=0;}
    }
    puts("Yes");
    for(auto it:ans) printf("%lld ",it);
    return 0;
}
