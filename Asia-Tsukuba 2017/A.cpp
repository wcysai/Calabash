/*************************************************************************
    > File Name: A.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-10-21 16:03:45
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
ll a,b;
vector<ll> x,y;
int main()
{
    scanf("%lld%lld",&a,&b);
    ll i,j;
    for(i=0;i*(i+1)/2<=a+b;i++);
    i--;
    ll sum1=0,sum2=0;
    for(ll k=i;k>=1;k--)
    {
        if(sum1+k<=a) {x.push_back(k); sum1+=k;}
        else {y.push_back(k); sum2+=k;}
    }
    printf("%lld\n",(ll)x.size());
    for(auto it:x) printf("%lld ",it);
    puts("");
    printf("%lld\n",(ll)y.size());
    for(auto it:y) printf("%lld ",it);
    return 0;
}


