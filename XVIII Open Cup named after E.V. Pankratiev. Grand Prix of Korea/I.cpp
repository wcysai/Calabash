//
// Created by calabash_boy on 18-6-4.
//SPOJ substring
// calc ans_i=é•¿åº¦=içš„æ‰€æœ‰å­ä¸²ï¼Œå‡ºçŽ°æ¬¡æ•°æœ€å¤šçš„ä¸€ç§å‡ºçŽ°äº†å¤šå°‘æ¬¡ã€‚
//
#include<bits/stdc++.h>
typedef long long LL;
using namespace std;
const int maxn = 2e5+100;
char s[maxn];
int n;
int ans [maxn];
int val[maxn];
struct Seg_Tree{
    LL val[maxn*4];LL lazy[maxn*4];
    inline void Up(int x){val[x] = val[x<<1]+val[x<<1|1];}
    inline void Down(int x,int l,int mid,int r,int* fa,int * dep){
        if (lazy[x]){
            val[x<<1] += 1LL*lazy[x]*(::val[mid] - ::val[l-1]);
            val[x<<1|1] += 1LL*lazy[x]*(::val[r] - ::val[mid]);
            lazy[x<<1]+= lazy[x];
            lazy[x<<1|1] += lazy[x];
            lazy[x] =0;
        }
    }
    void add(int x,int l,int r,int L,int R,int del,int* fa,int* dep){
        if (l>R||r<L)return;
        if (L<=l&&r<=R){
            val[x]+=1LL*del*(::val[r] - ::val[l-1]);
            lazy[x]+=del;
            return;
        }
        int mid = l+r >>1;
        Down(x,l,mid,r,fa,dep);
        add(x<<1,l,mid,L,R,del,fa,dep);add(x<<1|1,mid+1,r,L,R,del,fa,dep);
        Up(x);
    }
    LL query_Sum(int x,int l,int r,int L,int R,int* fa,int* dep){
        if (l>R||r<L)return 0;
        if (L<=l&&r<=R)return val[x];
        int mid = l+r >>1;
        Down(x,l,mid,r,fa,dep);
        return query_Sum(x<<1,l,mid,L,R,fa,dep)+query_Sum(x<<1|1,mid+1,r,L,R,fa,dep);
    }
}tree;

namespace Tree_Chain_Division{
    int first[maxn],nxt[maxn*2],des[maxn*2],tot=0;
    int tpos[maxn],dep[maxn],top[maxn];
    int fa[maxn],wson[maxn],sz[maxn];
    int cnt=0;
    inline void addEdge(int x,int y){
        tot++;
        des[tot] = y;
        nxt[tot] = first[x];
        first[x] = tot;
    }
    void dfs(int node,int father,int* fa_sam,int* l_sam){
        dep[node] = dep[father]+l_sam[node] - l_sam[fa_sam[node]];
        fa[node] = father;  sz[node] =1;
        for (int t = first[node];t;t = nxt[t]){
            int v = des[t];
            if (v==father){  continue;  }
            dfs(v,node,fa_sam,l_sam);
            if (sz[v]>sz[wson[node]]){
                wson[node] = v;
            }
            sz[node]+=sz[v];
        }
    }
    //nodeæ‰€åœ¨é“¾çš„å¤´æ˜¯chain
    void dfs2(int node,int father,int chain,int* fa_sam,int* sam_l){
        top[node] = chain;  tpos[node] = ++cnt; ::val[cnt] = sam_l[node] - sam_l[fa[node]];
        if (wson[node]){
            dfs2(wson[node],node,chain,fa_sam,sam_l);
        }
        for (int t = first[node];t;t = nxt[t]){
            int v = des[t];
            if (v==father||v ==wson[node]){  continue;  }
            dfs2(v,node,v,fa_sam,sam_l);
        }
    }
    /* s æ ‘æ ¹ */
    void init(int root,int * fa_sam,int* l_sam){
        dfs(root,0,fa_sam,l_sam);
        dfs2(root, 0, root,fa_sam,l_sam);
    }
    pair<LL,LL> query(int u,int v){
        LL res_sum =0;
        LL node_cnt =0;
        while (top[u] != top[v]){
            if (dep[top[u]] < dep[top[v]]) swap(u,v);
//            res_sum += bit.query(tpos[top[u]],tpos[u]);
            res_sum += tree.query_Sum(1,1,cnt,tpos[top[u]],tpos[u],fa,dep);
            node_cnt += ::val[tpos[u]] - ::val[tpos[top[u]]-1];
            u = fa[top[u]];
        }
        if (dep[u] <dep[v]) swap(u,v);
//        res_sum += bit.query(tpos[v],tpos[u]);
        res_sum += tree.query_Sum(1,1,cnt,tpos[v],tpos[u],fa,dep);
        node_cnt += ::val[tpos[u]] - ::val[tpos[v]-1] ;
        return {res_sum ,node_cnt};

    }
    void update(int u,int v){
        while (top[u] != top[v]){
            if (dep[top[u]] < dep[top[v]]) swap(u,v);
//            bit.add(tpos[top[u]],tpos[u],1);
            tree.add(1,1,cnt,tpos[top[u]],tpos[u],1,fa,dep);
            u = fa[top[u]];
        }
        if (dep[u] < dep[v]) swap(u,v);
        int l = min(tpos[u],tpos[v]);
        int r = max(tpos[u],tpos[v]);
//        bit.add(l,r,1);
        tree.add(1,1,cnt,l,r,1,fa,dep);
    }
}



/*æ³¨æ„éœ€è¦æŒ‰lå°†èŠ‚ç‚¹åŸºæ•°æŽ’åºæ¥æ‹“æ‰‘æ›´æ–°parentæ ‘*/
struct Suffix_Automaton{
    //basic
    int nxt[maxn*2][26],fa[maxn*2],l[maxn*2];
    int last,cnt;
    //extension
    int cntA[maxn*2],A[maxn*2];/*è¾…åŠ©æ‹“æ‰‘æ›´æ–°*/
    int num[maxn*2];/*æ¯ä¸ªèŠ‚ç‚¹ä»£è¡¨çš„æ‰€æœ‰ä¸²çš„å‡ºçŽ°æ¬¡æ•°*/
    void clear(){
        last =cnt=1;
        fa[1]=l[1]=0;
        memset(nxt[1],0,sizeof nxt[1]);
    }
    void init(char *s){
        while (*s){
            add(*s-'a');
            s++;
        }
    }
    void add(int c){
        int p = last;
        int np = ++cnt;
        memset(nxt[cnt],0,sizeof nxt[cnt]);
        l[np] = l[p]+1;
        last = np;
        while (p&&!nxt[p][c])nxt[p][c] = np,p = fa[p];
        if (!p)fa[np]=1;
        else{
            int q = nxt[p][c];
            if (l[q]==l[p]+1)fa[np] =q;
            else{
                int nq = ++ cnt;
                l[nq] = l[p]+1;
                memcpy(nxt[nq],nxt[q],sizeof (nxt[q]));
                fa[nq] =fa[q];
                fa[np] = fa[q] =nq;
                while (nxt[p][c]==q)nxt[p][c] =nq,p = fa[p];
            }
        }
    }
    void build(){
        memset(cntA,0,sizeof cntA);
        memset(num,0,sizeof num);
        for (int i=1;i<=cnt;i++)cntA[l[i]]++;
        for (int i=1;i<=n;i++)cntA[i]+=cntA[i-1];
        for (int i=cnt;i>=1;i--)A[cntA[l[i]]--] =i;
        /*æ›´è¡Œä¸»ä¸²èŠ‚ç‚¹*/
        int temp=1;
        for (int i=0;i<n;i++){
            num[temp = nxt[temp][s[i]-'a'] ]=1;
        }
        /*æ‹“æ‰‘æ›´æ–°*/
        for (int i=cnt;i>=1;i--){
            //basic
            int x = A[i];
            num[fa[x]]+=num[x];
            //special
            ans[l[x]] = max(ans[l[x]],num[x]);
        }
        //special
        for (int i=l[last];i>1;i--){
            ans[i-1] = max(ans[i-1],ans[i]);
        }
    }
    void debug(){
        for (int i=cnt;i>=1;i--){
            printf("num[%d]=%d l[%d]=%d fa[%d]=%d\n",i,num[i],i,l[i],i,fa[i]);
        }
    }
    void build_tree(){
        for (int i=2;i<=cnt;i++){
            //cerr<<i<<" "<<fa[i]<<endl;
            Tree_Chain_Division::addEdge(fa[i],i);
            Tree_Chain_Division::addEdge(i,fa[i]);
        }
        Tree_Chain_Division::init(1,fa,l);
        for (int i=1;i<maxn;i++){
            ::val[i] += ::val[i-1];
        }
    }
    void main(){
        int now =1;
        LL ans =0;
        for (int i=0;i<n;i++){
            int id = s[i]-'a';
            now = nxt[now][id];

            //cout<<"now:"<<now<<endl;
            pair<LL,LL> tmp_res = Tree_Chain_Division::query(1,now);
            //cout<<tmp_res.first<<" "<<tmp_res.second<<endl;
            ans += tmp_res.second;
            ans += 2*tmp_res.first;
            Tree_Chain_Division::update(1,now);
            printf("%lld\n",ans);
        }

    }
}sam;
int main(){
    scanf("%s",s);
    /* calc n must before sam.init()*/
    n = strlen(s);
    sam.clear();
    sam.init(s);
    sam.build();
    sam.build_tree();
    sam.main();
    return 0;
}
