#include<bits/stdc++.h>
#define MAXN 5005
#define INF 1000000000
#define MOD 1000000009
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,fact[MAXN],invf[MAXN],a[MAXN],cnt[MAXN];
int dp[MAXN],pre[MAXN],suf[MAXN];
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
vector<int> v;
int main()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<=5000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[5000]=pow_mod(fact[5000],MOD-2);
    for(int i=4999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
    {
        scanf("%d",&a[i]);
        v.push_back(a[i]);
    }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    for(int i=1;i<=n;i++) a[i]=lower_bound(v.begin(),v.end(),a[i])-v.begin()+1;
    sort(a+1,a+n+1);
    int ways=1;
    dp[0]=1;
    for(int i=1;i<=n;i++)
    {
        ways=1LL*ways*fact[cnt[a[i]]]%MOD;
        cnt[a[i]]++;
        ways=1LL*ways*i%MOD;
        ways=1LL*ways*invf[cnt[a[i]]]%MOD;
        pre[i]=ways;
    }
    for(int i=1;i<=n;i++)
    {
        memset(cnt,0,sizeof(cnt));
        memset(suf,0,sizeof(suf));
        suf[i+1]=1;
        ways=1;
        for(int j=i;j>=1;j--)
        {
            ways=1LL*ways*fact[cnt[a[j]]]%MOD;
            cnt[a[j]]++;
            ways=1LL*ways*(i-j+1)%MOD;
            ways=1LL*ways*invf[cnt[a[j]]]%MOD;
            suf[j]=ways;
        }
        dp[i]=pre[i];
        for(int j=1;j<=i;j++)
        {
            //if(a[j]==a[j-1]) continue;
            dec(dp[i],1LL*dp[j-1]*suf[j+1]%MOD);
        }
    }
    printf("%d\n",dp[n]);
    return 0;
}
