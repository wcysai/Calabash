#include<bits/stdc++.h>
#define MAXN 1000005
#define MOD 1000000007
#define INF 1000000000
using namespace std;
typedef long long ll;
int prime[MAXN],phi[MAXN],miu[MAXN];
bool is_prime[MAXN];
int sieve(int n)
{
    int p=0;
    for(int i=0;i<=n;i++) is_prime[i]=true;
    is_prime[0]=is_prime[1]=false;
    memset(miu,0,sizeof(miu));
    miu[1]=1;
    memset(phi,0,sizeof(phi));
    phi[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) {prime[p++]=i; phi[i]=i-1; miu[i]=-1;}
        for(int j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            miu[i*prime[j]]=i%prime[j]?-miu[i]:0;
            phi[i*prime[j]]=phi[i]*(i%prime[j]?prime[j]-1:prime[j]);
            if(i%prime[j]==0) break;
        }
    }
    return p;
}
int main()
{
    sieve(1000000);
    int x;
    while(scanf("%d",&x)==1)
    {
        int ans=0;
        for(int i=1;i*i<=x;i++)
        {
            if(x%i) continue;
            ans+=i*i*miu[x/i];
            if(i*i!=x) ans+=(x/i)*(x/i)*miu[i];
        }
        printf("%d\n",ans);
    }
}
