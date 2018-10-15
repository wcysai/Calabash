//
// Created by calabash_boy on 18-9-14.
//
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1000;
const int maxm = 200*500;
const int INF = 0x3f3f3f3f;
int from[maxm*2],first[maxm],nxt[maxm*2],des[maxm*2],c[maxm*2],tot;
int dep[maxn];int m,n,ss,tt;
map<string,int> id;
vector<int> versions[maxn];
map<int,int> con_cnt[maxn];
vector<pair<int,int> > conflict[maxn];
int conf[maxn][maxn];
int ans[maxn];
void init(){
    memset(first,-1,sizeof first);
    tot =-1;
}
inline void addEdge(int u,int v,int w){
    tot++;
    des[tot] = v;c[tot] =w;
    from[tot] = u;
    nxt[tot] = first[u];first[u] = tot;
}
bool bfs(){
    memset(dep,-1,sizeof dep);
    dep[ss] =0;
    queue<int> Q;Q.push(ss);
    while (!Q.empty()){
        int q = Q.front();Q.pop();
        for (int t = first[q];t!=-1;t= nxt[t]){
            int v = des[t],cx = c[t];
            if (dep[v]==-1&&cx){
                dep[v] = dep[q]+1;
                Q.push(v);
            }
        }
    }
    return dep[tt]!=-1;
}
int dfs(int node,int now){
    if (node==tt)return now;
    int res =0;
    for (int t = first[node];t!=-1&&res<now;t=nxt[t]){
        int v = des[t],cx = c[t];
        if (dep[v]==dep[node]+1&&cx){
            int x = min(cx,now-res);
            x = dfs(v,x);
            res +=x;
            c[t] -= x;c[t^1]+=x;
        }
    }
    if (!res) dep[node] = -2;
    return res;
}
void solve(){
    int res =0,del = 0;
    ss = n+m+1;tt = n+m+2;
    int chk =0;
    for (int i=1;i<=n;i++){
        if (ans[i])continue;
        chk++;
        for (int j=1;j<=m;j++){
            if (conf[i][j]){
                int u = i;
                int v = n+j;
                addEdge(u,v,1);
                addEdge(v,u,0);
            }
        }
        addEdge(ss,i,1);
        addEdge(i,ss,0);
    }
    for (int j=1;j<=m;j++){
        addEdge(n+j,tt,1);
        addEdge(tt,n+j,0);
    }
    while (bfs()){
        while (del = dfs(ss,INF)){res += del;}
    }
   // cout<<res<<"   "<<chk<<endl;
    if (res < chk) {
        cout<<"No\n";
        return;
    }
    cout<<"Yes\n";
    for (int i=0;i<=tot;i++){
        if (c[i] == 0 && from[i] <=n && des[i] >n && des[i] <= n+m){
            int u = from[i];
            int v = des[i] - n;
            ans[u] = conf[u][v];
        }
    }
    for (int i=1;i<=n;i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
}

int main(){
    cin>>n;
    for (int i=1;i<=n;i++){
        int cnt;
        string name;
        cin>>name>>cnt;
        id[name] = i;
        versions[i].resize(cnt);
        for (int j=1;j<=cnt;j++){
            int version;
            cin>>version;
            versions[i][j-1]=version;
        }
    }
    cin>>m;
    for (int i=1;i<=m;i++){
        int cnt;
        cin>>cnt;
        string name;int version;
        while (cnt--){
            cin>>name>>version;
            con_cnt[id[name]][version] ++;
            conflict[i].push_back({id[name],version});
            conf[id[name]][i] = version;
        }

    }
    for (int i=1;i<=n;i++){
        for (int j=0;j<versions[i].size();j++){
            int v =  versions[i][j];
            if(con_cnt[i][v] == 0){
                ans[i] = v;
                break;
            }
        }
    }
    init();
    solve();
    return 0;
}
/*
 3
 vim 3 1 2 3
 nano 2 5 8
 python 2 2 3
 2
 2 vim 3 nano 8
 3 vim 1 nano 5 vim 2




 2
 firefox 1 38
 chrome 1 46
 1
 2 firefox 38 chrome 46
 */
