#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define INV 500000004
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,N,X;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int fact[MAXN],invf[MAXN];
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
    for(int i=1;i<=1000000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[1000000]=pow_mod(fact[1000000],MOD-2);
    for(int i=999999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&N,&X);
        X=min(X,N);
        int ans=fact[N];
        for(int j=X+1;j<=N;j++) dec(ans,1LL*fact[N-j]*comb(N,j)%MOD*fact[j-1]%MOD);
        printf("%d\n",1LL*ans*pow_mod(fact[N],MOD-2)%MOD);
    }
    return 0;
}
