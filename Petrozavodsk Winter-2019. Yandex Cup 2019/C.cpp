#include<bits/stdc++.h>
#define MAXN 1005
#define MAXM 1005
#define MAXK 10005
#define MAXV 30005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct edge{int to,cap,rev,id;};
vector<edge> G[MAXV];
int n,m,k;
int level[MAXV];
int iter[MAXV];
int p[MAXK],sg[MAXK],l[MAXK];
int w[MAXV];
void add_edge(int from,int to,int cap,int id)
{
    G[from].push_back((edge){to,cap,(int)G[to].size(),id});
    G[to].push_back((edge){from,0,(int)G[from].size()-1,0});
}
void bfs(int s)
{
    memset(level,-1,sizeof(level));
    queue<int> que;
    level[s]=0;
    que.push(s);
    while(!que.empty())
    {
        int v=que.front();que.pop();
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
        while((f=dfs(s,t,INF))>0) flow+=f;
    }
}
map<P,int> mp1,mp2;
//1..n people
//n+1..n+tot1 pair(people,language)
//n+tot1+1..n+tot1+tot2 pair(song,language)
//n+tot1+tot2+1..n+tot1+tot2+m song
int tot1,tot2;
vector<int> ans;
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=k;i++) 
    {
        scanf("%d%d%d",&p[i],&sg[i],&l[i]);
        if(!mp1[P(p[i],l[i])]) mp1[P(p[i],l[i])]=++tot1;
        if(!mp2[P(sg[i],l[i])]) mp2[P(sg[i],l[i])]=++tot2;
    }
    int V=n+tot1+tot2+m;
    int s=V+1,t=V+2,S=V+3,T=V+4;
    for(int i=1;i<=k;i++)
    {
        add_edge(n+mp1[P(p[i],l[i])],n+tot1+mp2[P(sg[i],l[i])],1,i);
    }
    for(auto p:mp1) add_edge(p.F.F,n+p.S,1,0);
    for(auto p:mp2) add_edge(n+tot1+p.S,n+tot1+tot2+p.F.F,1,0);
    add_edge(t,s,INF,0);
    for(int i=1;i<=n;i++)
    {
        add_edge(s,i,INF,0);
        w[s]+=1; w[i]-=1;
    }
    for(int i=1;i<=m;i++)
    {
        add_edge(n+tot1+tot2+i,t,INF,0);
        w[t]-=1; w[n+tot1+tot2+i]+=1;
    }
    int sum=0;
    for(int i=1;i<=V+2;i++)
    {
        if(w[i]>0) {add_edge(i,T,w[i],0); sum+=w[i];}
        else add_edge(S,i,-w[i],0); 
    }
    int f=max_flow(S,T);
    if(f!=sum) {puts("-1"); return 0;}
    for(int i=1;i<=V+4;i++)
    {
        for(auto &e:G[i])
        {
            if(!e.id) continue;
            if(e.cap==0) ans.push_back(e.id);
        }
    }
    sort(ans.begin(),ans.end());
    printf("%d\n",(int)ans.size());
    for(auto v:ans) printf("%d ",v);
    return 0;
}

