#include<bits/stdc++.h>
#define MAXN 400005
#define INF 1000000000000000005LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,m;
ll k;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%d",&k,&m);
        ll ans=INF;
        for(ll delta=1;delta<=1000;delta++)
        {
            ll n=k^delta,cur=n;
            int cnt=0;
            while(cnt<m)
            {
                cur++;
                if(cur>n+delta) break;
                if(__gcd(cur,n)==1) cnt++;
            }
            if(cur==n+delta) ans=min(ans,n);
        }
        if(ans==INF) puts("-1"); else printf("%lld\n",ans);
    }
    return 0;
}
