#include<bits/stdc++.h>
#define MAXN 10000005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
template <class T>
void read(T &x) 
{
	static char ch;static bool neg;
	for(ch=neg=0;ch<'0' || '9'<ch;neg|=ch=='-',ch=getchar());
	for(x=0;'0'<=ch && ch<='9';(x*=10)+=ch-'0',ch=getchar());
	x=neg?-x:x;
}
int t;
__int128 n;
int prime[MAXN],mu[MAXN],cnt[MAXN],phi[MAXN],f[MAXN],g[MAXN];
bool is_prime[MAXN];
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
int sieve(int n)
{
    int p=0;
    for(int i=0;i<=n;i++) is_prime[i]=true;
    is_prime[0]=is_prime[1]=false;
    phi[1]=1; f[1]=1;
    mu[1]=1; g[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) {prime[p++]=i; mu[i]=-1; f[i]=2*i-1; phi[i]=i-1; g[i]=i;}
        for(int j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            mu[i*prime[j]]=i%prime[j]?-mu[i]:0;
            phi[i*prime[j]]=phi[i]*(i%prime[j]?prime[j]-1:prime[j]);
            g[i*prime[j]]=(i%prime[j]?prime[j]:g[i]*prime[j]);
            if(i%prime[j]) f[i*prime[j]]=1LL*f[i]*f[prime[j]]%MOD;
            else if(g[i]==i) f[i*prime[j]]=(1LL*f[i]*prime[j]+phi[i*prime[j]])%MOD;
            else f[i*prime[j]]=1LL*f[i/g[i]]*f[g[i]*prime[j]]%MOD;
            if(i%prime[j]==0) break;
        }
    }
    return p;
}
int sum[MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int main()
{
    sieve(10000000);
    for(int i=1;i<=10000000;i++)
    {
        sum[i]=((3LL*i+3)*f[i]+i)%MOD;
        add(sum[i],sum[i-1]);
    } 
    scanf("%d",&t);
    while(t--)
    {
        read(n);
        int limit=1;
        do  
        {
            __int128 x=limit+1;
            if(x*x*x-1>n) break;  
            limit++;
        }while(true);
        limit--;
        int ans=sum[limit];
        limit++;
        __int128 x=limit;
        x=x*x*x;
        for(int i=1;i<=limit;i++)
        {
            if(limit%i) continue;
            int res=1LL*phi[i]*(int)((n/i-(x-1)/i)%MOD)%MOD;
            add(ans,res);
        }
        printf("%d\n",ans);
    }
    return 0;
}
