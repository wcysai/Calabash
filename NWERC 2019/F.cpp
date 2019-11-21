#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 100;
int fa[maxn];
int find(int x){
    return fa[x] == x?x : fa[x] = find(fa[x]);
}

map<int,vector<int> > points;
vector<tuple<int,int,int> > ans;
void merge(int x,int y,int d){
    int fx = find(x);
    int fy = find(y);
    if (fx == fy)return;
    ans.push_back(make_tuple(x,y,d));
    fa[fx] = fy;
}
int main(){
    int n;
    cin>>n;
    for (int i=1;i<=n;i++)fa[i] = i;
    for (int i=1;i<=n;i++){
        int m;
        cin>>m;
        while (m--){
            int d;
            cin>>d;
            points[d].push_back(i);
        }
    }
    for (auto pr : points){
        int d = pr.first;
        for (int i=1;i<pr.second.size();i++){
            merge(pr.second[i-1],pr.second[i],d);
        }
    }
    if (ans.size() == n - 1){
        for (auto tp : ans){
            int x,y,d;
            tie(x,y,d) = tp;
            cout<<x<<" "<<y<<" "<<d<<endl;
        }
    }else{
        cout<<"impossible"<<endl;
    }
    return 0;
}
