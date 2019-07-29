//
// Created by calabash on 10/21/18.
//
#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ULL;
using namespace std;
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stderr, "[%s] " fmt "\n", __func__, ##__VA_ARGS__)
#else
#define _debug(...) ((void) 0)
#endif
const int maxn = 1e5+100;
const ll inf_ll = 0x3f3f3f3f3f3f3f3fLL;
const ULL MOD = 951970612352230049ULL;
int first[maxn],nxt[maxn*2],des[maxn*2],flag[maxn*2],len[maxn*2],tot;
int first2[maxn],nxt2[maxn*2],des2[maxn*2],flag2[maxn*2],len2[maxn*2],tot2;
bool in_used[maxn*2];
inline void addEdge(int x,int y,int w,int Flag){
    tot ++;
    des[tot] = y;
    flag[tot] = Flag;
    nxt[tot] = first[x];
    len[tot] = w;
    first[x] = tot;
    tot2 ++;
    des2[tot2] = x;
    nxt2[tot2] = first2[y];
    len2[tot2] = w;
    flag2[tot2] = Flag;
    first2[y] = tot2;
}
int n,m;
const char * happy = "HAPPY";
const char * sad = "SAD";
const char * soso = "SOSO";
int S = 1,T = 2;
ll dis_S[maxn],dis_T[maxn];
bool in[maxn];
void BFS1(int start,int end,ll * dis){
    for (int i=1;i<=n;i++){
        dis[i] = inf_ll;
    }
    memset(in,0,sizeof in);
    dis[start] = 0;
    queue<int> Q;
    Q.push(start);
    in[start] = 1;
    while (!Q.empty()){
        int head = Q.front();Q.pop();
        for (int t = first[head];t;t=nxt[t]){
            int v = des[t];
            int l = len[t];
            if (dis[v] > dis[head] + l){
                dis[v] = dis[head] + l;
                if (!in[v]){
                    in[v] = 1;
                    Q.push(v);
                }
            }
        }
        in[head] = 0;
    }
}
void BFS2(int start,int end,ll * dis){
    for (int i=1;i<=n;i++){
        dis[i] = inf_ll;
    }
    memset(in,0,sizeof in);
    dis[start] = 0;
    queue<int> Q;
    Q.push(start);
    in[start] = 1;
    while (!Q.empty()){
        int head = Q.front();Q.pop();
        for (int t = first2[head];t;t=nxt2[t]){
            int v = des2[t];
            int l = len2[t];
            if (dis[v] > dis[head] + l){
                dis[v] = dis[head] + l;
                if (!in[v]){
                    in[v] = 1;
                    Q.push(v);
                }
            }
        }
        in[head] = 0;
    }
}
vector<int> RE[maxn];
vector<int> E[maxn];
pair<pair<int,int>,int> Edge[maxn];

ULL cnt1[maxn];
ULL cnt2[maxn];
int d1[maxn],d2[maxn];
void dfs1(int u){
    for (int v: E[u]){
        cnt1[v] = (cnt1[u] + cnt1[v])%MOD;
        d1[v] --;
        if (d1[v] == 0)dfs1(v);
    }
}
void dfs2(int u){
    for (int v : RE[u]){
        cnt2[v] = (cnt2[v] + cnt2[u])%MOD;
        d2[v] --;
        if (d2[v] == 0)dfs2(v);
    }
}
void calc_cnt(int start,int end){
    cnt1[start] = 1;
    cnt2[end] =1;
    dfs1(start);
    dfs2(end);
}
bool built[maxn];
void build(int x){
    if (built[x])return;
    built[x] = 1;
    for (int t = first2[x];t;t=nxt2[t]){
        int v = des2[t];
        int l = len2[t];
        if (dis_S[v] == dis_S[x] -l){
            E[v].push_back(x);
            RE[x].push_back(v);
            in_used[flag2[t]] = 1;
            d1[x] ++;
            d2[v]++;
            build(v);
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        Edge[i] = {{u,v},w};
        addEdge(u,v,w,i);
    }
    BFS1(S,T,dis_S);
    BFS2(T,S,dis_T);
    ll min_len = dis_S[T];
    build(T);

    for (int i=1;i<=n;i++){
        _debug("dis_S[%d]=%lld",i,dis_S[i]);
        _debug("dis_T[%d]=%lld",i,dis_T[i]);
    }
    for (int i=1;i<=n;i++){
        for (int v : E[i]){
            _debug("%d -> %d",i,v);
        }
    }
    calc_cnt(S,T);
    for (int i=1;i<=m;i++){
        int u = Edge[i].first.first;
        int v = Edge[i].first.second;
        int l = Edge[i].second;
        if (in_used[i] ){
            __int128_t val = 1;
            val *= cnt1[u];
            val *= cnt2[v];
            val %= MOD;
            if (cnt1[T] == val){
                puts(sad);
            }else{
                puts(soso);
            }
        }else{
            if (dis_S[v] + l + dis_T[u] < min_len){
                puts(happy);
            }else{
                puts(soso);
            }
        }
    }
    return 0;
}
/*
 4 5
 1 3 5
 3 4 6
 4 2 7
 2 1 18
 2 3 12


 7 5
 1 3 2
 1 6 3
 4 2 4
 6 2 5
 7 5 6

 10 14
 1 7 9
 1 8 3
 2 8 4
 2 6 11
 3 7 8
 3 4 4
 3 2 1
 3 2 7
 4 8 4
 5 6 11
 5 8 12
 6 10 6
 7 10 8
 8 3 6
 */
