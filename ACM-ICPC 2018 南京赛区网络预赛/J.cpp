/*************************************************************************
    > File Name: J.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-09-01 12:19:49
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 20000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n;
int prime[MAXN],g[MAXN],f[MAXN];
bool is_prime[MAXN];
int sieve(int n)
{
    int p=0;
    for(int i=0;i<=n;i++) is_prime[i]=true;
    is_prime[0]=is_prime[1]=false;
    g[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) {prime[p++]=i; g[i]=2;}
        for(int j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            if(i%prime[j]==0) 
            {
                if(g[i]==0) g[i*prime[j]]=0;
                else if((i/prime[j])%prime[j]==0) g[i*prime[j]]=0;
                else g[i*prime[j]]=g[i]/2;
                break;
            }
            else g[i*prime[j]]=g[i]*2;
        }
    }
    for(int i=1;i<=n;i++) f[i]=f[i-1]+g[i];
    return p;
}
int main()
{
    sieve(20000000);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        printf("%d\n",f[n]);
    }
    return 0;
}
