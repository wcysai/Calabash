/*************************************************************************
    > File Name: K.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-08-20 12:10:44
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,a,b,c,d;
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d%d",&a,&b,&c,&d);
        int noball=pow_mod(2,b);
        int noracket=1LL*(b+d+1)*pow_mod(2,c)%MOD;
        int noall=b+1;
        int ans=noball+noracket-noall;
        if(ans>=MOD) ans-=MOD;
        if(ans<0) ans+=MOD;
        ans=1LL*ans*pow_mod(2,a)%MOD;
        printf("%d\n",ans);
    }
    return 0;
}
