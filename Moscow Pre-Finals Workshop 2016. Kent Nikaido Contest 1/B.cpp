#include<bits/stdc++.h>
#define MAXN 2000005
#define INF 1000000000
#define MOD 1000000007
#define F firstt
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int N,K,L;
int p[MAXN],fact[MAXN],invf[MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
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
int main()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<=2000000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[2000000]=pow_mod(fact[2000000],MOD-2);
    for(int i=1999999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    scanf("%d%d%d",&N,&K,&L);
    p[0]=1;
    for(int i=1;i<=2000000;i++) p[i]=1LL*p[i-1]*K%MOD;
    if(N==L)
    {
        int ans=0;
        for(int i=1;i<=L;i++)
        {
            int g=__gcd(i,L);
            add(ans,1LL*p[g]);
        }
        ans=1LL*ans*pow_mod(L,MOD-2)%MOD;
        printf("%d\n",ans);
    }
    else
    {
        int ans=0;
        if(L%2==0)
        {
            add(ans,comb(N+K-1,K-1));
        }
        else
        {
            add(ans,comb(N+K-1,K-1));
            add(ans,comb(K,N));
        }
        printf("%d\n",ans);
    }
    return 0;
}
