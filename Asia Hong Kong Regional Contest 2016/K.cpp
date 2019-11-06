#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 300005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,p;
vector<int> G[MAXM];
vector<int> v[MAXM];
vector<int> has[MAXM];
int indeg[MAXM],dp[MAXM];
vector<int> chara[MAXM];
vector<int> ans[MAXM];
set<P> s;
bool cmp(int x,int y)
{
    if(v[x].size()!=v[y].size()) return v[x].size()>v[y].size();
    return x<y;
}
vector<int> roots;
void dfs(int u)
{
    dp[u]=(int)chara[u].size();
    int sum=0;
    for(auto to:G[u])
    {
        sum+=(int)v[to].size();
    }
    if(sum!=(int)v[u].size()) return;
    int ans=INF;
    for(auto to:G[u])
    {
        dfs(to);
        ans=min(ans,dp[to]);
    }
    dp[u]+=ans;
}
void solve(int u,int need,int st)
{
    int taken=min(need,(int)chara[u].size());
    for(int j=0;j<taken;j++) ans[st+j].push_back(chara[u][j]);
    st+=taken;
    need-=taken;
    if(!need) return;
    for(auto to:G[u]) solve(to,need,st);
}
int main()
{
    scanf("%d%d%d",&n,&m,&p);
    for(int i=1;i<=m;i++)
    {
        int k;
        scanf("%d",&k);
        for(int j=0;j<k;j++)
        {
            int x;
            scanf("%d",&x);
            v[i].push_back(x);
            has[x].push_back(i);
        }
        sort(v[i].begin(),v[i].end());
    }
    for(int i=1;i<=n;i++)
    {
        if(!has[i].size()) {puts("0"); return 0;}
        sort(has[i].begin(),has[i].end(),cmp);
        for(int j=1;j<(int)has[i].size();j++) 
        {
            int x=has[i][j-1],y=has[i][j];
            if(s.count(P(x,y))) continue;
            s.insert(P(x,y));
            G[x].push_back(y);
            indeg[y]++;
        }
    }
    for(int i=1;i<=m;i++)
    {
        if(!indeg[i]) roots.push_back(i);
    }
    ++m;
    for(auto v:roots) G[m].push_back(v);
    for(int i=1;i<=n;i++) v[m].push_back(i);
    for(int i=1;i<=p;i++)
    {
        int x;
        scanf("%d",&x);
        chara[x].push_back(i);
    }
    dfs(m);
    printf("%d\n",dp[m]);
    solve(m,dp[m],1);
    for(int i=1;i<=dp[m];i++)
    {
        printf("%d",(int)ans[i].size());
        for(auto x:ans[i]) printf(" %d",x);
        puts("");
    }
    return 0;
}
