#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
vector<int> G[MAXN];
set<int> deg4,nodeg4;
set<P> dd;
int color[MAXN],deg[MAXN],colored[MAXN];
bool ex[MAXN][5];
int get_color(int v)
{
    if(!ex[v][1]) return 1;
    if(!ex[v][2]) return 2;
    if(!ex[v][3]) return 3;
    assert(!ex[v][4]);
    return 4;
}
void update4(int v,int c)
{
    color[v]=c;dd.erase(P(colored[v],v));deg4.erase(v);
    for(auto u:G[v])
    {
        if(!ex[u][c])
        {
            ex[u][c]=true;
            if(deg4.count(u))
            {
                dd.erase(P(colored[u],u));
                colored[u]++;
                dd.insert(P(colored[u],u));
            }
        }
    }
}
void update3(int v,int c)
{
    color[v]=c;nodeg4.erase(v);
    for(auto u:G[v])
    {
        if(!ex[u][c])
        {
            ex[u][c]=true;
            if(deg4.count(u))
            {
                dd.erase(P(colored[u],u));
                colored[u]++;
                dd.insert(P(colored[u],u));
            }
        }
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);G[v].push_back(u);
        deg[v]++;deg[u]++;
    }
    memset(ex,false,sizeof(ex));
    for(int i=1;i<=n;i++)
    {
        if(deg[i]>=4)
        {
            deg4.insert(i);
            dd.insert(P(0,i));
        }
        else nodeg4.insert(i);
    }
    int tot=n;
    while(tot>0)
    {
        tot--;
        if(deg4.size()>0)
        {
            auto it=dd.end();it--;
            int v=it->S,c=get_color(v);
            printf("%d %d\n",v,c);fflush(stdout);
            update4(v,c);
        }
        else
        {
            auto it=nodeg4.begin();
            int v=*it,c=get_color(v);
            printf("%d %d\n",v,c);fflush(stdout);
            update3(v,c);
        }
        int v,c;scanf("%d%d",&v,&c);
        if(v==-1) break;
        if(deg4.count(v)) update4(v,c); else update3(v,c);
    }
    return 0;
}
