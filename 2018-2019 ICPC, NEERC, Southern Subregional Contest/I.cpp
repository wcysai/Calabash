#include<bits/stdc++.h>
#define MAXV 3005
#define MAXE 50000
#define INF 1000000
using namespace std;
typedef pair<int,int> P;
struct edge{int to,cap,rev;};
int t,n,m,k,V;
vector<edge> G[MAXV];
vector<int> H[MAXV];
int u[MAXV],v[MAXV];
int level[MAXV];
int iter[MAXV];
int ans[MAXV];
void add_edge(int from,int to,int cap)
{
    G[from].push_back((edge){to,cap,(int)G[to].size()});
    G[to].push_back((edge){from,0,(int)G[from].size()-1});
}
void bfs(int s)
{
    memset(level,-1,sizeof(level));
    queue<int> que;
    level[s]=0;
    que.push(s);
    while(!que.empty())
    {
        int v=que.front(); que.pop();
        for(int i=0;i<(int)G[v].size();i++)
        {
            edge &e=G[v][i];
            if(e.cap>0&&level[e.to]<0)
            {
                level[e.to]=level[v]+1;
                que.push(e.to);
            }
        }
    }
}

int dfs(int v,int t,int f)
{
    if(v==t) return f;
    for(int &i=iter[v];i<(int)G[v].size();i++)
    {
        edge &e=G[v][i];
        if(level[v]<level[e.to]&&e.cap>0)
        {
            int d=dfs(e.to,t,min(f,e.cap));
            if(d>0)
            {
                e.cap-=d;
                G[e.to][e.rev].cap+=d;
                return d;
            }
        }
    }
    return 0;
}
int max_flow(int s,int t)
{
    int flow=0;
    for(;;)
    {
        bfs(s);
        if(level[t]<0) return flow;
        memset(iter,0,sizeof(iter));
        int f;
        while((f=dfs(s,t,INF))>0)
          flow+=f;
    }
}
void print()
{
    for(int i=1;i<=m;i++) printf("%d%c",ans[i],i==m?'\n':' ');
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d",&n,&m,&k);
        for(int i=1;i<=n;i++) H[i].clear();
        for(int i=1;i<=m;i++) ans[i]=0;
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d",&u[i],&v[i]);
            H[u[i]].push_back(i); H[v[i]].push_back(i);
        }
        V=n+m+2;
        int s=n+m+1,t=n+m+2;
        for(int i=1;i<=V;i++) G[i].clear();
        bool f=true;
        for(int i=1;i<=n;i++) if((int)H[i].size()>2*k) {f=false; break;}
        if(!f)
        {
            print();
            continue;
        }
        for(int i=1;i<=m;i++) add_edge(n+i,t,1);
        int cnt=0;
        for(int i=1;i<=n;i++)
        {
            int d=(int)H[i].size();
            if(d>k)
            {
                int need=d-k; cnt+=need;
                add_edge(s,i,2*need);
                for(auto e:H[i]) add_edge(i,n+e,1);
            }
        }
        if(max_flow(s,t)<2*cnt)
        {
            print();
            continue;
        }
        int tot=0;
        for(int i=1;i<=n;i++)
        {
            vector<int> tmp;
            for(auto e:G[i])
            {
                if(e.to>=n+1&&e.to<=n+m&&e.cap==0)
                {
                    tmp.push_back(e.to-n);
                }
            }
            assert(tmp.size()%2==0);
            for(int i=tot+1;i<=tot+tmp.size()/2;i++)
            {
                int id=i-tot-1;
                ans[tmp[2*id]]=ans[tmp[2*id+1]]=i;
            }
            tot+=tmp.size()/2;
        }
        for(int i=1;i<=m;i++) if(!ans[i]) ans[i]=++tot;
        print();
    }
    return 0;
}