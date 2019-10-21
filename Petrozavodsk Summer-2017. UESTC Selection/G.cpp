#include<bits/stdc++.h>
#define MAXN 2000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,m,k;
int fact[MAXN],invf[MAXN];
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
int peanut(int n,int m)
{
    return comb(n+1,m+1);
}
int difpeanut(int l,int r,int m)
{
    int res=peanut(r,m);
    dec(res,peanut(l-1,m));
    return res;
}
int peanut2(int n,int m)
{
    return 1LL*(m+1)*comb(n+2,m+2)%MOD;
}
int solve2(int n,int m)
{
    int ans=peanut(n/2-1,m-2);
    add(ans,difpeanut(1,n/2,m-2));
    return 1LL*ans*n%MOD;
}
int solve1(int n,int m)
{
    int ans=1LL*(n-1)*peanut(n/2-1,m-3)%MOD;
    dec(ans,peanut2(n/2-1,m-3));
    ans=1LL*ans*n%MOD;
    dec(ans,2LL*solve2(n,m)%MOD);
    return ans;
}
int main()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<=2000000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[2000000]=pow_mod(fact[2000000],MOD-2);
    for(int i=1999999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&k);
        if(k>3) {puts("0"); continue;}
        if(k==3)
        {
            if(m!=3) {puts("0"); continue;}
            int res=1LL*n*(n-1)%MOD*(n+1)%MOD*pow_mod(24,MOD-2)%MOD;
            printf("%d\n",res);
            continue;
        }
        else if(k==2)
        {
            if(m==3)
            {
                int res=comb(n,3);
                dec(res,1LL*n*(n-1)%MOD*(n+1)%MOD*pow_mod(24,MOD-2)%MOD);
                printf("%d\n",res);
                continue;
            }
            else printf("%d\n",solve2(n,m));
        }
        else if(m==3) {puts("0"); continue;}
        else if(k==1) printf("%d\n",solve1(n,m));
        else
        {
            int ans=comb(n,m);
            dec(ans,solve2(n,m)); dec(ans,solve1(n,m));
            printf("%d\n",ans);
        }
    }
    return 0;
}
