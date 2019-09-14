#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 100;
vector<int> E[maxn];
int fa[maxn];
int find(int x){
    return fa[x] == x?x : fa[x] = find(fa[x]);
}
int n,m,k;
bool monster[maxn];
vector<int> EE[maxn];
long long sum[maxn];
vector<pair<int,int> > edges;
void solve(){
    scanf("%d%d%d",&n,&m,&k);
    memset(sum,0,sizeof sum);
    memset(monster,0,sizeof monster);
    edges.clear();
    for (int i=1;i<=n;i++){
        E[i].clear();
        EE[i].clear();
        fa[i] = i;
    }
    for (int i=1;i<=m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        edges.push_back(make_pair(u,v));
    }
    for (int i=1;i<=k;i++){
        int x;
        scanf("%d",&x);
        monster[x] = 1;
    }
    for (auto e : edges){
        int u,v;
        tie(u,v) = e;
        if (monster[u] || monster[v])continue;
        int fu = find(u);
        int fv = find(v);
        if (fu == fv)continue;
        fa[fu] = fv;
    }
    for (int i=1;i<=n;i++){
        if (monster[i])continue;
        sum[find(i)] ++;
    }

    for (auto e : edges){
        int u,v;
        tie(u,v) = e;
        u = find(u);
        v = find(v);
        if (u == v)continue;
        EE[u].push_back(v);
        EE[v].push_back(u);
    }
    double ans = sum[find(1)];
    for (int i=1;i<=n;i++){
        if (i == find(i) && monster[i]){
            bool legal = false;
            for (int v : EE[i]){
                if (v == find(1)){
                    legal = true;
                    break;
                }
            }
            if (!legal)continue;
            double temp_ans = sum[find(1)];
            map<int,int> num;
            for (int v : EE[i]){
                num[v] ++;
            }
            double delta_ans = 0;
            for (auto pr : num){
                int v,cnt;
                tie(v,cnt) = pr;
                if (v == find(1))continue;
                delta_ans += 1.0 * cnt / EE[i].size() * sum[v];
            }
            temp_ans += delta_ans;
            ans = max(ans,temp_ans);
        }
    }
    printf("%.9lf\n",ans);
}
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        solve();
    }
    return 0;
}
