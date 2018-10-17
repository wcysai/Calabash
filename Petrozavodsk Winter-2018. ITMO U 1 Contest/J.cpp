#include <bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll save[305][305];
ll n,h,a[MAXN],dp[MAXN];
int main()
{
    scanf("%lld%lld",&n,&h);
    for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
    a[n]=INF;
    dp[1]=1;
    for(ll i=1;i+h<=n;i+=h) if(a[i]!=h) dp[i+h]+=dp[i];
    for(ll i=1;i<=n;i++)
    {
        for(ll j=1;j<=300;j++)
        {
            if(a[i]==j) continue;
            (dp[i]+=save[j][i%j])%=MOD;
        }
        if(a[i]>300)
        {
            for(ll j=i+a[i];j<=n;j+=a[i])
            {
                if(a[j]!=a[i]) (dp[j]+=dp[i])%=MOD;
            }
        } else (save[a[i]][i%a[i]]+=dp[i])%=MOD;
    }
    printf("%lld\n",dp[n]);
    return 0;
}
