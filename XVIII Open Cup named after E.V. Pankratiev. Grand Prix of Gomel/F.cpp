#include <bits/stdc++.h>
using namespace std;
const int maxn = 200;
vector<vector<int> > res[maxn];
int main(){
    int p;
    cin>>p;
    if (p==2){
        cout<<"4 5"<<endl;
        cout<<"2 1 2"<<endl;
        cout<<"1 2"<<endl;
        cout<<"3 5 1 3"<<endl;
        cout<<"2 2 3"<<endl;
        return 0;
    }
    int m =120;
    for (int i=1;i<=m-1;i++){
        res[i].resize(m);
        for (int j=0;j<m;j++){
            res[i][j].push_back(i);
        }
    }
    res[m].resize(m-1);
    for (int i=0;i<m-1;i++){
        res[m][i].push_back(m);
    }
    for (int i=m;i>=2;i--){
        for (int j=0;j<i-2;j++){
            res[i][j].push_back(j+1);
        }
    }
    int n = m*(m-1) + m-1;
    cout<<n<<" "<<m<<endl;
    for (int i=1;i<=m;i++){
        for (int j=0;j<res[i].size();j++){
            cout<<res[i][j].size()<<" ";
           // reverse(res[i][j].begin(),res[i][j].end())
            for (int k = 0;k < res[i][j].size();k++){
                cout<<res[i][j][k]<<" ";
            }
            cout<<endl;
        }
    }
    return 0;
}
