#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e3+100;
int d[maxn];
int n;
inline void addEdge(int x,int y){
    d[x]++;
    d[y]++;
}
int main(){
    cin>>n;
    for (int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        addEdge(u,v);
    }
    int ans =0;
    for (int i=1;i<=n;i++){
        ans += (d[i]==1);
    }
    cout<<ans<<endl;
    return 0;
}
