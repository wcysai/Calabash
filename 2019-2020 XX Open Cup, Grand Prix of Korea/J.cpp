#include<bits/stdc++.h>
#define MAXN 250005
#define MAXM 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN],b[MAXN],c[MAXN];
int st[MAXN],t,root;
vector<int> G[MAXN];
vector<int> enter[MAXM];
priority_queue<ll> pque[MAXN];
bool cmp(int x,int y)
{
    return b[x]>b[y];
}
void add_edge(int u,int v)
{
    G[u].push_back(v);
}
void merge(int v,int to)
{
    if(pque[v].size()<pque[to].size()) swap(pque[v],pque[to]);
    vector<ll> tmp;
    while(pque[to].size())
    {
        ll x=pque[v].top(); pque[v].pop();
        ll y=pque[to].top(); pque[to].pop();
        tmp.push_back(x+y);
    }
    for(auto x:tmp) pque[v].push(x);
}
void dfs(int v)
{
    if(!G[v].size())
    {
        pque[v].push(c[v]);
        return;
    }
    for(auto to:G[v])
    {
        dfs(to);
        merge(v,to);
    }
    if(v<=n) pque[v].push(c[v]);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d%d",&a[i],&b[i],&c[i]);
        enter[a[i]].push_back(i);
    }
    root=n+1;
    for(int i=1;i<=1000000;i++)
    {
        while(t>0&&b[st[t-1]]==i) t--;
        sort(enter[i].begin(),enter[i].end(),cmp);
        for(auto x:enter[i])
        {
            if(t==0) add_edge(root,x); else add_edge(st[t-1],x);
            st[t++]=x;
        }
    }
    dfs(root);
    int tot=0;
    ll cur=0;
    while(pque[root].size())
    {
        ll x=pque[root].top(); pque[root].pop();
        cur+=x; printf("%lld ",cur);
        tot++;
    }
    for(int i=tot+1;i<=n;i++) printf("%lld ",cur);
    puts("");
    return 0;
}
