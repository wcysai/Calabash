#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
ll n;
char str[2];
ll a[MAXN];
ll dp[2][256];
ll find(char c)
{
    if(c>='0'&&c<='9') return c-'0';
    return c-'A'+10;
}
void upd(ll &a,ll b) {a=max(a,b);}
int main()
{
    scanf("%lld",&n);
    for(ll i=1;i<=n;i++)
    {
        scanf("%s",str);
        a[i]=find(str[0])*16+find(str[1]);
    }
    memset(dp,-1,sizeof(dp));
    dp[0][0]=0;
    for(ll i=0;i<n;i++)
    {
        ll now=i&1,nxt=1-now;
        memset(dp[nxt],-1,sizeof(dp[nxt]));
        for(ll j=0;j<256;j++)
        {
            if(dp[now][j]==-1) continue;
            if(j!=256) upd(dp[nxt][j+1],dp[now][j]);
            upd(dp[nxt][j],dp[now][j]+((i-j)^a[i+1]));
        }
    }
    ll ans=0;
    for(ll i=0;i<256;i++) upd(ans,dp[n&1][i]);
    printf("%lld\n",ans);
    return 0;
}

