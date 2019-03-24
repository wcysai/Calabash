#include<bits/stdc++.h>
#define MAXN 10000005
#define MAXP 2000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int fact[MAXN],invf[MAXN],phi[MAXN],prime[MAXP];
bool is_prime[MAXN];
int T,n,m,ans;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
void sieve(int n)
{
    memset(is_prime,true,sizeof(is_prime));
    memset(phi,0,sizeof(phi));
    is_prime[0]=is_prime[1]=true;
    phi[1]=1;
    int p=0;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) {prime[p++]=i; phi[i]=i-1;}
        for(int j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            phi[prime[j]*i]=phi[i]*(i%prime[j]?(prime[j]-1):prime[j]);
            if(i%prime[j]==0) break;
        }
    }
}
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
int comb(int n,int k)
{
    if(n<k) return 0;
    return 1LL*fact[n]*invf[k]%MOD*invf[n-k]%MOD;
}
int find_ans(int x)
{
    if(x!=1) 
    {
        if(n%x) return 0;
        return comb(n/x-1,m/x-1);
    }
    int ret=comb(n-1,m-1);
    dec(ret,1LL*m*comb(n-(n-1)/2-1,m-1)%MOD);
    return ret;
}
int main()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<=10000000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[10000000]=pow_mod(fact[10000000],MOD-2);
    for(int i=9999999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    sieve(10000000);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m); ans=0;
        //counting rotation
        for(int j=1;j*j<=m;j++)
        {
            if(m%j) continue;
            add(ans,1LL*phi[j]*find_ans(j)%MOD);
            if(j*j!=m) add(ans,1LL*phi[m/j]*find_ans(m/j)%MOD);
        }
        //reverse plus rotation
        //1 fixed point + (m-1)/2 fixed pairs
        if(m&1)
        {
            int ret;
            if(n%2==0)
            {
                ret=comb(n/2-1,(m+1)/2-1);
                dec(ret,comb(n/2-(n/2-1)/2-1,(m+1)/2-1));
                ret=1LL*ret*m%MOD;
            }
            else
            {
                ret=comb((n+1)/2-1,(m+1)/2-1);
                dec(ret,comb((n+1)/2-((n+1)/2)/2-1,(m+1)/2-1));
                ret=1LL*ret*m%MOD;
            }
            add(ans,ret);
        }
        else
        {
            // case 1: m/2 fixed pairs
            // case 2: 2 fixed points + m/2-1 fixed pairs
            if(n%2==0) add(ans,1LL*(m/2)*comb(n/2-1,m/2-1)%MOD);
            if(n&1)
            {
                int ret=comb((n+1)/2-1,m/2);
                dec(ret,comb((n+1)/2-((n-1)/2)/2-1,m/2)); 
                dec(ret,comb((n+1)/2-((n+1)/2)/2-1,m/2));
                ret=2LL*ret%MOD;
                add(ans,1LL*(m/2)*ret%MOD);
            }
            else
            {
                int ret=comb(n/2-1,m/2);
                dec(ret,2LL*comb(n/2-(n/2-1)/2-1,m/2)%MOD);
                add(ret,comb(n/2,m/2));
                dec(ret,2LL*comb(n/2-(n/2)/2,m/2)%MOD);
                add(ans,1LL*(m/2)*ret%MOD);
            }
        }
        ans=1LL*ans*pow_mod(2*m,MOD-2)%MOD;
        printf("%d\n",ans);
    }
    return 0;
}
