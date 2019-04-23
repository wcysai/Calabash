#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+100;
typedef tuple<int,int,int> ITEM;
int n,m;
vector<int> E[maxn];
int wson[maxn];
int pos[maxn];
int sz[maxn];
int dep[maxn];
int father[maxn];
int top[maxn];
int tpos[maxn];
int cnt;
void dfs(int u,int fa){
    dep[u] = dep[fa] + 1;
    sz[u] = 1;
    father[u] = fa;
    for (int v : E[u]){
        if (v == fa)continue;
        dfs(v,u);
        if (sz[v] > sz[wson[u]])wson[u] = v;
        sz[u] += sz[v];
    }
}
void dfs2(int node,int father,int chain){
    top[node] = chain;
    tpos[node] = ++cnt;
    if (wson[node])dfs2(wson[node],node,chain);
    for (int v : E[node]){
        if (v == father || v == wson[node])continue;
        dfs2(v,node,v);
    }
}
vector<tuple<int,int,int> > Edges;
vector<int> EE[maxn];
vector<ITEM> all_items;
vector<ITEM> useful;
void lca(int x,int y,int w){
    if (x == y)return;
    while (top[x] != top[y]){
        if (dep[top[x]] < dep[top[y]])swap(x,y);
        all_items.push_back(make_tuple(tpos[top[x]],tpos[x],w));
        x = father[top[x]];
    }
    if (x == y)return;
    if (dep[x] < dep[y])swap(x,y);
    all_items.push_back(make_tuple(tpos[y] + 1,tpos[x],w));
}
int min_val[maxn];
struct Node{
    int l,r,w;
    bool operator < (const Node & other)const {
        return other.w < w;
    }
};
void prework(){
    for (int i=1;i<=n;i++){
        min_val[i] = INT_MAX;
    }
    sort(all_items.begin(),all_items.end(),[](ITEM x,ITEM y){
       return get<0>(x) > get<0>(y); 
    });
    priority_queue<Node> pq;
    for (int i=1;i<=n;i++){
        while (!pq.empty() && pq.top().r < i)pq.pop();
        while (!all_items.empty()){
            int l,r,w;
            tie(l,r,w) = all_items.back();
            if (l == i){
                all_items.pop_back();
                pq.push((Node){l,r,w});
            }else break;
        }
        if (!pq.empty()){
            min_val[i] = pq.top().w;
        }
    }
    for (int i=1;i<=n;i++){
        int pos = tpos[i];
        int w = min_val[pos];
        if (w == INT_MAX)continue;
        Edges.push_back(make_tuple(i,father[i],w));
    }
}
int fa[maxn];
int find(int x){
    return fa[x] == x?x:fa[x] = find(fa[x]);
}
void kruskal(){
    for (int i=1;i<=n;i++){
        fa[i] = i;
    }
    sort(Edges.begin(),Edges.end(),[](ITEM x,ITEM y){
        return get<2>(x) < get<2>(y); 
    });
    for (ITEM edge : Edges){
        int u,v,w;
        tie(u,v,w) = edge;
        int fu = find(u);
        int fv = find(v);
        if (fu == fv)continue;
        fa[fu] = fv;
        useful.push_back(make_tuple(u,v,w));
    }
    int ans1 = 0;
    long long ans2 = 0;
    int anc = find(1);
    for (ITEM edge: useful){
        int u,v,w;
        tie(u,v,w) = edge;
        int fu = find(u);
        if (fu == anc){
            ans2 += w;
        }
    }
    for (int i=1;i<=n;i++){
        if (find(i) == anc)ans1++;
    }
    cout<<ans1<<" "<<ans2<<endl;
}
int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        E[u].push_back(v);
        E[v].push_back(u);
    }
    dfs(1,0);
    dfs2(1,0,1);
    for (int i=0;i<m;i++){
        int u,v,U,V,w;
        scanf("%d%d%d%d%d",&u,&v,&U,&V,&w);
        lca(u,v,w);
        lca(U,V,w);
        Edges.push_back(make_tuple(u,U,w));
    }
    prework();
    kruskal();
    return 0;   
}
