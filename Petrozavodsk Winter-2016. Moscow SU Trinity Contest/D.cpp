#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
const int maxn = 4e5 + 100;
typedef pair<int,int> pii;
int ans[maxn*2];
int Cnt;
int l[maxn];
struct SegmentTree{
    pii Max[maxn*4];
    void build(int x,int l,int r){
        Max[x] = make_pair(0,0);
        if (l == r)return;
        int mid = l + r >> 1;
        build(x<<1,l,mid);
        build(x<<1|1,mid+1,r);
    }
    void up(int x){
        Max[x] = max(Max[x<<1],Max[x<<1|1]);
    }
    void update(int x,int l,int r,int pos,pii val){
        if (l == r){
            Max[x] = val;
            return ;
        }
        int mid = l + r >> 1;
        if (pos <= mid)update(x<<1,l,mid,pos,val);
        else update(x<<1|1,mid+1,r,pos,val);
        up(x);
    }
    pii query(int x,int l,int r,int L,int R){
        if (l > R || L > r)return make_pair(0,0);
        if (L <= l && r <= R)return Max[x];
        int mid = l + r >> 1;
        return max(query(x<<1,l,mid,L,R),query(x<<1|1,mid+1,r,L,R));
    }
}tree,tree2;
set<pii> heap[maxn];
namespace HLD{
    int right[maxn];
    int dep[maxn],fa[maxn];
    int first[maxn],nxt[maxn],des[maxn],tot;
    int sz[maxn],wson[maxn],top[maxn],tpos[maxn],cnt = 0;
    void add_edge(int x,int y){
        tot ++;
        des[tot] = y;
        nxt[tot] = first[x];
        first[x] = tot;
    }
    void dfs(int u,int father){
        dep[u] = dep[father] + 1;
        fa[u] = father;
        sz[u] = 1;
        for (int t = first[u];t;t=nxt[t]){
            int v = des[t];
            if (v == father)continue;
            dfs(v,u);
            sz[u] += sz[v];
            if (sz[v] > sz[wson[u]])wson[u] = v;
        }
    }
    void dfs2(int node,int father,int chain){
        top[node] = chain;  tpos[node] = ++cnt;
        right[chain] = max(right[chain],cnt);
        if (wson[node]){
            dfs2(wson[node],node,chain);
        }
        for (int t = first[node];t;t=nxt[t]){
            int v = des[t];
            if (v==father||v ==wson[node]){  continue;  }
            dfs2(v,node,v);
        }
    }
    void init(int root){
        dfs(root,0);
        dfs2(root, 0, root);
    }
    void modify(int u,pii val,bool add){
        for (;u;u=fa[top[u]]){
            if (add){
                heap[u].insert(val);
            }else{
                heap[u].erase(val);
            }
            pii Val = {0,0};
            if (!heap[u].empty()){
                Val = *heap[u].rbegin();
                tree.update(1,1,Cnt,tpos[u],{l[u] + Val.first,Val.second});
                tree2.update(1,1,Cnt,tpos[u],Val);
            }else{
                tree.update(1,1,Cnt,tpos[u],Val);
                tree2.update(1,1,Cnt,tpos[u],Val);
            }

        }
    }
    pii query(int u){
        pii res = {0,0};
        for (;u;u=fa[top[u]]){
            res = max(res,tree.query(1,1,Cnt,tpos[top[u]],tpos[u]));
            pii tmp = tree2.query(1,1,Cnt,tpos[u],right[top[u]]);
            tmp.first += l[u];
            res = max(res,tmp);
        }
        return res;
    }

}
struct SAM{
    int nxt[maxn][26];
    int fa[maxn];
    int pos[maxn];
    int len = 0;
    int last,cnt;
    SAM(){
        clear();
    }
    void clear(){
        last = cnt = 1;
        fa[1] = l[1] = 0;
        memset(nxt[1],0,sizeof nxt[1]);
    }
    void init(char *s){
        while (*s){
            len ++;
            add(*s - 'a');
            s++;
        }
    }
    void add(int c){
        int p = last;
        int np = ++cnt;
        pos[len] = np;
//        memset(nxt[cnt],0,sizeof nxt[cnt]);
        l[np] = l[p] + 1;
        last = np;
        while (p && !nxt[p][c]) nxt[p][c] = np,p = fa[p];
        if (!p)fa[np] = 1;
        else{
            int q = nxt[p][c];
            if (l[q] == l[p] + 1)fa[np] = q;
            else{
                int nq = ++cnt;
                l[nq] = l[p] +1;
                memcpy(nxt[nq],nxt[q],sizeof nxt[q]);
                fa[nq] = fa[q];
                fa[np] = fa[q] = nq;
                while (nxt[p][c] == q)nxt[p][c] = nq,p = fa[p];
            }
        }
    }
    void extract(){
        for (int i=2;i<=cnt;i++){
            HLD::add_edge(fa[i],i);
        }
        ::Cnt = cnt;
    }
}sam;
int n,m;
vector<pii> query[maxn];
vector<pii> Q;
char s[maxn];
int read(){
    int ret = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9')ch = getchar();
    while (ch >= '0' && ch <= '9') ret = ret * 10 + ch - '0',ch = getchar();
    return ret;
}
int main(){
    n = read();
    m = read();
  //  scanf("%d%d",&n,&m);
    scanf("%s",s+1);
    sam.init(s+1);
    sam.extract();
    HLD::init(1);
    Q.resize(m + 2);
    for (int i=1;i<=m;i++){
        int l,r;
        l = read();
        r = read();
        //scanf("%d%d",&l,&r);
        query[r].push_back(make_pair(l,i));
        Q[i] = make_pair(l,r);
    }
    for (int i=n;i>=1;i--){
        int x = sam.pos[i];
        while (1){
            pii max_query = HLD::query(x);
            if (max_query.second == 0)break;
            if (max_query.first > i){
                int id = max_query.second;
                if (i >= Q[id].first){
                    ans[id] = max(ans[id],i - Q[id].first + 1);
                }
                HLD::modify(sam.pos[Q[id].second],make_pair(Q[id].first,id),false);
            }else break;
        }
        for (pii pr : query[i]){
            HLD::modify(x,pr,true);
        }
    }
    for (int i=1;i<=m;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}









