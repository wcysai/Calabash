/*************************************************************************
    > File Name: E.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-08-16 12:09:11
 ************************************************************************/
 
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,p[MAXN],pp[MAXN][MAXN];
int pre[MAXN];
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
int rev;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) pre[i]=pow_mod(i,m);
    rev=pow_mod(100,MOD-2);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&p[i]);
        p[i]=1LL*p[i]*rev%MOD;
    }
    for(int i=1;i<=n;i++)
    {
        pp[i][1]=p[i];
        for(int j=2;j+i-1<=n;j++)
            pp[i][j]=1LL*pp[i][j-1]*p[i+j-1]%MOD;
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;i+j-1<=n;j++)
        {
            int res=pp[i][j];
            if(i!=1) res=1LL*res*(1-p[i-1]+MOD)%MOD;
            if(i+j-1!=n) res=1LL*res*(1-p[i+j]+MOD)%MOD;
            ans=(ans+1LL*res*pre[j])%MOD;
        }
    }
    printf("%d\n",ans);
    return 0;
}
