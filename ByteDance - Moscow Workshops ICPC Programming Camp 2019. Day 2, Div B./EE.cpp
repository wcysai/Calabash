#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 505
#define MAXK 505
#define MAXM 20005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<ll,ll> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
int n,k,a[MAXN],d[MAXN],c[MAXN];
ll dp[MAXN][MAXM];
struct convex_hull
{
    vector<P> st;
    int cur;
    void clear() {st.clear(); cur=0;}
    void add(ll u,ll v)
    {
        P p=P(u,v);
        int t=(int)st.size();
        while(t>1&&((long double)st[t-1].F-st[t-2].F)*((long double)p.S-st[t-1].S)>=((long double)st[t-1].F-p.F)*((long double)st[t-2].S-st[t-1].S)) st.pop_back(),t--;
        st.push_back(p);
    }
    ll query(int x)
    {
        int t=(int)st.size();
        if(t==0) return INF;
        while(cur+1<t&&st[cur].F*x+st[cur].S>=st[cur+1].F*x+st[cur+1].S) cur++;
        return st[cur].F*x+st[cur].S;
    }
};
struct segtree
{
    convex_hull seg[4*MAXM];
    void clear(int k,int l,int r)
    {
        seg[k].clear();
        if(l==r) return;
        ll mid=(l+r)/2;
        clear(k*2,l,mid); clear(k*2+1,mid+1,r);
    }
    void add(int k,int l,int r,int pos,ll u,ll v)
    {
        seg[k].add(u,v);
        if(l==r) return;
        ll mid=(l+r)/2;
        if(pos<=mid) add(k*2,l,mid,pos,u,v); else add(k*2+1,mid+1,r,pos,u,v);
    }
    ll query(int k,int l,int r,int x,int y,int q)
    {
        if(l>y||x>r) return INF;
        if(l>=x&&r<=y) return seg[k].query(q);
        ll mid=(l+r)/2;
        return min(query(k*2,l,mid,x,y,q),query(k*2+1,mid+1,r,x,y,q));
    }
}SegTree;
struct node
{
    int p;
    ll u,v;
};
bool cmp(node x,node y)
{
    return x.u>y.u;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d%d%d",&a[i],&d[i],&c[i]);
    for(int i=1;i<=n;i++) fill(dp[i],dp[i]+20001,INF);
    dp[1][0]=0;
    for(int i=1;i<=min(c[1],20000);i++) dp[1][i]=dp[1][i-1]+2LL*(a[1]-(i-1)*d[1]);
    int s=c[1];
    for(int i=1;i<=n-1;i++)
    {
        SegTree.clear(1,0,20000);
        vector<node> v; v.clear();
        for(int j=0;j<=min(s,20000);j++) 
        {
            if(dp[i][j]==INF) continue;
            v.push_back((node){j,2LL*j*d[i+1],-1LL*j*j*d[i+1]-1LL*d[i+1]*j-2LL*a[i+1]*j+dp[i][j]});
        }
        sort(v.begin(),v.end(),cmp);
        for(auto en:v) SegTree.add(1,0,20000,en.p,en.u,en.v);
        s=min(20000,s+c[i+1]);
        for(int j=0;j<=min(s,20000);j++)
        {
            int l=max(0,j-c[i+1]),r=j;
            dp[i+1][j]=SegTree.query(1,0,20000,l,r,j)+2LL*a[i+1]*j+1LL*d[i+1]*j-1LL*j*j*d[i+1];
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=10;j++) printf("%lld ",dp[i][j]);
        puts("");
    }
    for(int i=0;i<k;i++)
    {
        int x; scanf("%d",&x);
        printf("%lld\n",dp[n][x]/2);
    }
    return 0;
}
