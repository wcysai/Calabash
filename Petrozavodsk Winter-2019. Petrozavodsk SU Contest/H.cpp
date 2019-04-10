#include<bits/stdc++.h>
#define MAXN 305
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k;
int fact[MAXN],invf[MAXN];
int t[MAXN],f[MAXN],g[MAXN];
vector<P> v;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD; if(a<0) a+=MOD;}
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
    for(int i=1;i<=300;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[300]=pow_mod(fact[300],MOD-2);
    for(int i=299;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",&t[i]);
    for(int i=1;i<=n;i++) v.push_back(P(t[i],i));
    sort(v.begin(),v.end());
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            int p=0;
            if(n-j-1>=k-1)
            {
                int greater=n-j-1;
                int less=j-1;
                for(int before=k-1;before<=greater;before++)
                    add(p,1LL*comb(greater,before)*fact[before+1]%MOD*fact[greater-before]%MOD*comb(n,less)%MOD*fact[less]%MOD);
            }
            add(f[v[j].S],1LL*(fact[n]-p)*v[i].F%MOD);
            add(f[v[i].S],1LL*p*v[j].F%MOD);
            add(g[v[i].S],p);
        }
    }
    for(int i=1;i<=n;i++)
    {
        add(f[i],1LL*fact[n]*t[i]%MOD);
        printf("%lld ",1LL*f[i]*g[i]%MOD);
    }   
    return 0;
}
