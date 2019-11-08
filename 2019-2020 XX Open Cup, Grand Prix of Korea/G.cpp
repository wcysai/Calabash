#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 100;
int n,m,s,t;
bool vis[maxn];
bool used[maxn];
vector<int> ans;
vector<pair<int,int> > E[maxn];
vector<pair<int,int> > RE[maxn];
void dfs(int u){
    vis[u] = 1;
    for (auto e : RE[u]){
        int v,c;
        tie(v,c) = e;
        if (vis[v])continue;
        dfs(v);
    }
}
int main(){
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for (int i=0;i<m;i++){
        int u,v,c;
        scanf("%d%d%d",&u,&v,&c);
        E[u].push_back(make_pair(v,c));
        RE[v].push_back(make_pair(u,c));
    }
    dfs(t);
    if (!vis[s]){
        puts("IMPOSSIBLE");
        return 0;
    }
    int now = s;
    while (1){
        if (now == t)break;
        if (used[now]){
            puts("TOO LONG");
            return 0;
        }
        used[now] = 1;
        //ans.push_back(now);
        int min_c = INT_MAX,min_v;
        for (auto e : E[now]){
            int v,c;
            tie(v,c) = e;
            if (vis[v] and c < min_c){
                min_c = c;
                min_v = v;
            }
        }
        if (min_c == INT_MAX)break;
        ans.push_back(min_c);
        now = min_v;
    }
    for (int x : ans){
        printf("%d ",x);
    }
    puts("");
    return 0;
}
