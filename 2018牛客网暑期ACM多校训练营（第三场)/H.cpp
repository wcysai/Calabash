/*************************************************************************
    > File Name: H.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-07-26 12:03:08
 ************************************************************************/
 
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 10000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k;
int prime[MAXN];
bool is_prime[MAXN];
int cnt[MAXN];
int sieve(int n)
{
    int p=0;
    for(int i=0;i<=n;i++) is_prime[i]=true;
    is_prime[0]=is_prime[1]=false;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) prime[p++]=i;
        for(int j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            if(i%prime[j]==0) break;
        }
    }
    cnt[0]=cnt[1]=0;
    for(int i=2;i<=n;i++)
    {
        cnt[i]=cnt[i-1];
        if(is_prime[i]) cnt[i]++;
    }
    return p;
}
int main()
{
    sieve(10000000);
    scanf("%d",&n);
    ll ans=0;
    for(int i=1;i<=n;i++)
    {
        int res=n/i;
        ans+=1LL*cnt[res]*cnt[res]-cnt[res];
    }
    printf("%lld\n",ans);
    return 0;
}
