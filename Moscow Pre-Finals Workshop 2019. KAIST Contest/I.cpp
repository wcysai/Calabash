#include <bits/stdc++.h>
using namespace std;
const int maxn = 250000 + 10;
int a[maxn];
int n;
int st[maxn][20];
int dep[maxn];
int ans[maxn];
int ans2[maxn];
int get_lca(int x,int y){
    if (dep[x] < dep[y])swap(x,y);
    for (int i=19;i>=0;i--){
        if (dep[st[x][i]] >= dep[y])x = st[x][i];
    }
    if (x == y)return x;
    for (int i=19;i>=0;i--){
        if (st[x][i] != st[y][i]){
            x = st[x][i];
            y = st[y][i];
        }
    }
    assert(st[x][0] == st[y][0]);
    return st[x][0];
}
vector<int> lis[maxn];
int LIS[maxn];
int anss[maxn];
void solve(){
    memset(st,0,sizeof st);
    memset(dep,0,sizeof dep);
    for (int i=0;i<=n;i++){
        lis[i].clear();
    }
    memset(anss,0,sizeof anss);
    lis[0].push_back(0);
    memset(LIS,0,sizeof LIS);
    int len = 0;
    anss[0] = -1;
    for (int i=1;i<=n;i++){
        int idx = -1;
        if (a[i] > LIS[len]){
            len ++;
            lis[len].push_back(a[i]);
            LIS[len] = a[i];
            idx = len;
        }else{
            idx = lower_bound(LIS + 1,LIS + 1 + len,a[i]) - LIS;
            LIS[idx] = a[i];
            lis[idx].push_back(a[i]);
        }
        int pre = idx - 1;
        int idx2 = lower_bound(lis[idx-1].begin(), lis[idx-1].end(),a[i], [](int x,int y){
            return x > y;
        }) - lis[idx-1].begin();
        int max_val = lis[idx-1][idx2];
        int min_val = lis[idx-1].back();
        int lca_ = get_lca(max_val,min_val);
        anss[a[i]] = anss[lca_] + 1;
        st[a[i]][0] = lca_;
        dep[a[i]] = dep[lca_] + 1;
        for (int step=1;step<20;step++){
            st[a[i]][step] = st[st[a[i]][step-1]][step-1];
        }

    }
}
int main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        scanf("%d",a+i);
    }
    solve();
    for (int i=1;i<=n;i++){
        ans[i] = anss[a[i]];
    }
    reverse(a + 1,a + 1 + n);
    for (int i=1;i<=n;i++)a[i] = 1 + n - a[i];
    solve();
    for (int i=1;i<=n;i++){
        int idx = n + 1 - i;
        ans[idx] += anss[a[i]];
    }

    for (int i=1;i<=n;i++){
        printf("%d%c",ans[i] + ans2[i],i == n?'\n':' ');
    }
    return 0;
}
