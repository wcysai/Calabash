#include<bits/stdc++.h>
#define MAXN 55
#define MAXK 105
#define MAXM 5005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,c[MAXN],fact[MAXM],invf[MAXM],inv[MAXM];
int res[MAXK][MAXK];
int dp[MAXN][MAXM];
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
    for(int i=1;i<=5000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[5000]=pow_mod(fact[5000],MOD-2);
    for(int i=4999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    for(int i=1;i<=4999;i++) inv[i]=1LL*invf[i]*fact[i-1]%MOD;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&c[i]);
    res[0][0]=1;
    for(int i=1;i<=100;i++)
        for(int j=1;j<=100;j++)
            for(int k=1;k<=j;k++)
                add(res[i][j],1LL*res[i-1][j-k]*k%MOD);
    dp[0][0]=1;
    int sum=0;
    for(int i=0;i<n-1;i++)
    {
        int cnt=c[i+1];
        static int tmp[MAXM];
        for(int j=0;j<=sum;j++) tmp[j]=0;
        for(int glued_parts=1;glued_parts<=cnt;glued_parts++)
            for(int chosen_parts=1;chosen_parts<=glued_parts;chosen_parts++)
                if((glued_parts-chosen_parts)&1) dec(tmp[chosen_parts],1LL*comb(glued_parts-1,chosen_parts-1)*res[glued_parts][cnt]%MOD);
                else add(tmp[chosen_parts],1LL*comb(glued_parts-1,chosen_parts-1)*res[glued_parts][cnt]%MOD);
        for(int chosen_parts=1;chosen_parts<=cnt;chosen_parts++)
            for(int fixed_parts=0;fixed_parts<=sum;fixed_parts++)
                add(dp[i+1][fixed_parts+chosen_parts],1LL*dp[i][fixed_parts]*comb(fixed_parts+chosen_parts,chosen_parts)%MOD*tmp[chosen_parts]%MOD);
        sum+=cnt;
    }
    int cnt=c[n];
    static int tmp[MAXM];
    for(int j=0;j<=sum;j++) tmp[j]=0;
    for(int glued_parts=1;glued_parts<=cnt;glued_parts++)
        for(int chosen_parts=1;chosen_parts<=glued_parts;chosen_parts++)
            if((glued_parts-chosen_parts)&1) dec(tmp[chosen_parts],1LL*comb(glued_parts-1,chosen_parts-1)*res[glued_parts][cnt]%MOD*inv[glued_parts]%MOD);
                else add(tmp[chosen_parts],1LL*comb(glued_parts-1,chosen_parts-1)*res[glued_parts][cnt]%MOD*inv[glued_parts]%MOD);
    for(int chosen_parts=1;chosen_parts<=cnt;chosen_parts++)
        for(int fixed_parts=0;fixed_parts<=sum;fixed_parts++)
            add(dp[n][fixed_parts+chosen_parts],1LL*dp[n-1][fixed_parts]*comb(fixed_parts+chosen_parts-2,chosen_parts-1)%MOD*tmp[chosen_parts]%MOD);
    sum+=cnt;
    int ans=0;
    for(int i=0;i<=sum;i++) add(ans,dp[n][i]);
    ans=1LL*ans*sum%MOD;
    printf("%d\n",ans);
    return 0;
}
