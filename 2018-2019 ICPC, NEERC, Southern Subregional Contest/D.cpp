/*************************************************************************
    > File Name: D.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-10-20 16:11:11
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll n,k,a[MAXN],b[MAXN];
int main()
{
    scanf("%lld%lld",&n,&k);
    for(ll i=0;i<n;i++) scanf("%lld",&a[i]);
    if(n==1) {printf("%lld\n",(a[0]+k-1)/k); return 0;}
    ll ans=0;
    for(ll i=0;i<n;i++)
    {
        if(b[i]) {ans++; a[i]-=min(a[i],k-b[i]);}
        ans+=a[i]/k;
        b[i+1]=a[i]%k;
    }
    if(b[n]) ans++;
    printf("%lld\n",ans);
    return 0;
}
