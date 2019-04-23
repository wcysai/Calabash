#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 255
#define MAXM 25005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef bitset<250> bs;
int n,m;
string str;
bs g[MAXN],rg[MAXN];
bs used;
int ans,cnt;
vector<int> vs;
void dfs(int v)
{
    if(used[v]) return;
    used.set(v);
    bs vis=(~used)&g[v];
    while(vis.any())
    {
        int i=vis._Find_first();
        dfs(i);
        vis=(~used)&g[v];
    }
    vs.push_back(v);
}
void rdfs(int v)
{
    if(!used[v]) cnt++; else return;
    used.set(v);
    bs vis=(~used)&rg[v];
    while(vis.any())
    {
        int i=vis._Find_first();
        rdfs(i);
        vis=(~used)&rg[v];
    }
}
int korasaju()
{
    ans=0; used.reset();
    vs.clear();
    for(int i=0;i<n;i++) if(!used[i]) dfs(i);
    cnt=0;
    used.reset();
    for(int i=(int)vs.size()-1;i>=0;i--)
        if(!used[vs[i]])
        {
            cnt=0;
            rdfs(vs[i]);
            ans+=cnt*(cnt-1)/2;
        }
    return ans;
}
void modify(int u,int v)
{
    g[u].flip(v); rg[v].flip(u);
}
int main()
{
    scanf("%d%d ",&n,&m);
    for(int i=0;i<n;i++)
    {
        cin>>str;
        for(int j=0;j<n;j++) 
            if(str[j]=='1')
            {
                g[i].set(j);
                rg[j].set(i);
            }
    }
    for(int i=0;i<m;i++)
    {
        int x;scanf("%d",&x);
        for(int j=0;j<x;j++)
        {
            int u,v; scanf("%d%d",&u,&v);
            u--;v--;
            modify(u,v);
        } 
        printf("%d\n",korasaju());
    }
    return 0;
}
