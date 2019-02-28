#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 100005
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
int n,m;
P a[MAXN];
struct seg
{
    int l,r,id;
};
seg b[MAXN];
bool cmp(seg x,seg y)
{
    if(x.r!=y.r) return x.r>y.r;
    return x.l<y.l;
}
set<P> s;
vector<int> use[MAXN];
bool dp[MAXN][3];
int last[MAXN][3];
int ans[MAXN];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) {scanf("%d",&a[i].F); a[i].S=i;}
    for(int i=1;i<=m;i++) {scanf("%d%d",&b[i].l,&b[i].r); b[i].id=i;}
    sort(b+1,b+m+1,cmp);
    sort(a+1,a+n+1,greater<P>());
    int now=1;
    for(int i=1;i<=n;i++)
    {
        while(now<=m&&b[now].r>=a[i].F) {s.insert(P(b[now].l,b[now].id)); now++;}
        int cnt=0;
        auto it=s.lower_bound(P(a[i].F+1,0));
        while(cnt<3&&it!=s.begin())
        {
            it--;
            use[a[i].S].push_back(it->S);
            cnt++;
        }
    }
   /* for(int i=1;i<=n;i++)
    {
        for(auto x:use[i]) printf("%d ",x);
        puts("");
    }*/
    memset(dp,false,sizeof(dp));
    for(int i=0;i<(int)use[1].size();i++) {dp[1][i]=true; last[1][i]=-1;}
    for(int i=2;i<=n;i++)
        for(int j=0;j<(int)use[i].size();j++)
            for(int k=0;k<(int)use[i-1].size();k++)
                if(dp[i-1][k]&&use[i-1][k]!=use[i][j]) 
                {
                    dp[i][j]=true;
                    last[i][j]=k;
                }
    bool f=false;
    int id=-1;
    for(int i=0;i<(int)use[n].size();i++) if(dp[n][i]) {f=true; id=i;}
    if(!f) {puts("No"); return 0;}
    puts("Yes");
    for(int i=n;i>=1;i--)
    {
        ans[i]=use[i][id];
        id=last[i][id];
    }
    for(int i=1;i<=n;i++) printf("%d%c",ans[i],i==n?'\n':' ');
    return 0;
}

