/*************************************************************************
    > File Name: I.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-08-22 12:17:13
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 40000005
#define MAXP 3000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,k,a[MAXN];
int gcd(int a,int b) {if(b==0) return a; return gcd(b,a%b);}
int prime[MAXP],phi[MAXN];
ll ans[MAXN/2];
bool is_prime[MAXN];
void genphi(int n)
{
    int p=0;
    memset(phi,0,sizeof(phi));
    memset(is_prime,true,sizeof(is_prime));
    is_prime[0]=is_prime[1]=false;
    phi[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) {prime[p++]=i; phi[i]=i-1;}
        for(int j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            phi[i*prime[j]]=phi[i]*(i%prime[j]?prime[j]-1:prime[j]);
            if(i%prime[j]==0) break;
        }
    }
    //printf("%d\n",p);
}
int main()
{
    genphi(40000000);
    for(int i=1;i<=20000000;i++)
        ans[i]=ans[i-1]+phi[2*i]/2;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        printf("%lld\n",ans[n]);
    }
    return 0;
}
