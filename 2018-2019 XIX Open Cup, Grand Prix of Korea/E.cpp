#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5+100;
int n,m;
set<int> E[maxn];
set<int> todo;
bool used[maxn];
int main(){
    scanf("%d%d",&n,&m);
    for (int i=0;i<m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        E[u].insert(v);
        E[v].insert(u);
    }
    for (int i=1;i<=n;i++){
        if (E[i].size() == 2){
            todo.insert(i);
        }
    }
    while (todo.size()){
        int x = *todo.begin();
                todo.erase(x);
        if (E[x].size() != 2)continue;
       // cout<<x<<endl;

        used[x] = 1;
        int y,z;
        auto it = E[x].begin();
        y = *it;
        it ++;
        z = *it;
        //cout<<x<<" "<<y<<" "<<z<<endl;
        E[y].erase(x);
        E[z].erase(x);
        E[x].erase(y);
        E[x].erase(z);
        // new edge : y - z
        if (E[y].count(z)){
        }else{
            E[y].insert(z);
            E[z].insert(y);
        }
        if (todo.count(y) == 0 && E[y].size() == 2){
            todo.insert(y);
        }
        if (todo.count(z) == 0 && E[z].size() == 2){
            todo.insert(z);
        }
    }
    int cnt = 0;
    for (int i=1;i<=n;i++){
        cnt += E[i].size();
    }
    if (cnt == 2){
        puts("Yes");
    }else{
        puts("No");
    }
    return 0;
}
