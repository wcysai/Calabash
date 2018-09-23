/*************************************************************************
    > File Name: L.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-09-24 00:01:55
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
ll T;
ll check(ll l,ll r)
{
    ll ret=0;
    while(l<r&&a[l]==a[r]) ret+=a[l],l++,r--;
    if(l>r) return ret;
    while(l<r)
    {
        if(a[l]!=a[l+1]&&a[r]!=a[r-1]) return -1;
        if(a[l]==a[l+1]) ret+=a[l],l+=2; else ret+=a[r],r-=2;
    }
    return ret;
}
int main()
{
    scanf("%lld",&T);
    while(T--)
    {
        scanf("%lld",&n);
        ll s=0;
        for(ll i=1;i<=n;i++)
        {
            scanf("%lld",&a[i]);
            s^=a[i];
        }
        if(s==0) {puts("Draw"); continue;}
        for(ll j=32;j>=0;j--)
            if((s>>j)&1) {k=j; break;}
        for(ll i=1;i<=n;i++) a[i]=(a[i]>>k)&1;
        if(n%2==0) {puts("First"); continue;}
        if(a[1]==0&&a[n]==0) {puts("Second"); continue;}
        if((a[1]==1&&check(2,n)%2==0)||(a[n]==1&&check(1,n-1)%2==0)) puts("First"); else puts("Second");
    }
    return 0;
}

