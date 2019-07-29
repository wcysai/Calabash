#include <bits/stdc++.h>
using namespace std;
const int maxn = 200000+100;
char s[maxn];
//char s[maxn];
int n;
pair<int,int> ans[maxn];
struct SAM{
    int nxt[maxn*2][26],fa[maxn*2],l[maxn*2];
    int last,cnt;
    int endpos[maxn*2];
    int son1[maxn*2];
    int son2[maxn*2];
    bool key[maxn*2];
    vector<int> E[maxn*2];
    int pos[maxn*2];
    SAM(){clear();}
    void clear(){
        last = cnt = 1;
        fa[1] = l[1] = 0;
        memset(nxt[1],0,sizeof nxt[1]);
    }
    void init(char *s){
        while (*s){
            add(*s - 'a');
            s++;
        }
    }
    void add(int c){
        int p = last;
        int np = ++cnt;
        memset(nxt[cnt],0,sizeof nxt[cnt]);
        l[np] = l[p] + 1;
        last = np;
        while (p && !nxt[p][c]) nxt[p][c] = np,p = fa[p];
        if (!p)fa[np] = 1;
        else{
            int q = nxt[p][c];
            if (l[q] == l[p] + 1)fa[np] = q;
            else{
                int nq = ++cnt;
                l[nq] = l[p] + 1;
                memcpy(nxt[nq],nxt[q],sizeof nxt[q]);
                fa[nq] = fa[q];
                fa[np] = fa[q] = nq;
                while (nxt[p][c]  == q)nxt[p][c] = nq,p = fa[p];
            }
        }
    }
    void build(char *s){
        for (int i=1;i<=cnt;i++){
            endpos[i] = -1;
        }
        int temp = 1;
        for (int i=0;i<n;i++){
            temp = nxt[temp][s[i] - 'a'];
            key[temp] = 1;
            endpos[temp] = i;
            //endpos[temp] = i+1;
            //int t = temp;
            //while(endpos[t] == -1){
            //    endpos[t] = i;
            //    t = fa[t];
            // }
            pos[i] = temp; 
        }
    }
    void extract(){
        for (int i=1;i<=cnt;i++){
            E[i].clear();
        }
        for (int i=2;i<=cnt;i++){
            E[fa[i]].push_back(i);
        }
    }
    int sz[maxn*2];
    int wson[maxn*2];
    int top[maxn*2];
    int dep[maxn*2];
    void dfs(int u,int father){
        dep[u] = dep[father] + 1;
        fa[u] = father;
        sz[u] = 1;
        for (int v : E[u]){
            if (v == father)continue;
            dfs(v,u);
            if (sz[v] > sz[wson[u]])wson[u] = v;
            sz[u] += sz[v];
        }
    }
    void dfs2(int u,int father,int chain){
        top[u] = chain;
        if (wson[u]) dfs2(wson[u],u,chain);
        for (int v : E[u]){
            if (v == father || v == wson[u])continue;
            dfs2(v,u,v);
        }
    }
    void build_lca(){
        for (int i=1;i<=cnt;i++){
            wson[i] = 0;
        }
        dfs(1,0);
        dfs2(1,0,1);
    }
    int lca(int x,int y){
        while (top[x] != top[y]){
            if (dep[top[x]] < dep[top[y]])swap(x,y);
            x = fa[top[x]];
        }
        if (dep[x] < dep[y])swap(x,y);
        return y;
    }
    int cmp(int l1,int r1,int l2,int r2){
        //r1 = n-1 - r1;
        //l1 = n-1 - l1;
        //l2 = n-1 - l2;
        //r2 = n-1 - r2;
        //swap(l1,r1);
        //swap(l2,r2);
        int u = pos[r1],v = pos[r2];
        int LCA = lca(u,v);
        int lcs = l[LCA];
        if (lcs >= r1 - l1 + 1)return 0;
        if (s[r1 - lcs ] < s[r2 - lcs])return -1;
        else return 1;
    }
    void update(int lcp,int endpos1,int endpos2){
        if (ans[lcp].first == -1){
            ans[lcp] = {endpos1,endpos2};
            return;
        }
        int resu = cmp(endpos1 - lcp+1,endpos1,ans[lcp].first - lcp + 1,ans[lcp].first);
        if (resu<0){
            ans[lcp] = {endpos1,endpos2};
        }else if (resu == 0){
            ans[lcp] = max(ans[lcp],{endpos1,endpos2});
        }
    }
    void dfs_ans(int u,int father){
        if (E[u].size() == 0){
            son1[u] = endpos[u];
            return;
        }
        for (int v : E[u]){
            if (v == father)continue;
            dfs_ans(v,u);
            vector<int> t(0);
            //TODO
            t.push_back(son1[u]);
            t.push_back(son2[u]);
            t.push_back(son1[v]);
            sort(t.begin(),t.end());
            son1[u] = t[2];
            son2[u] = t[1];
        }
        if (key[u]){
            //if (endpos[u] >= son1[u]){
            vector<int> t(0);
            t.push_back(son1[u]);
            t.push_back(son2[u]);
            t.push_back(endpos[u]);
            sort(t.begin(),t.end());
            son1[u] = t[2];
            son2[u] = t[1];
        }
        if (son1[u]!= -1 && son2[u] != -1){
            update(l[u],son1[u],son2[u]);
        }

    }
    void main(){
        for (int i=1;i<=cnt;i++){
            son1[i] = son2[i] = -1;
        }
        dfs_ans(1,0);
    }
}sam2;
int main(){
    scanf("%s",s);
    n = strlen(s);
    reverse(s,s+n);
    sam2.init(s);
    sam2.build(s);
    sam2.extract();
    sam2.build_lca();
    int q;
    scanf("%d",&q);
    for (int i=0;i<maxn;i++){
        ans[i] = {-1,-1};
    }
    for (int i=0;i<n;i++){
        ans[i+1] = {i,i};
    }
    sam2.main();
    while (q--){
        int lcp;
        scanf("%d",&lcp);
        pair<int,int> Ans = ans[lcp];
        if (Ans.first == -1 ){
            puts("-1 -1");
        }else
        printf("%d %d\n",n-Ans.first,n-Ans.second);
    }
    return 0;
}


