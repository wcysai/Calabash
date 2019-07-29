#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 100005
#define MAXK 205
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
struct line
{
    ll k,b;
    int id;
};
int n,k,tot,t,now;
line st[MAXN];
ll get(line u,line v) {if(u.k==v.k) return -INF; else return (v.b-u.b)/(u.k-v.k);}
int a[MAXN],sum[MAXN];
ll dp[MAXK][MAXN];
int last[MAXK][MAXN];
void add(ll u,ll v,int id)
{
    line p=(line){u,v,id};
    while(t-now>1&&get(st[t-1],p)<=get(st[t-1],st[t-2])) t--;
    st[t++]=p;
}
bool cmp(P x,P y)
{
    if(x.S!=y.S) return x.S<y.S;
    return x.F<y.F;
}
pair<int,ll> query(ll x)
{
    while(now+1<t&&st[now].k*x+st[now].b<=st[now+1].k*x+st[now+1].b) now++; 
    return make_pair(st[now].id,st[now].k*x+st[now].b);
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]); 
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
    for(int i=1;i<=k;i++)
    {
        now=0;t=0;
        for(int j=i+1;j<=n;j++)
        {
            add(sum[j-1],dp[i-1][j-1]-1LL*sum[j-1]*sum[j-1],j-1);
            pair<int,ll> res=query(sum[j]);
            dp[i][j]=res.S;last[i][j]=res.F;
        }
    }
    printf("%lld\n",dp[k][n]);
    int cur=n;
    while(k>0)
    {
        cur=last[k][cur];
        printf("%d ",cur);
        k--;
    }
    return 0;
}

