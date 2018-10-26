//
// Created by calabash on 10/24/18.
//
#include<bits/stdc++.h>
using namespace std;
const int maxn = 200000+100;
const int INF = 0x3f3f3f3f;
const int inf = INF;
int C;
int first[maxn],nxt[maxn*2],des[maxn*2],c[maxn*2],tot;
int dep[maxn];int m,n,ss,tt;
void init(){
    memset(first,-1,sizeof first);
    tot =-1;
}
inline void addEdge(int u,int v,int w){
    tot++;
    des[tot] = v;c[tot] =w;
    nxt[tot] = first[u];first[u] = tot;
}
bool bfs(){
    memset(dep,-1,sizeof dep);
    dep[ss] =0;
    queue<int> Q;Q.push(ss);
    while (!Q.empty()){
        int q = Q.front();Q.pop();
        for (int t = first[q];t!=-1;t= nxt[t]){
            int v = des[t],cx = c[t];
            if (dep[v]==-1&&cx){
                dep[v] = dep[q]+1;
                Q.push(v);
            }
        }
    }
    return dep[tt]!=-1;
}
int dfs(int node,int now){
    if (node==tt)return now;
    int res =0;
    for (int t = first[node];t!=-1&&res<now;t=nxt[t]){
        int v = des[t],cx = c[t];
        if (dep[v]==dep[node]+1&&cx){
            int x = min(cx,now-res);
            x = dfs(v,x);
            res +=x;
            c[t] -= x;c[t^1]+=x;
        }
    }
    if (!res) dep[node] = -2;
    return res;
}

vector<pair<int,int> > E[maxn];
int Dis[maxn];
bool used[maxn];
struct Node{
    int u,dis;
    bool operator < (const Node &other)const {
        return other.dis < dis;
    }
};
void dij(int S){
    priority_queue<Node> Q;
    Q.push({S,0});
    memset(Dis,inf,sizeof Dis);
    memset(used,0,sizeof used);
    Dis[S] = 0;
    while (!Q.empty()){
        Node head = Q.top();Q.pop();
        int u = head.u;
        int dis = head.dis;
        if (used[u])continue;
        used[u] = 1;
        for (auto pr : E[u]){
            int v = pr.first;
            int len = pr.second;
            if (Dis[v] > Dis[u] + len){
                Dis[v] = Dis[u] + len;
                Q.push({v,Dis[v]});
            }
        }
    }
}
vector<pair<int,int> > Edge(0);
void build_dag(int S){
    for (int u=1;u<=n;u++){
        for (auto pr : E[u]){
            int v = pr.first;
            int len = pr.second;
            if (Dis[v] == Dis[u] + len){
                Edge.push_back({u,v});
            }
        }
    }
}
int Pos[maxn];
vector<int> cls[maxn];

int solve(int x){
    if (cls[x].empty())return 0;

    init();
    for (auto pr : Edge){
        addEdge(pr.first,pr.second,1);
        addEdge(pr.second,pr.first,0);
    }
    ss =1,tt = n+1;
    for (auto xx : cls[x]){
        addEdge(xx,tt,1);
        addEdge(tt,xx,0);
    }
    int res =0,del =0;
    while (bfs()){
        while (del = dfs(ss,INF)){res += del;}
    }
    return res;
}
void debug(){
    for (auto pr : Edge){
        printf("[Edge in DAG] %d->%d\n",pr.first,pr.second);
    }
}
int main(){
    int ans =0;
    init();
    scanf("%d%d%d",&n,&m,&C);
    for (int i=0;i<m;i++){
        int x,y,t;
        scanf("%d%d%d",&x,&y,&t);
        E[x].push_back({y,t});
        E[y].push_back({x,t});
    }
    dij(1);
    build_dag(1);
    //debug();
    vector<int> id(0);
    for (int i=1;i<=C;i++){
        scanf("%d",Pos+i);
        id.push_back(Dis[Pos[i]]);
    }
    sort(id.begin(),id.end());
    id.erase(unique(id.begin(),id.end()),id.end());
    for (int i=1;i<=C;i++){
       // printf("Dis[%d]=%d\n",Pos[i],Dis[Pos[i]]);
        if (Dis[Pos[i]] == 0){
            ans ++;
            continue;
        }

        int Id = lower_bound(id.begin(),id.end(),Dis[Pos[i]]) - id.begin();
       // printf("id = %d\n",Id);
        cls[Id].push_back(Pos[i]);
    }

    for (int i=0;i<id.size();i++){
        ans += solve(i);
    }
    cout<<ans<<endl;
    return 0;
}
/*
3 3 2
 1 2 42
 2 3 1
 2 3 1
 2 3




 4 4 5
 1 2 5
 1 3 4
 4 2 5
 4 3 6
 4 4 4 4 1
 */
