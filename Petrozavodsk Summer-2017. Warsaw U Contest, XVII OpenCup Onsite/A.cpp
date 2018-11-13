#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ULL;
const int maxn = 5e3+10;
const int maxt = 202;
const int maxm = 1e6+200;
//mt19937_64 roundgod(time(0));
int fa[maxt][maxn];
int sz[maxt][maxn];
vector<int> vec[maxt][maxn];
ULL h[maxn];
int d,n,m;
ULL weight[maxt][maxn];
unordered_map<ULL,int> cnt;
unordered_map<ULL,int> temp;
int find(int x,int W){
    return fa[W][x] == x?x:fa[W][x] = find(fa[W][x],W);
}
int main(){
    scanf("%d%d%d",&d,&n,&m);
    for (int i=1;i<=d;i++){
        for (int j=1;j<=n;j++){
            weight[i][j] = 1ul*rand()*rand()*rand();
        }
    }
    for (int i=1;i<=d;i++){
        for (int j=1;j<=n;j++){
            fa[i][j] = j;
            sz[i][j] = 1;
            vec[i][j].push_back(j);
            h[j] += weight[i][j];
        }
    }
    for (int i=1;i<=n;i++){
        cnt[h[i]]++;
    }
    int ans =n;
    while (m--){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        int fu = find(u,w);
        int fv = find(v,w);
        if (fu == fv){
            printf("%d\n",ans);
            continue;
        }
        if (sz[fu]<sz[fv]){
            swap(u,v);
            swap(fu,fv);
        }
        temp.clear();
        for (int vv : vec[w][fv]){
            cnt[h[vv]]--;
            if (cnt[h[vv]] == 0)cnt.erase(h[vv]);
            h[vv] -= weight[w][fv];
            h[vv] += weight[w][fu];
            temp[h[vv]]++;
            fa[w][vv] = fu;
            vec[w][fu].push_back(vv);
        }
        vec[w][fv].clear();
        vec[w][fv].resize(0);
        vec[w][fv].shrink_to_fit();
        for (auto pr : temp){
            if (cnt.find(pr.first) != cnt.end())
            ans += 2ll * pr.second * cnt[pr.first];
        }
        for (auto pr : temp){
            cnt[pr.first] += pr.second;
        }
        printf("%d\n",ans);
    }
    return 0;
}
