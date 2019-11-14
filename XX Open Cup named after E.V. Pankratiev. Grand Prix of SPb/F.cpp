#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 100;
typedef long long ll, LL;
vector<tuple<int,int,int> > E[maxn];
typedef map<int,ll> MAP;

int n,t;

MAP dfs(int u, int dd, int limit) {
    vector<MAP> sons; sons.push_back(MAP{{dd, limit}});

    LL totw = limit;
    for (auto e : E[u]) {
        int v,d,w; tie(v,d,w) = e;
        totw += w;
        sons.push_back(dfs(v, d, w));
    }

    auto ret = move(*max_element(sons.begin(),sons.end(),[](const MAP& x,const MAP& y) {
        return x.size() < y.size();
    }));

    for (auto& s : sons) for (auto pr : s) ret[pr.first] += pr.second;

    LL del = totw - limit;
    while (del > 0) {
        auto it = ret.begin();
        if (it->second <= del) {
            del -= it->second;
            ret.erase(it);
        } else {
            it->second -= del;
            del = 0;
        }
    }
    return move(ret);
}

int main(){
    cin>>n>>t;
    for (int i=1;i<=n;i++){
        int d,p,w;
        cin>>d>>p>>w;
        E[p].push_back(make_tuple(i,d,w));
    }
    LL ans = 0;
    for (auto pr : dfs(0,0,t)) ans += 1ll * pr.first * pr.second;
    cout << ans << endl;
    return 0;
}
