#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 100;
const int N = maxn * 20;
int ans[maxn];
int p[maxn];
int c[maxn];
int n;
vector<pair<int,int>> TE[maxn];
struct Trie{
    int nxt[N][3];
    int fail[N];
    int Fail[N][3];
    int dep[N];
    int root = 0;
    int cnt = 0;
    int id[N];
    int insert(int pre,int ch){
        if (!nxt[pre][ch]){
            nxt[pre][ch] = ++cnt;
            dep[cnt] = dep[pre] + 1;
        }
        return nxt[pre][ch];
    }
    void put(int node,int color){
        id[node] = color;
    }
    int first_[N],nxt_[N],des_[N];
    int tot_;
    void add_edge(int x,int y){
        tot_ ++;
        des_[tot_] = y;
        nxt_[tot_] = first_[x];
        first_[x] = tot_;
    }
    //vector<int> E[N];
    void main(){
        queue<int> Q;
        Q.push(0);
        Fail[0][0] = nxt[0][0];
        Fail[0][1] = nxt[0][1];
        Fail[0][2] = nxt[0][2];
/*        for (int i=0;i<=cnt;i++){
            for (int ch = 0;ch < 2;ch ++){
                cerr<<"nxt["<<i<<"]["<<ch<<"]="<<nxt[i][ch]<<endl;
           }
        }
        */
        while (!Q.empty()){
            int head = Q.front();Q.pop();
            for (int ch = 0;ch < 3;ch ++){
                if (!nxt[head][ch])continue;
                int v = nxt[head][ch];
                if (head == 0){
                    fail[v] = 0;
                }else{
                    fail[v] = Fail[fail[head]][ch];
                }
                for (int cc = 0;cc < 3;cc ++){
                    Fail[v][cc] = Fail[fail[v]][cc];
                }
                for (int cc = 0;cc < 3;cc ++){
                    if (nxt[v][cc])Fail[v][cc] = nxt[v][cc];
                }
                Q.push(v);
            }
        }
        /*
        for (int i=1;i<=cnt;i++){
            cerr<<"fail["<<i<<"]="<<fail[i]<<endl;
            cerr<<"id["<<i<<"]="<<id[i]<<endl;
            cerr<<"Fail["<<i<<"][0]="<<Fail[i][0]<<endl;
            cerr<<"Fail["<<i<<"][1]="<<Fail[i][1]<<endl;
            E[fail[i]].push_back(i);
        }
        */
        //for (int i=1;i<=cnt;i++)E[fail[i]].push_back(i);
        for (int i=1;i<=cnt;i++)add_edge(fail[i],i);
        dfs(0,0,0);
    }
    void dfs(int u,int latest,int length){
        if (id[u]){
            int len = 2;
            int val = c[id[u]];
            while (va
