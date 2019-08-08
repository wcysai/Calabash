#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 100;
const int inf = 0x3f3f3f3f;
int n,m;
int W[maxn];
int ans[maxn];
struct Query{
    int x,k,id;
    Query(int x_,int k_,int id_):x(x_),k(k_),id(id_){}
    Query(){}
}Q[maxn];
namespace HLD{
    int first[maxn];int nxt[maxn*2];int des[maxn*2];
    int tot,cnt=0;
    int nid[maxn];
    int tpos[maxn];int dep[maxn];int top[maxn],bottom[maxn];
    int fa[maxn]; int wson[maxn];  int sz[maxn];
    int p_mx[maxn];
    set<pair<int,int> > tags0[maxn],tags1[maxn];
    struct SegmentTree{
        pair<int,int> mx[maxn * 4];
        void up(int x){
            mx[x] = max(mx[x<<1],mx[x<<1|1]);
        }
        void build(int x,int l,int r,set<pair<int,int> > *tags){
            if (l == r){
                mx[x] = *tags[l].begin();
                mx[x].first *= -1;
                return;
            }
            int mid = l + r >> 1;
            build(x << 1,l,mid,tags);
            build(x<< 1 | 1,mid+ 1,r,tags);
            up(x);
        }
        pair<int,int> query(int x,int l,int r,int L,int R){
            if (l > R || L > r)return make_pair(-inf,-1);
            if (L <= l && r <= R)return mx[x];
            int mid = l + r >> 1;
            return max(query(x<<1, l, mid, L, R) , query(x<<1|1, mid+1, r, L,R));
        }
        void update(int x,int l,int r,int pos,pair<int,int> pi){
            if (l == r){
                mx[x] = pi;
                return;
            }
            int mid = l + r >> 1;
            if (pos <= mid)update(x<<1,l,mid,pos,pi);
            else update(x<<1|1,mid+1,r,pos,pi);
            up(x);
        }
    }T0,T1;
    inline void addEdge(int _u, int _v){
        des[++tot] = _v;
        nxt[tot] = first[_u];
        first[_u] = tot;
    }
    inline void clear(int n){
        n += 5;
        memset(first,0,sizeof(int) * n);
        memset(tpos,0,sizeof(int) * n);
        dep[0] = tot = cnt = 0;
        memset(wson,0,sizeof (int) * n);
        for (int i=1;i<=n;i++){
            tags0[i].clear();
            tags0[i].insert(make_pair(inf,-1));
            tags1[i].clear();
            tags1[i].insert(make_pair(inf,-1));

        }
    }
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
    void dfs2(int node,int father,int chain){
        top[node] = chain;  tpos[node] = ++cnt;
        nid[cnt] = node;bottom[chain] = node;
        if (wson[node]){
            dfs2(wson[node],node,chain);
        }
        for (int t = first[node];t;t = nxt[t]){
            int v = des[t];
            if (v==father||v ==wson[node]){  continue;  }
            dfs2(v,node,v);
        }
    }
    void init(int root){
        dfs(root,0);
        dfs2(root, 0, root);
        for (int i=1;i<=n;i++){
            int node = nid[i];
            p_mx[i] = W[node];
            if (node != top[node])p_mx[i] = max(p_mx[i-1],p_mx[i]);
            if (node != top[node]) bottom[node] = bottom[top[node]];
        }
    }
    void build(){
        T0.build(1, 1, n, tags0);
        T1.build(1, 1, n, tags1);
    }
    void add(const Query & q){
        int x = q.x, k = q.k;
        while (x){
            int mx = p_mx[tpos[x]];
            tags0[tpos[x]].insert(make_pair(-(mx + k),q.id));
            tags1[tpos[x]].insert(make_pair(-k,q.id));
            x = fa[top[x]];
        }
    }
    void remove(const Query & q){
        int x = q.x, k = q.k;
        while (x){
            int mx = p_mx[tpos[x]];
            tags0[tpos[x]].erase(make_pair(-(mx + k),q.id));
            pair<int,int> pi0 = *tags0[tpos[x]].begin();
            pi0.first *= -1;
            T0.update(1, 1, n, tpos[x], pi0);
            tags1[tpos[x]].erase(make_pair(-k,q.id));
            pair<int,int> pi1 = *tags1[tpos[x]].begin();
            pi1.first *= -1;
            T1.update(1, 1, n, tpos[x], pi1);
            x = fa[top[x]];
        }
    }
    pair<int,int> query(int x){
        pair<int,int> ret = make_pair(-inf,-1);
        while (x){
            ret = max(ret,T0.query(1, 1, n, tpos[top[x]], tpos[x]));
            pair<int,int> tmp = T1.query(1,1,n,tpos[x],tpos[bottom[x]]);
            tmp.first += p_mx[tpos[x]];
            ret = max(ret,tmp);
            x = fa[top[x]];
        }
        return ret;
    }
    void solve(){
        for(int i=n;i>=1;i--){
            while (1){
                pair<int,int> qpi = query(i);
                if (qpi.first >= i){
                    ans[qpi.second] = i;
                    remove(Q[qpi.second]);
                }else break;
            }

        }
    }
    int lca(int x,int y){
        while (top[x]!=top[y]){
            if (dep[top[x]]<dep[top[y]]){swap(x,y);}
            x = fa[top[x]];
        }
        if (dep[x]<dep[y])swap(x,y);
        return y;
    }
}

int main(){
    scanf("%d%d",&n,&m);
    HLD::clear(n);
    for (int i=1;i<=n;i++){
        scanf("%d",W+i);
    }
    for (int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        HLD::addEdge(u, v);
        HLD::addEdge(v, u);
    }
    HLD::init(1);
    for (int i=1;i<=m;i++){
        int x,k;
        scanf("%d%d",&x,&k);
        Q[i] = Query(x,k,i);
        HLD::add(Q[i]);
    }
    HLD::build();
    HLD::solve();
    for (int i=1;i<=m;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}
/*
 3 1
 2 2 2
 1 2
 1 3
 3 0
 */
