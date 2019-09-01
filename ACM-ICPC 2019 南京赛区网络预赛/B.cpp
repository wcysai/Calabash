#include<bits/stdc++.h>
#define MAXN 1000005
#define MOD 1000000007
#define INF 1000000000
using namespace std;
typedef long long ll;
int prime[MAXN],phi[MAXN];
bool is_prime[MAXN];
int T,a,b,m;
int sieve(int n)
{
    int p=0;
    for(int i=0;i<=n;i++) is_prime[i]=true;
    is_prime[0]=is_prime[1]=false;
    memset(phi,0,sizeof(phi));
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
    return p;
}
int pow_mod(int a,int i,int mod)
{
    int s=1%mod;
    while(i)
    {
        if(i&1) s=1LL*s*a%mod;
        a=1LL*a*a%mod;
        i>>=1;
    }
    return s;
}
int c[15],p[15][15];
int get_res(int mod,int iter)
{
    if(mod==1) return 0;
    if(iter==0) return 1%mod;
    if(iter==1) return a%mod;
    if(a<=7&&iter<=c[a]) return p[a][iter]%mod;
    if(a<=7&&iter-1<=c[a]) return pow_mod(a,p[a][iter-1],mod);
    return pow_mod(a,get_res(phi[mod],iter-1)+phi[mod],mod);
}
int main()
{
    sieve(1000000);
    c[2]=4; p[2][1]=2; p[2][2]=4; p[2][3]=16; p[2][4]=65536;
    c[3]=2; p[3][1]=3; p[3][2]=27;
    c[4]=2; p[4][2]=256;
    c[5]=2; p[5][2]=3125;
    c[6]=2; p[6][2]=46656;
    c[7]=2; p[7][2]=823543;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&a,&b,&m);
        if(a==1) printf("%d\n",1%m);
        else printf("%d\n",get_res(m,b));
    }
}
