#include<bits/stdc++.h>
#define MAXN 250005
#define INF 1000000000000LL
#define INF2 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k;
ll dp[MAXN][2];
int cnt[MAXN][2];
struct edge
{
    int to,cost;
};
vector<edge> G[MAXN];
int dfs(int v,int p,ll d)
{
    dp[v][0]=dp[v][1]=0;
    cnt[v][0]=0;cnt[v][1]=1;
    //0: don't choose
    //1: must choose
    ll maxd=-INF2;
    int ccnt=0;
    for(auto e:G[v])
    {
        if(e.to==p) continue;
        dfs(e.to,v,d);
        dp[v][1]+=max(dp[e.to][0],dp[e.to][1]);
        dp[v][0]+=max(dp[e.to][0],dp[e.to][1]);
        int cur;
        if(dp[e.to][0]>dp[e.to][1]) cur=cnt[e.to][0];
        else if(dp[e.to][1]>dp[e.to][0]) cur=cnt[e.to][1];
        else cur=min(cnt[e.to][0],cnt[e.to][1]);
        cnt[v][0]+=cur;cnt[v][1]+=cur;
        ll dif=-d+e.cost-max(dp[e.to][0],dp[e.to][1])+dp[e.to][0];
        if(dif>maxd) {maxd=dif; ccnt=cnt[e.to][0]-cur;}
        else if(dif==maxd) ccnt=min(ccnt,cnt[e.to][0]-cur);
    }
    dp[v][1]+=maxd;
    cnt[v][1]+=ccnt;
}
int check(ll d)
{
    dfs(1,0,d);
    if(dp[1][0]>dp[1][1]) return cnt[1][0];
    else if(dp[1][1]>dp[1][0]) return cnt[1][1];
    else return min(cnt[1][0],cnt[1][1]);
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=0;i<n-1;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        G[u].push_back((edge){v,w});
        G[v].push_back((edge){u,w});
    }
    ll l=-INF,r=INF;
    while(r-l>1)
    {
        ll mid=(l+r)/2;
        int x=check(mid);
        if(x>k) l=mid; else r=mid;  
    }
//    printf("%lld\n",r);
    check(r);
    ll ans = max(dp[1][0], dp[1][1]) + k * r;
    for (int i = 1; i <= n; i++) for (auto& e : G[i]) e.cost = 1;
    if (check(0) < k) puts("Impossible");
    else cout << ans << endl;
    return 0;
}
