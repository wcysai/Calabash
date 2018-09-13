/*************************************************************************
    > File Name: B.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-08-25 13:45:47
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define rep(i, n) for (int i=0; i<(n); i++)
#define Rep(i, n) for (int i=1; i<=(n); i++)
#define range(x) (x).begin(), (x).end()
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const int MAXN=1000005;
int BLOCK;
int T,n,k,N,a[MAXN],ans;
int prime[MAXN],phi[MAXN],miu[MAXN],g[MAXN],f[MAXN];
bool is_prime[MAXN];
vector<P> fact;
unordered_map<int,int> mp;
int gcd(int a,int b) {if(b==0) return a; return gcd(b,a%b);}
int _mod(int x) {if(x>=MOD) return x-MOD; else if(x<0) return x+MOD; else return x;}


namespace lagrange {

    typedef long long LL;
    typedef unsigned long long ULL;
    ULL n, k;

    constexpr LL m = 1000000007;

#define pow owahgrauhgso
    ULL powmod(ULL b, ULL e) {
      ULL r = 1;
      while (e) {
        if (e & 1) r = r * b % m;
        b = b * b % m;
        e >>= 1;
      }
      return r;
    }

    const int MAXN = 128;
    ULL inv[MAXN];
    ULL poww[MAXN][MAXN];

    void init() {
      inv[1] = 1;
      for (int i = 2; i <= 100; i++) 
        inv[i] = (m - m / i) * inv[m % i] % m; 
      for (int i = 0; i < 100; i++) {
          for (int j = 0; j < 100; j++) {
            poww[i][j] = powmod(i, j);
          }
      }
    }
    
    ULL pow[MAXN];

    void fake_sieve() {
      Rep (i, k + 1) pow[i] = poww[i][k];
      /*
      pow[1] = 1;
      Rep (i, k + 1) pow[i] = powmod(i, k);
      */
    }

    ULL sum[MAXN];
    ULL ans[MAXN];

    auto addmod = [](ULL a, ULL b) -> ULL {return (a+b)%m;};

    ULL lagrange() {
      ULL p;
      p = 1;
      for (int i=0; i<=k+1; i++) {
        if (i) p = p * inv[i] % m;
        ans[i] = (k+1-i)&1 ? m-sum[i] : sum[i];
        ans[i] = ans[i] * p % m;
        p = p * (m + n - i) % m;
      }
      p = 1;
      for (int i=k+1; i>=0; i--) {
        if (k+1-i) p = p * inv[k+1-i] % m;
        ans[i] = ans[i] * p % m;
        p = p * (m + n - i) % m;
      }
      return accumulate(ans, ans+k+2, 0, addmod); 
    }

    ULL powsum(int N, int _n) {
      k = N; n = _n;
      fake_sieve();
      partial_sum(pow, pow+k+2, sum, addmod);
      return lagrange();
    } 

#undef pow

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
int genmiu(int n)
{
    int p=0;
    memset(is_prime,true,sizeof(is_prime));
    is_prime[0]=is_prime[1]=false;
    miu[1]=1;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) {prime[p++]=i; miu[i]=-1;}
        for(int j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[i*prime[j]]=false;
            miu[i*prime[j]]=i%prime[j]?-miu[i]:0;
            if(i%prime[j]==0) break;
        }
    }
    return p;
}
void genf(int n,int N)
{
    ll p=0;
    g[1]=1;
    for(ll i=2;i<=n;i++)
    {
        if(is_prime[i]) {p++; g[i]=pow_mod(i,N)-1;}
        for(ll j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            if(i%prime[j]==0)
            {
                g[i*prime[j]]=1LL*g[i]*pow_mod(prime[j],N)%MOD;
                break;   
            }
            else g[i*prime[j]]=1LL*g[i]*(pow_mod(prime[j],N)-1)%MOD;
        }
    }
    for(ll i=1;i<=n;i++) f[i]=_mod(f[i-1]+g[i]);
}
int calc(int cur)
{
    int res;
    res=(int)lagrange::powsum(N,cur);
    //calculate here sigma 1^N+...+((n)/cur)^N
    return res;
}
void dfs(int now,int limit,int sgn,int cur)
{
    if(now==limit)
    {
        ans=_mod(ans+sgn*calc(n/cur));
        return;
    }
    for(int i=0;i<=min(fact[now].S,1);i++)
    {
        if(i==0) dfs(now+1,limit,sgn,cur);
        if(i==1) dfs(now+1,limit,-sgn,cur*fact[now].F);
    }
}
int get(int x)
{
    if(x<=BLOCK) return f[x];
    if(mp.find(x)!=mp.end()) return mp[x];
    int res=calc(x);
    for(ll i=2,r;i<=x;i=r+1)
    {
        r=x/(x/i);
        res=_mod(res-1LL*get(x/i)*(r-i+1)%MOD);
    }
    return mp[x]=res;
}
int main()
{
    int p=genmiu(1000000);
    lagrange::init();
    scanf("%d",&T);
    int kase=0;
    while(T--)
    {
        kase++;mp.clear();
        scanf("%d%d",&k,&n);
        int G=0;N=0;
        for(int i=1;i<=k;i++)
        {
            scanf("%d",&a[i]);
            if(a[i]==-1) N++; else G=gcd(G,a[i]);
        }
        ans=0;
        if(G!=0)
        {
            fact.clear();
            int tot=G;
            for(int i=0;i<p;i++)
            {
                if(tot==1) break;
                if(tot<=1000000&&is_prime[tot]) break;
                int cnt=0;
                while(tot%prime[i]==0)
                {
                    tot/=prime[i];
                    cnt++;
                }
                if(cnt) fact.push_back(P(prime[i],cnt));
            }
            if(tot!=1) fact.push_back(P(tot,1));
            dfs(0,(int)fact.size(),1,1);
            printf("Case #%d: %d\n",kase,ans);
        }
        else
        {
            BLOCK=(int)pow(n,2.0/3);
            genf(BLOCK,N);
            printf("Case #%d: %d\n",kase,get(n));
        }
    }
    return 0;
}
