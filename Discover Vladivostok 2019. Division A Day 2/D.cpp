#include<bits/stdc++.h>
#define MAXN 55
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
string s[MAXN],t[MAXN];
int cnt[MAXN];
vector<int> G[2*MAXN];
int match[2*MAXN];
bool used[2*MAXN];
void add_edge(int u,int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}
bool dfs(int v)
{
    used[v]=true;
    for(int i=0;i<(int)G[v].size();i++)
    {
        int u=G[v][i],w=match[u];
        if(w<0||(!used[w]&&dfs(w)))
        {
            match[v]=u;
            match[u]=v;
            return true;
        }
    }
    return false;
}
int bipartite_matching()
{
    int res=0;
    for(int i=1;i<=2*n;i++) match[i]=-1;
    for(int i=1;i<=2*n;i++)
    {
        if(match[i]<0)
        {
            for(int j=1;j<=2*n;j++) used[j]=0;
            if(dfs(i)) res++;
        }
    }
    return res;
}
bool can(string s,string t)
{
    for(int i=0;i<m;i++) 
    {
        if(s[i]=='?') continue;
        if(s[i]!=t[i]) return false;
    }
    return true;
}
int main()
{
    freopen("lots.in","r",stdin);
    freopen("lots.out","w",stdout);
    while(scanf("%d%d",&n,&m)==2)
    {
        if(!n&&!m) break;
        for(int i=0;i<n;i++) cin>>s[i];
        for(int i=0;i<n;i++) cin>>t[i];
        bool f=true;
        for(int i=0;i<n;i++)
        {
            cnt[i]=0;
            for(int j=0;j<m;j++) if(t[i][j]=='x') cnt[i]++;
            if(i>0&&cnt[i]>cnt[i-1]) f=false;
        }
        for(int i=1;i<=2*n;i++) G[i].clear();
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(can(s[i],t[j])) add_edge(i+1,n+j+1);
        if(bipartite_matching()!=n) f=false;
        if(!f) puts("NO");
        else
        {
            puts("YES");
            for(int i=1;i<=n;i++) cout<<t[match[i]-n-1]<<endl;
        }
    }
}
