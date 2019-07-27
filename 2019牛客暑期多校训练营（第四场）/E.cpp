#include<bits/stdc++.h>
#define MAXN 105
#define MOD 998244353
using namespace std;
typedef vector<int> vec;
typedef vector<vec> mat;
typedef long long ll;
int T;
ll n,a;
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
int fact[MAXN],invf[MAXN],p2[MAXN];
int comb(int n,int k)
{
    if(n<k) return 0;
    return 1LL*fact[n]*invf[k]%MOD*invf[n-k]%MOD;
}
int dp[MAXN][MAXN];
int main()
{
    fact[0]=invf[0]=p2[0]=1;
    for(int i=1;i<=100;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[100]=pow_mod(fact[100],MOD-2);
    for(int i=99;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    for(int i=0;i<=30;i++)
        for(int j=0;j<=30;j++)
            for(int ii=0;ii<=i;ii++)
                for(int jj=0;jj<=j;jj++)
                    if((ii-jj)%3==0) add(dp[i][j],1LL*comb(i,ii)*comb(j,jj)%MOD);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%lld",&n,&a);
        int even=0,odd=0;
        for(int i=0;i<=60;i++)
            if(a&(1LL<<i))
            {
                if(i&1) odd++;
                else even++;
            }
        int ans=0;
        for(int i=0;i<=odd;i++)
            for(int j=0;j<=even;j++)
            {
                if((i+j)&1) dec(ans,1LL*pow_mod(dp[odd-i][even-j],n)*comb(odd,i)%MOD*comb(even,j)%MOD);
                else add(ans,1LL*pow_mod(dp[odd-i][even-j],n)*comb(odd,i)%MOD*comb(even,j)%MOD);
            }
        printf("%d\n",ans);
    }
    return 0;
}
