#include<bits/stdc++.h>
#define MAXN 2005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,fact[MAXN],invf[MAXN],inv[MAXN];
int catalan[MAXN];
int dp[505][505];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int tot,type,t;
int cnt[MAXN];
int pos[MAXN];
int lson[MAXN],rson[MAXN],fa[MAXN],label[MAXN];
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
    for(int i=1;i<=2000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[2000]=pow_mod(fact[2000],MOD-2);
    for(int i=1999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    for(int i=1;i<=2000;i++) inv[i]=1LL*invf[i]*fact[i-1]%MOD;
    for(int i=0;i<=1000;i++) catalan[i]=1LL*comb(2*i,i)*inv[i+1]%MOD;
    for(int i=0;i<=500;i++) dp[i][0]=1;
    for(int i=1;i<=500;i++) dp[1][i]=catalan[i];
    for(int i=2;i<=500;i++)
    {
        for(int j=1;j<=500;j++)
        {
            dp[i][j]=0;
            for(int k=0;k<=j;k++) add(dp[i][j],1LL*dp[i-1][j-k]*catalan[k]%MOD);
        }
    }
    scanf("%d",&n);
    int v=1;
    tot=0; t=1;
    for(int i=1;i<=n;i++)
    {
        int type;
        scanf("%d",&type);
        if(type==0) v=fa[v];
        else if(type==1)
        {
            if(!lson[v])
            {
                int u=label[v];
                lson[v]=++t;
                fa[t]=v; label[t]=u; cnt[u]--; pos[u]++;
                v=lson[v];
            }
            else v=lson[v];
        }
        else if(type==2)
        {
            if(!rson[v])
            {
                int u=label[v];
                rson[v]=++t;
                fa[t]=v; label[t]=u; cnt[u]--; pos[u]++;
                v=rson[v];
            }
            else v=rson[v];
        }
        else if(type==3)
        {
            int u=label[v]; pos[u]--;
            int x;
            scanf("%d",&x);
            tot++;
            lson[v]=++t;
            fa[t]=v; label[t]=tot; cnt[tot]=x-1; pos[tot]=2;
        }
        else if(type==4)
        {
            int u=label[v]; pos[u]--;
            int x;
            scanf("%d",&x);
            tot++;
            rson[v]=++t;
            fa[t]=v; label[t]=tot; cnt[tot]=x-1; pos[tot]=2;
        }
    }
    int ans=1;
    for(int i=1;i<=tot;i++) ans=1LL*ans*dp[pos[i]][cnt[i]]%MOD;
    printf("%d\n",ans);
    return 0;
}
