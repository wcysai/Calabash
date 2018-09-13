/*************************************************************************
    > File Name: D.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-08-20 12:24:05
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
ll t,a,b,c,A,B,C;
ll gcd(ll a,ll b) {if(b==0) return a; return gcd(b,a%b);}
int main()
{
    scanf("%lld",&t);
    while(t--)
    {
        scanf("%lld%lld%lld",&a,&b,&c);
        scanf("%lld%lld%lld",&A,&B,&C);
        ll res=a*B+b*C+c*A-a*C-b*A-c*B;
        ll sum=a+b+c;
        ll g=gcd(sum,res);
        res/=g;sum/=g;
        if(g<0) {res=-res; sum=-sum;}
        if(sum==1) printf("%lld\n",res);
        else printf("%lld/%lld\n",res,sum);
    }
    return 0;
}
