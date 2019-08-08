#include<bits/stdc++.h>
#define MAXN 10005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
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
int T,N,M;
int main()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<=10000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[10000]=pow_mod(fact[10000],MOD-2);
    for(int i=9999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&N,&M);
        int ans=0;
        for(int i=1;i<=N;i++)
        {
            int s=N-M*i;
            if(s<0) break;
            for(int j=0;j<=s;j++)
            {
                add(ans,comb(j+2*i-1,2*i-1));
                if(j>=i) dec(ans,comb(j+i-1,2*i-1));
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
