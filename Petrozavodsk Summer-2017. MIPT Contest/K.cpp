#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,m;
int fact[MAXN],invf[MAXN];
int cnt[MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
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
    for(int i=1;i<=1000000;i++) fact[i]=1LL*i*fact[i-1]%MOD;
    invf[1000000]=pow_mod(fact[1000000],MOD-2);
    for(int i=999999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    scanf("%d%d%d",&n,&k,&m);
    int s=0,ans=0;
    for(int i=1;i<=n-k-1;i++)
    {
        int cnt=comb(n-k+m-2-i,m-2);
        add(ans,1LL*cnt*i%MOD);
    }
    s=(comb(n-k+m,m)-comb(n-k+m-1,m-1)+MOD)%MOD;
    add(ans,s);
    printf("%d\n",ans);
    return 0;
}
