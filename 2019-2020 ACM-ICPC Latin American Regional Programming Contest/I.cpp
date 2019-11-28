#include <bits/stdc++.h>
using namespace std;
const int maxn = 2005;
const int mod = 1e9 + 7;
int d[maxn];
bool vis[maxn];
int f[maxn];

int n,l;
vector<int> E[maxn];
int main(){
    cin>>n>>l;
    for (int i=1;i<=l;i++){
        int cnt;
        cin>>cnt;
        while (cnt--){
            int x;
            cin>>x;
            E[i].push_back(x);
            d[x] ++;
        }
    }
    vis[1] = 1;
    f[1] = 1;
    queue<int> Q;
    for (int i=1;i<=n;i++){
        if (d[i] == 0)Q.push(i);
    }
    while (!Q.empty()){
        int head = Q.front();Q.pop();
        for (int v : E[head]){
            vis[v] |= vis[head];
            (f[v] += f[head] )%= mod;
            d[v] --;
            if (d[v] == 0){
                Q.push(v);
            }
        }
    }
    int F = 0, CNT = 0;
    for (int i=l + 1;i <= n;i++){
        (F += f[i]) %= mod;
        CNT += vis[i];
    }
    cout<<F<<" "<<CNT<<endl;
    return 0;
}
