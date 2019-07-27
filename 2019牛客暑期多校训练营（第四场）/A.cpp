#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 100;
int n;
vector<int> E[maxn];
bool key[maxn];
int dis[maxn];
int k;
void dfs(int u,int fa){
    dis[u] = dis[fa] + 1;
    for (int v : E[u]){
        if (v == fa)continue;
        dfs(v,u);
    }
}
int main(){
    scanf("%d%d",&n,&k);
    for (int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        E[u].push_back(v);
        E[v].push_back(u);
    }
    int S;
    for (int i=0;i<k;i++){
        int x;
        scanf("%d",&x);
        key[x] = 1;
        S = x;
    }
    for (int i=1;i<=n;i++)dis[i] = INT_MAX;
    dfs(S,0);
    int T = S;
    for (int i=1;i<=n;i++){
        if (key[i] && dis[i] > dis[T]){
            T = i;
        }
    }
    dfs(T,0);
    int A = T;
    for (int i=1;i<=n;i++){
        if (key[i] && dis[i] > dis[A]){
            A = i;
        }
    }
    cout<<(dis[A])/2<<endl;
    return 0;
}
