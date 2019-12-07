#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 100;
struct SAM{
    int nxt[maxn*2][26],fa[maxn*2],l[maxn*2];
    int last,cnt;
    int Num[maxn*2];
    SAM(){clear();}
    vector<int> E[maxn*2];
    void clear(){
        last = cnt = 1;
        fa[1] = l[1] = 0;
        memset(nxt[1],0,sizeof nxt[1]);
    }
    int add(int pre,int c,int num){
        last = pre;
        int p = last;
        int np = ++cnt;
        Num[np] = num;
        memset(nxt[cnt],0,sizeof nxt[cnt]);
        l[np] = l[p] + 1;last = np;
        while (p && !nxt[p][c])nxt[p][c] = np,p = fa[p];
        if (!p)fa[np] = 1;
        else{
            int q = nxt[p][c];
            if (l[q] == l[p] + 1)fa[np] = q;
            else{
                int nq = ++cnt;
                l[nq] = l[p] + 1;
                memcpy(nxt[nq],nxt[q],sizeof nxt[q]);
                fa[nq] = fa[q];fa[np] = fa[q] = nq;
                while (nxt[p][c] == q)nxt[p][c] = nq,p = fa[p];
            }
        }
        return np;
    }
    void dfs(int u,int fa){
        st[u][0] = fa;
        for (int i=1;i<20;i++){
            st[u][i] = st[st[u][i-1]][i-1];
        }
        for (int v : E[u]){
            dfs(v,u);
            Num[u] += Num[v];
        }
    }
    int st[maxn*2][20];
    void build(){
        for (int i=2;i<=cnt;i++){
            E[fa[i]].push_back(i);   
        }
        dfs(1,0);
    }
    int query(int u,int len){
        for (int i=19;i>=0;i--){
            int v = st[u][i];
            if (v and l[fa[v]] + 1 >len)u = v;
        }
        if (l[fa[u]] + 1 > len)u = fa[u];
        return Num[u];
    }
}sam;

struct Trie{
    int Root = 1;
    int cnt = 2;
    int nxt[maxn][26];
    int num[maxn];
    int sam_pos[maxn];
    int add(int p,int ch){
        if (!nxt[p][ch]){
            nxt[p][ch] = cnt++;
        }
        int now = nxt[p][ch];
        num[now] ++;
        return now;
    }
    void bfs(){
        queue<int> Q;
        Q.push(1);
        sam_pos[1] = 1;
        while (!Q.empty()){
            int head =Q.front();Q.pop();
            for (int i=0;i<26;i++){
                if (!nxt[head][i])continue;
                int now = nxt[head][i];
                sam_pos[now] = sam.add(sam_pos[head],i,num[now]);
                Q.push(now);
            }
        }
    }
}trie;
char s[maxn];
int trie_pos[maxn];
int main(){
    int n,q;
    scanf("%d%d",&n,&q);
    scanf("%s",s+1);
    trie_pos[1] = trie.add(1,s[1] - 'A');
    for (int i=2;i<=n;i++){
        int fa;
        scanf("%d",&fa);
        trie_pos[i] = trie.add(trie_pos[fa],s[i] - 'A');
    }
    trie.bfs();
    sam.build();
    while (q--){
        int x,l;
        scanf("%d%d",&x,&l);
        printf("%d\n",sam.query(trie.sam_pos[trie_pos[x]],l));
    }
    return 0;
}
