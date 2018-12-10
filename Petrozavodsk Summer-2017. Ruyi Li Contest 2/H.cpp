#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
ll n,m,b[MAXN],c[MAXN];
ll now;
vector<int> v;
int main()
{
    scanf("%lld%lld",&n,&m);
    for(ll i=0;i<=m;i++) scanf("%lld",&b[i]);
    now=1;
    for(ll i=1;i<=n;i++)
    {
        while(!b[now]&&now<=m) now++;
        assert(now<=m);
        v.push_back(now);
        memset(c,0,sizeof(c));
        for(ll j=0;j+now<=m;j++)
        {
            if(b[j])
            {
                assert(b[j+now]>=b[j]);
                c[j]=b[j];b[j+now]-=b[j];
            }
        }
        for(ll j=0;j<=m;j++) b[j]=c[j];
    }
    for(ll i=0;i<n;i++) printf("%lld%c",v[i],i==n-1?'\n':' ');
    return 0;
}
