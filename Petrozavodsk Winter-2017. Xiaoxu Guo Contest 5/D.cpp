#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define MAXW 5500000
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll n,a[MAXN],s;
bool dp[MAXW];
ll gcd(ll a,ll b) {return b==0?a:gcd(b,a%b);}
ll lcm(ll a,ll b) {return a*b/gcd(a,b);}
bool deq[MAXW];
int main()
{
    while(scanf("%lld",&n)==1)
    {
        ll m=1;
        for(ll i=1;i<=n;i++) m=lcm(m,i);
        s=0;
        for(ll i=1;i<=n;i++)
        {
            scanf("%lld",&a[i]);
            s+=i*a[i];
        }
        fill(dp,dp+n*m+1,false);
        dp[0]=true;
        for(ll i=1;i<=n;i++)
        {
            for(ll j=0;j<i;j++)
            {
                ll s=0,t=0,cnt=0;
                for(ll k=0;k*i+j<n*m;k++)
                {
                    bool val=dp[k*i+j];
                    deq[t++]=val;
                    if(val) cnt++;
                    if(cnt) dp[k*i+j]=true; else dp[k*i+j]=false;
                    if(t-s>a[i])
                    {
                        if(deq[s]) cnt--;
                        s++;
                    }
                }
            }
        }
        ll ans=0;
        for(ll i=0;i<n*m;i++)
        {
            if(dp[i])
            {
                ans++;
                if(s-i>=n*m) ans++;
            }
        }
        for(ll i=1;i<=m;i++)
        {
            if(dp[n*m-i])
            {
                ll l=n*m-i+m,r=s-n*m;
                if(r>=l) ans+=(r-l)/m+1;
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}

