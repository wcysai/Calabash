#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll a[MAXN],bas[62];
ll T,n;
int main()
{
    scanf("%lld",&T);
    while(T--)
    {
        ll s=0;
        memset(bas,0,sizeof(bas));
        scanf("%lld",&n);
        for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
        for(ll i=1;i<=n;i++) s^=a[i];
        for(ll i=1;i<=n;i++)
        {
            ll x=a[i]&s;
            for(ll j=60;j>=0;j--)
            {
                if(x&(1LL<<j))
                {
                    if(!bas[j])
                    {
                        bas[j]=x;
                        break;
                    }
                    x^=bas[j];
                }
            }
        }
        for(ll i=60;i>=0;i--)
            for(ll j=i-1;j>=0;j--)
                if(bas[i]&(1LL<<j)) bas[i]^=bas[j];
        ll now=s;
        for(ll i=60;i>=0;i--) if(bas[i]) {now=bas[i]; break;}
        printf("%lld\n",now-(s^now));
    }
    return 0;
}

