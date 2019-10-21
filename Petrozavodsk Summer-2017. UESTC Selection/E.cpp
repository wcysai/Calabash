#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 100;
const int N = 13e6 + 10;
int NODE[maxn][11];
char s[maxn];
int n;
int q;
int ans[maxn];
vector<tuple<int,int,int,int> > query1[maxn];
vector<tuple<int,int,int,int,int,int> > query2;
typedef tuple<int,int,int,int> QUERY1;
typedef tuple<int,int,int,int,int,int> QUERY2;

struct Trie{
    int nxt[N][5];
    int CNT[N];
    int root = 1;
    int cnt = 1;

    void clear(){
        memset(CNT,0,sizeof CNT);
    }
    void dfs(int now,int dep){

        if (dep == 11)return;
        for (int i=0;i<5;i++){
            nxt[now][i] = ++cnt;
            dfs(nxt[now][i],dep+1);
        }
    }
    Trie(){
        dfs(root,1);
        cerr<<cnt<<endl;
    }
    void add(int i,int len){
        int now = root;
        int delta = len + 1;
        for (int j=0;j<len;j++){
            delta --;
            now = nxt[now][s[i+j]-'a'];
            assert(now);
            CNT[now] += delta;
        }
    }
    int find(char *t){
        int now = root;
        while (*t){
            now = nxt[now][*t - 'a'];
            assert(now);
            t ++;
        }
        return now;
    }
}trie;

int len[maxn][2];
inline void add_query(int id,int R,int sig,int node,int len){
    if (R - 10 + 1 > 0)query1[R - 10 + 1].push_back(make_tuple(id,R - 10 + 1,sig,node));
    if (R > 0){
        query2.push_back(make_tuple(id,max(1,R - 10 + 2),R,sig,node,len));
    }
}
void gao1(){
    for (int i=1;i<=n;i++){
        // %2 == 0
        trie.add(i,len[i][0]);
        // %2 == 1
        trie.add(i,len[i][1]);
        while (!query1[i].empty()){
            int id,r,sig,node;
            tie(id,r,sig,node) = query1[i].back();
            query1[i].pop_back();
            ans[id] += sig * trie.CNT[node];
        }
    }
}
void gao2(){
    for (auto query : query2){
        int id,L,R,sig,node,tlen;
        tie(id,L,R,sig,node,tlen) = query;
        //cerr<<"query: "<<id<<" "<<sig<<" "<<L<<" "<<R<<endl;
        for (int i = L;i <= R;i++){
            if (node == NODE[i][tlen]){
                int temp_ans = max(0, min(R,i + len[i][0] - 1) - (i + tlen - 1) + 1) + max(0,min(R,i + len[i][1] - 1) - (i + tlen - 1) + 1);
          //      cerr<<id<<" "<<i<<" "<<sig<<" "<<temp_ans<<endl;
                ans[id] += sig * temp_ans;
            }
        }
    }
}
void solve(){
    s[0] = '#';
    trie.clear();
    scanf("%s",s+1);
    n = strlen(s+1);
    //q = read();
    scanf("%d",&q);
    query2.clear();
    for (int i=1;i<=n;i++){
        len[i][0] = 0;
        len[i][1] = 1;
        NODE[i][0] = 1;
        for (int j=1;j<=10;j++)NODE[i][j] = 0;
        for (int j=1;j<=min(10,n - i + 1);j++)NODE[i][j] = trie.nxt[NODE[i][j-1]][s[i+j -1] - 'a'];
        while (len[i][0] + 1 < i && s[i + len[i][0]] == s[i-1-len[i][0]])len[i][0] ++;
        while (len[i][1] + 1 <= i && s[i + len[i][1]] == s[i-len[i][1]])len[i][1] ++;
        assert(len[i][0] <= 10);
        assert(len[i][1] <= 10);
    }
    for (int i=1;i<=q;i++){
        ans[i] = 0;
        //int L = read(),R = read();
        int L,R;
        static char t[50];
        scanf("%d%d%s",&L,&R,t+1);
        //scanf("%s",t+1);
        int node = trie.find(t+1);
        int tlen = strlen(t + 1);
        //cerr<<L<<"   "<<R<<"   "<<t+1<<endl;
        add_query(i,L-1,-1,node,tlen);
        add_query(i,R,1,node,tlen);
        for (int j = max(1,L - 20); j <= min(n,L + 20); j ++){
            int min_len0 = max(tlen,max(L - j + 1, j-1 - L + 2));
            int min_len1 = max(tlen,max(L - j + 1,j - L + 2));
            if (NODE[j][tlen] == node){
                int temp_ans = max(0,len[j][0] - min_len0 + 1) + max(0,len[j][1] - min_len1 + 1);
                ans[i] -= temp_ans;
            }
        }
    }
    gao1();
    gao2();
    for (int i=1;i<=q;i++)printf("%d\n",ans[i]);
}
int main(){
//    int T = read();
    int T;
    scanf("%d",&T);
    while (T--){
        solve();
    }
    return 0;
}
