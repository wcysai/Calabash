#include<bits/stdc++.h>
#define MAXN 505
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef pair<P,P> PP;
int n,a[MAXN][MAXN];
vector<P> path;
vector<vector<P> > inpath;
vector<PP> ans;
map<int,vector<P> > mp;
bool used[MAXN][MAXN];
void dfs(P p)
{
    if(used[p.F][p.S]) return;
    used[p.F][p.S]=true;
    path.push_back(p);
    int val=a[p.F][p.S];
    if(mp[val].size()==1) return;
    P nxt=(mp[val][0]==p?mp[val][1]:mp[val][0]);
    used[nxt.F][nxt.S]=true;
    path.push_back(nxt);
    dfs(P(nxt.S,nxt.F));
}
void go_swap(P x,P y)
{
    ans.push_back(PP(x,y));
}
void solve()
{
    inpath.clear();
    memset(used,false,sizeof(used));
    for(int i=0;i<n;i++)
    {
        int val=a[i][i];
        if(used[i][i]) continue;
        if(mp[val].size()==1) {used[i][i]=true; continue;}
        path.clear();
        dfs(P(i,i));
        if((int)path.size()&1)
        {
            for(int j=(int)path.size()-1;j>=2;j-=2) go_swap(path[j],path[j-2]);
            continue;
        }
        else inpath.push_back(path);
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        {
            if(i==j||used[i][j]) continue;
            int val=a[i][j];
            if(mp[val].size()!=1) continue;
            path.clear(); path.push_back(P(i,j)); used[i][j]=true;
            dfs(P(j,i));
            for(int k=0;k+2<(int)path.size();k+=2) go_swap(path[k],path[k+2]);
            assert(inpath.size());
            auto pth=inpath.back();
            for(int k=2;k<(int)pth.size();k+=2) go_swap(pth[0],pth[k]);
            int sz=(int)path.size();
            go_swap(path[sz-1],pth[0]); go_swap(path[sz-2],pth.back());
            inpath.pop_back();
        }
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        {
            if(i==j||used[i][j])continue;
            int val=a[i][j];
            if(mp[val].size()!=2) continue;
            path.clear();
            dfs(P(i,j));
            for(int k=1;k+2<(int)path.size();k+=2) go_swap(path[k],path[k+2]);
        }
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        {
            scanf("%d",&a[i][j]);
            mp[a[i][j]].push_back(P(i,j));
        }
    solve();
    printf("%d\n",(int)ans.size());
    for(auto p:ans) printf("%d %d %d %d\n",p.F.F+1,p.F.S+1,p.S.F+1,p.S.S+1);
    return 0;
}
