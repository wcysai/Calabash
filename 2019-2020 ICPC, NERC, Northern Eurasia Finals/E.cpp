#include <bits/stdc++.h>
using namespace std;
const int maxn  = 105;
vector<int> ans;
int n,m;
int a[maxn][maxn];
bool used[maxn];
int main(){
    cin>>n>>m;
    for (int i=1;i<=m;i++){
        for (int j=1;j<=n;j++){
            cin>>a[i][j];
        }
    }
    for (int other = 1;other <n;other ++){
        vector<pair<int,int> > temp(0);
        vector<int> tmp_ans(0);
        int sum = 0;
        for (int i=1;i<=m;i++){
            int delta = a[i][other] - a[i][n];
            if (delta >=0){
                sum += delta;
                tmp_ans.push_back(i);
            }else{
                temp.push_back(make_pair(delta,i));
            }
        }
        sort(temp.begin(),temp.end());
        reverse(temp.begin(),temp.end());
        for (auto pr : temp){
            if (pr.first + sum >=0){
                sum += pr.first;
                tmp_ans.push_back(pr.second);
            }else break;
        }
        if (tmp_ans.size() > ans.size())ans = tmp_ans;
    }
    for (int x : ans){
        used[x] = true;
    }
    cout<<m - ans.size()<<endl;
    for (int i = 1;i <=m;i++){
        if (!used[i])cout<<i<<" ";
    }
    cout<<endl;
    return 0;
}
