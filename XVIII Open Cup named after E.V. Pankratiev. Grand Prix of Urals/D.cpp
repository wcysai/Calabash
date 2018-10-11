#include<bits/stdc++.h>
#define MAXN 6000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
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
int n;
int fact[MAXN],invf[MAXN];
int comb(int n,int k)
{
    return 1LL*fact[n]*invf[k]%MOD*invf[n-k]%MOD;
}
int main()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<=6000000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[6000000]=pow_mod(fact[6000000],MOD-2);
    for(int i=5999999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    scanf("%d",&n);
    if(n%2==0) {printf("%d\n",pow_mod(10,n/2)); return 0;}
    int ans=0;
    for(int i=0;i<=4;i++)
    {
        int m=(((n-1)/2)/2)*9+i;
        int now=0,cur=1;
        for(int j=0;j<=n/2;j++)
        {
            if(m<10*j) break;
            now=(now+1LL*cur*comb(n/2+m-10*j-1,m-10*j)*comb(n/2,j))%MOD;
            if(now<0) now+=MOD;
            cur=-cur;
        }
        ans+=now;if(ans>=MOD) ans-=MOD;
        //printf("%d\n",now);
    }
    printf("%d\n",ans);
    return 0;
}
