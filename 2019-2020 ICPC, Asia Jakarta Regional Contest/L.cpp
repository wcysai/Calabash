#include <bits/stdc++.h>
using namespace std;
const int maxn = 2000 + 100;
const int maxm = maxn * maxn;
typedef bitset<maxn> bs;
struct Max_Flow{
    int first[maxn * 2],nxt[maxm * 2],des[maxm * 2],c[maxm * 2],tot;
    int dep[maxn];
    int ss,tt;
    Max_Flow(){clear();}
    void clear(){
        memset(first,-1,sizeof first);
        tot = -1;
    }
    inline void addEdge(int u,int v,int w){
        tot ++;
        des[tot] = v;c[tot] = w;
        nxt[tot] = first[u];first[u] = tot;
    }
    bool bfs(){
        memset(dep,-1,sizeof dep);
        dep[ss] = 0;
        queue<int> Q;
        Q.push(ss);
        while (!Q.empty()){
            int q = Q.front();
            Q.pop();
            for (int t = first[q];t != -1;t=nxt[t]){
                int v = des[t],cx = c[t];
                if (dep[v] == -1 && cx){
                    dep[v] = dep[q] + 1;
                    Q.push(v);
                }
            }
        }
        return dep[tt] != -1;
    }
    int dfs(int node,int now){
        if (node == tt)return now;
        int res = 0;
        for (int t = first[node];t!= -1;t = nxt[t]){
            int v = des[t],cx = c[t];
            if (dep[v] == dep[node] + 1 && cx){
                int x = min(cx,now - res);
                x = dfs(v,x);
                res += x;c[t] -= x;c[t^1] += x;
            }
        }
        if (!res)dep[node] = -2;
        return res;
    }
    void init(vector<tuple<int,int,int> > Edge){
        for (auto tp : Edge){
            int u,v,w;
            tie(u,v,w) = tp;
            addEdge(u,v,w);addEdge(v,u,0);
        }
    }
    ll max_flow(int s,int t){
        ss = s;tt = t;
        ll res = 0,del = 0;
        while (bfs()){while (del = dfs(ss,INF)){res += del;}}
        return res;
    }
}net;
vector<int> C(0);
inline int id(int c){
    return lower_bound(C.begin(),C.end(),c) - C.begin();
}
vector<int> _cc[maxn];
bs color[maxn];
vector<int> E[maxn];
int n,k;
int main(){
    cin>>n>>k;
    for (int i=1;i<=n;i++){
        int v,m;
        cin>>v>>m;
        E[v].push_back(i);
        E[i].push_back(v);
        while (m--){
            int cc;
            cin>>cc;
            _cc[i].push_back(cc);
            C.push_back(cc);
        }
    }
    sort(C.begin(),C.end());
    C.erase(unique(C.begin(),C.end()),C.end());
    for (int i=1;i<=n;i++){

    }

}
