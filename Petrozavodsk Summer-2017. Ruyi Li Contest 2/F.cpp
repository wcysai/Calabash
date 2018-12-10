#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll n,m;
int main()
{
    scanf("%lld%lld",&n,&m);
    ll ans;
    if(m<=n-1)
    {
        ans=(n-1-m)*(n-2-m)*n+(n-1-m)*(m+1)*n*2+m*2+m*(m-1)*2;
        printf("%lld\n",ans);
    }
    else if(m>=n*(n-1)/2)
    {
        printf("%lld\n",n*(n-1));
        return 0;
    }
    else
    {
        ans=(n-1)*(n-2)*2+(n-1)*2;
        ans-=(m-n+1)*2;
        printf("%lld\n",ans);
    }
    return 0;
}
