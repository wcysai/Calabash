#include<bits/stdc++.h>
#define MAXN 300005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,tot,t,V;
map<string,int> mp;
map<vector<int>,int> mp2;
vector<int> G[MAXN];
int match[MAXN];
bool used[MAXN];
void add_edge(int u,int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
}
int get_id(string str)
{
    if(mp.find(str)==mp.end()) mp[str]=++tot;
    return mp[str];
}
int get_vertex_id(vector<int> &v)
{
    if(mp2.find(v)==mp2.end()) mp2[v]=++t;
    return mp2[v];
}
vector<int> v;
string str;
bool dfs(int v)
{
    used[v]=true;
    for(int i=0;i<G[v].size();i++)
    {
        int u=G[v][i],w=match[u];
        if(w<0||!used[w]&&dfs(w))
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
    memset(match,-1,sizeof(match));
    for(int v=1;v<=V;v++)
    {
        if(match[v]<0)
        {
            memset(used,0,sizeof(used));
            if(dfs(v))
            {
                res++;
            }
        }
    }
    return res;
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        int x;
        scanf("%d",&x);
        v.clear();
        for(int j=0;j<x;j++)
        {
            cin>>str;
            v.push_back(get_id(str));
        }
        sort(v.begin(),v.end());
        for(int mask=1;mask<(1<<x);mask++)
        {
            vector<int> tmp;
            for(int j=0;j<x;j++) if(mask&(1<<j)) tmp.push_back(v[j]);
            get_vertex_id(tmp);
        }
    }
    int SZ=(int)mp2.size();
    for(auto p:mp2)
    {
        auto x=p.F;
        int sz=(int)x.size();
        int id=get_vertex_id(x);
        for(int j=0;j<sz;j++)
        {
            vector<int> tmp=x;
            tmp.erase(tmp.begin()+j);
            if(!tmp.size()) continue;
            add_edge(id,SZ+get_vertex_id(tmp));
        }
    }
    V=2*SZ;
    printf("%d\n",SZ-bipartite_matching());
    return 0;
}
