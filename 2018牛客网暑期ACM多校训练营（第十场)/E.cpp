/*************************************************************************
    > File Name: E.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-08-19 14:50:31
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
int t,n,M,k,a[MAXN];
int prime[MAXN],miu[MAXN],f[MAXN],g[MAXN],inv[MAXN];
int bucket[MAXN];
bool is_prime[MAXN];
vector<int> factor[MAXN];
int gcd(int a,int b) {if(b==0) return a; return gcd(b,a%b);}
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
void genmiu(int n)
{
    int p=0;
    memset(is_prime,true,sizeof(is_prime));
    memset(miu,0,sizeof(miu));
    is_prime[0]=is_prime[1]=false;
    miu[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) {prime[p++]=i; miu[i]=-1;}
        for(int j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            miu[i*prime[j]]=i%prime[j]?-miu[i]:0;
            if(i%prime[j]==0) break;
        }
    }
}
int main()
{
    genmiu(100000);
    scanf("%d",&t);
    for(int i=1;i<=100000;i++)
        for(int j=i;j<=100000;j+=i)
            factor[j].push_back(i);
    inv[1]=1;
    for(int i=2;i<=100000;i++)
        inv[i]=1LL*(MOD-MOD/i)*inv[MOD%i]%MOD;
    while(t--)
    {
        memset(bucket,0,sizeof(bucket));
        memset(f,0,sizeof(f));
        scanf("%d%d",&n,&M);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
        {
            for(int j=0;j<(int)factor[a[i]].size();j++)
                bucket[factor[a[i]][j]]++;
        }
        int ans=0;
        for(int i=1;i<=M;i++)
        {
            int res=0;
            for(int j=0;j<(int)factor[i].size();j++)
            {
                int p=factor[i][j];
                f[p]=pow_mod(1+i,bucket[p])-1;
                if(f[p]<0) f[p]+=MOD;
                f[p]=1LL*f[p]*inv[i]%MOD;
            }
            for(int j=0;j<(int)factor[i].size();j++)
            {
                int p=factor[i][j];g[p]=0;
                int d=i/p;
                for(int k=0;k<(int)factor[d].size();k++)
                {
                    int v=factor[d][k];
                    g[p]=(g[p]+miu[v]*f[p*v]);
                    if(g[p]>=MOD) g[p]-=MOD;
                    if(g[p]<0) g[p]+=MOD;
                }
                res=(res+1LL*p*g[p])%MOD;
                if(res>=MOD) res-=MOD;
            }
            //printf("%d\n",res);
            ans^=res;
        }
        printf("%d\n",ans);
    }
    return 0;
}
