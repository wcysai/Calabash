#include <bits/stdc++.h>
using namespace std;

#define rep(i, n) for (int i = 0; i < int(n); i++)
#define Rep(i, n) for (int i = 1; i <=int(n); i++)
#define range(x) begin(x), end(x)
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug() ((void) 0)
#endif
typedef long long ll;
const int maxn = 5e5+100;
int first[maxn*2];int nxt[maxn*2];int des[maxn*2];
int tpos[maxn];int dep[maxn];int top[maxn];
int fa[maxn]; int wson[maxn];  int sz[maxn];
int n,q,m,Root,tot=0,cnt=0;  char s[10];
ll w[maxn],sum_w[maxn];
struct Seg_Tree{
    ll sum[maxn*4];
    ll lazy[maxn];
    void build(int x,int l,int r){
        sum[x] = lazy[x] = 0;
        if (l == r)return ;
        int mid = l+r >>1;
        build(x<<1,l,mid);
        build(x<<1|1,mid+1,r);
    }
    void up(int x){
        sum[x] = sum[x<<1] + sum[x<<1|1];
    }
    void down(int x,int l,int mid,int r){
        sum[x<<1] += 1ll * lazy[x] * (sum_w[mid] - sum_w[l-1]);
        sum[x<<1|1] += 1ll * lazy[x] * (sum_w[r] - sum_w[mid]);
        lazy[x<<1]+=lazy[x];
        lazy[x<<1|1] += lazy[x];
        lazy[x] = 0;
    }
    void add(int x,int l,int r,int L,int R){
        if (l>R || R>r)return;
        if (L<=l && r <= R){
            sum[x] += sum_w[r] - sum_w[l-1];
            lazy[x]++;
            return ;
        }
        int mid = l+r >>1;
        if (lazy[x]){
            down(x,l,mid,r);
        }
        add(x<<1,l,mid,L,R);add(x<<1|1,mid+1,r,L,R);
        up(x);
    }
    ll query(int x,int l,int r,int L,int R){
        if (l>R || L>r)return 0;
        if (L<= l && r<= R)return sum[x];
        int mid = l+r >>1;
        if (lazy[x])
            down(x,l,mid,r);
        return query(x<<1,l,mid,L,R) + query(x<<1|1,mid+1,r,L,R);
    }
}tree;
inline void addEdge(int _u, int _v){
    des[++tot] = _v;
    nxt[tot] = first[_u];
    first[_u] = tot;
}
namespace Tree_Chain_Division{
    //统计dep，子树sz，重儿子wson
    void dfs(int node,int father){
        dep[node] = dep[father]+1;
        fa[node] = father;  sz[node] =1;
        for (int t = first[node];t;t = nxt[t]){
            int v = des[t];
            if (v==father){  continue;  }
            dfs(v,node);
            if (sz[v]>sz[wson[node]]){
                wson[node] = v;
            }
            sz[node]+=sz[v];
        }
    }
    //node所在链的头是chain
    void dfs2(int node,int father,int chain){
        top[node] = chain;  tpos[node] = ++cnt;
        sum_w[cnt] = sum_w[cnt-1] + w[node] - w[father];
        if (wson[node]){
            dfs2(wson[node],node,chain);
        }
        for (int t = first[node];t;t = nxt[t]){
            int v = des[t];
            if (v==father||v ==wson[node]){  continue;  }
            dfs2(v,node,v);
        }
    }
    /* s 树根 */
    void init(int root){
        dfs(root,0);
        dfs2(root, 0, root);
    }
    int lca(int x,int y){
        while (top[x]!=top[y]){
            if (dep[top[x]]<dep[top[y]]){swap(x,y);}
            x = fa[top[x]];
        }
        if (dep[x]<dep[y])swap(x,y);
        return y;
    }
    void modify(int u,int v){
        while (top[u]!=top[v]){
            if (dep[top[u]]<dep[top[v]]){  swap(u,v);  }
            tree.add(1,1,n,tpos[top[u]],tpos[u]);
            //res+= tree.query(1,1,n,tpos[top[u]],tpos[u]);
            u = fa[top[u]];
        }
        if (dep[u]<dep[v]){  swap(u,v); }
        tree.add(1,1,n,tpos[v],tpos[u]);
        //res += tree.query(1,1,n,tpos[v],tpos[u]);
    }
    int get_sum(int u,int v){
        int res =0;
        while (top[u]!=top[v]){
            if (dep[top[u]]<dep[top[v]]){  swap(u,v);  }
            res+= tree.query(1,1,n,tpos[top[u]],tpos[u]);
            u = fa[top[u]];
        }
        if (dep[u]<dep[v]){  swap(u,v); }
        res += tree.query(1,1,n,tpos[v],tpos[u]);
        return res;
    }
}


int main(){
    while(scanf("%d",&n)!= EOF){
        tree.build(1,1,n);
        cnt=0;
        for (int i=1;i<=n;i++){
            first[i] = 0;
        }
        tot =0;
        for (int i=1;i<=n;i++){
            scanf("%lld",w+i);
        }
        for (int i=2;i<=n;i++){
            int p;
            scanf("%d",&p);
            addEdge(p,i);
        }
        Tree_Chain_Division::init(1);
        for (int i=1;i<=n;i++){
            if (i!=1)
            printf("%lld\n",Tree_Chain_Division::get_sum(1,i));
            Tree_Chain_Division::modify(1,i);
        }
    }
    return 0;
}
/*
 3
 1 2 3
 1 1
 5
 1 2 3 4 5
 1 2 2 1

 */
