#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,x,y;
deque<int> a,b;
int deg[MAXN];
priority_queue<int,vector<int>,greater<int> >pque;
vector<P> ans;
void add_edge(int u,int v)
{
    ans.push_back(P(u,v));
}
int main()
{
    scanf("%d%d%d%d",&n,&m,&x,&y);
    for(int i=1;i<=n+m;i++) deg[i]=1;
    for(int i=0;i<x;i++)
    {
        int p;
        scanf("%d",&p);
        deg[p]++;
        a.push_back(p);
    }
    for(int i=0;i<y;i++)
    {
        int p;
        scanf("%d",&p);
        deg[p]++;
        b.push_back(p);
    }
    if(x>=m||y>=n)
    {
        puts("No");
        return 0;
    }
    puts("Yes");
    while(a.size()<m-1)
    {
        a.push_back(n);
        deg[n]++;
    }
    while(b.size()<n-1)
    {
        b.push_back(n+m);
        deg[n+m]++;
    }
    for(int i=1;i<=n+m;i++) if(deg[i]==1) pque.push(i);
    for(int i=1;i<=n+m-2;i++)
    {
        int leaf=pque.top(); pque.pop();
        if(leaf<=n)
        {
            int v=b.front();
            add_edge(leaf,v);
            deg[v]--;
            if(deg[v]==1) pque.push(v);
            b.pop_front();
        }
        else
        {
            int v=a.front();
            add_edge(leaf,v);
            deg[v]--;
            if(deg[v]==1) pque.push(v);
            a.pop_front();
        }
    }
    int v=pque.top(); pque.pop();
    int u=pque.top(); pque.pop();
    add_edge(u,v);
    for(auto p:ans) printf("%d %d\n",p.F,p.S);
    return 0;
}
