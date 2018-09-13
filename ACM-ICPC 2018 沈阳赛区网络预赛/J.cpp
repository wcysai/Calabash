#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+100;
const int BLOCK = sqrt(maxn);
typedef long long LL;
int first[maxn],des[maxn*2],nxt[maxn*2],tot;
int n,q;
struct BIT{
    LL val[maxn];
    int lowbit(int x){
        return x&(-x);
    }
    void add(int x,int delta){
        while (x< maxn){
            val[x]+= delta;
            x += lowbit(x);
        }
    }
    LL query(int x){
        LL ret =0;
        while (x){
            ret += val[x];
            x -= lowbit(x);
        }
        return ret;
    }
}small;
vector<vector<int> > Node;
int l[maxn],r[maxn];
int dfs_clock;
LL Val[maxn];
int dep[maxn];
vector<int> big;
inline void addEdge(int x,int y){
    tot ++;
    des[tot] = y;
    nxt[tot] = first[x];
    first[x] = tot;
}
void dfs(int node,int fa){
    l[node] = ++dfs_clock;
    Node[dep[node]].push_back(dfs_clock);
    for (int t = first[node];t;t=nxt[t]){
        int v = des[t];
        if (v == fa)continue;
        dep[v] = dep[node] +1;
        dfs(v,node);
    }
    r[node] = dfs_clock;
}
int main(){
    scanf("%d%d",&n,&q);
    Node.resize(n);
    for (int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    dfs(1,0);
    for (int i=0;i<n;i++){
        if (Node[i].size()>BLOCK){
            big.push_back(i);
        }
    }

    while (q--){
        int op;
        scanf("%d",&op);
        if (op == 1){
            //modify
            //O(BLOCK*logn)
            int L,X;
            scanf("%d%d",&L,&X);
            if (Node[L].size()<= BLOCK){
                for (int node : Node[L]){
                    small.add(node,X);
                }
            }else{
                Val[L] += X;
            }
        }else{
            //query
            // O(n/BLOCK *log)
            int X;
            scanf("%d",&X);
            LL ans = small.query(r[X]) - small.query(l[X]-1);
            for (int dep : big){
                ans += Val[dep]* (upper_bound(Node[dep].begin(),Node[dep].end(),r[X]) - lower_bound(Node[dep].begin(),Node[dep].end(),l[X]));
            }
            printf("%lld\n",ans);
        }
    }
    return 0;
}
