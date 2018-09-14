#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+100;
int first[maxn],nxt[maxn*2],des[maxn*2],tot;
int n;
int dis[maxn];
int max_dis[maxn];
int len[maxn],len_cnt;
int wson[maxn],top[maxn];
int root=1,maxLen =0;
vector<int> ans;
inline void addEdge(int x,int y){
    tot++;
    des[tot] =y;
    nxt[tot] = first[x];
    first[x] = tot;
}
void dfs0(int node,int father){
    for (int t = first[node];t;t=nxt[t]){
        int v = des[t];
        if (v==father) continue;
        dis[v] = dis[node] +1;
        dfs0(v,node);
    }
}
void dfs1(int node,int father){
    max_dis[node] =1;
    dis[node] = dis[father]+1;
    for (int t = first[node];t;t=nxt[t]){
        int v = des[t];
        if (v==father)continue;
        dfs1(v,node);
        max_dis[node] = max(max_dis[node],max_dis[v]+1);
        if (max_dis[v]>max_dis[wson[node]]){
            wson[node] = v;
        }
    }
}
void dfs2(int node,int father,int chain){
    top[node] = chain;
    len[chain]++;
    if (wson[node]){
        dfs2(wson[node],node,chain);
    }
    for (int t = first[node];t;t=nxt[t]){
        int v = des[t];
        if (v==father||v==wson[node])continue;
        dfs2(v,node,v);
    }
}
bool cmp(int x,int y){
    return x>y;
}
int main(){
//    freopen("input.in","r",stdin);
    scanf("%d",&n);
    for (int i=0;i<n-1;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    dfs0(1,0);
    for (int i=1;i<=n;i++){
        if (dis[i]>maxLen){
            maxLen = dis[i];
            root = i;
        }
    }
    memset(dis,0,sizeof dis);
    dfs1(root,0);
    dfs2(root,0,root);
    for (int i=1;i<=n;i++){
//        cout<<"wson["<<i<<"]="<<wson[i]<<"dis["<<i<<"]="<<dis[i]<<endl;
        if (len[i]){
            ans.push_back(len[i]);
        }
    }
    sort(ans.begin(),ans.end(),cmp);
    int Sum = 0;
    printf("1 ");
    for (int i=0;i<ans.size();i++){
        Sum+=ans[i];
        printf("%d ",Sum);
    }
    for (int i=0;i<n-ans.size()-1;i++){
        printf("%d ",n);
    }
    return 0;
}
