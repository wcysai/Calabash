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
struct node
{
    int p;
    ll u,v;
};
struct convex_hull
{
    deque<node> st;
    int cur;
    void clear() {st.clear(); cur=0;}
    void erase(int x)
    {
        if(st.size()==0||st.front().p!=x) return;
        if(cur>0) cur--;
        st.pop_front();
    }
    void add(int pos,ll u,ll v)
    {
        node p=(node){pos,u,v};
        int t=(int)st.size();
        /*while(t>1&&((long double)st[t-1].u-st[t-2].u)*((long double)p.v-st[t-1].v)>=((long double)st[t-1].u-p.u)*((long double)st[t-2].v-st[t-1].v)) 
        {
            st.pop_back();
            if(cur==t-1) cur--;
            t--;
        }*/
        st.push_back(p);
    }
    ll query(int x)
    {
        int t=(int)st.size();
        if(t==0) return INF;
        while(cur+1<t&&st[cur].u*x+st[cur].v>=st[cur+1].u*x+st[cur+1].v) cur++;
        return st[cur].u*x+st[cur].v;
    }
}ch;
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
        ch.clear();
        s=min(20000,s+c[i+1]);
        int r=s,l=max(0,s-c[i+1]);
        for(int j=r;j>=l;j--) if(dp[i][j]!=INF) ch.add(j,2LL*j*d[i+1],-1LL*j*j*d[i+1]-1LL*d[i+1]*j-2LL*a[i+1]*j+dp[i][j]);
        for(int j=r;j>=0;j--)
        {
            dp[i+1][j]=ch.query(j)+2LL*a[i+1]*j+1LL*d[i+1]*j-1LL*j*j*d[i+1];
            if(l!=0)
            {
                l--;
                if(dp[i][l]!=INF) ch.add(l,2LL*l*d[i+1],-1LL*l*l*d[i+1]-1LL*d[i+1]*l-2LL*a[i+1]*l+dp[i][l]);
            }
            ch.erase(j);
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

