//
// Created by calabash_boy on 18-5-9.
//
#include<bits/stdc++.h>
using namespace std;
const int maxn = 20;
int T,G;
map<string,int> id;
int idcnt;
string a[6][maxn];
int ida[6][maxn];
bool used[maxn*6];
string b;
int idb;
int Cas=0;
bool check(int y){
    int x = G-y;
    memset(used,0,sizeof used);
    int nowrk=0;
    int nowa=0;
    while (x){
        if (!used[ida[nowa][nowrk]]){
            used[ida[nowa][nowrk]]=1;
            x--;
        }
        nowa++;
        if (nowa==5){
            nowa=0;
            nowrk++;
        }
    }
    if (used[idb])return true;
    if (y==0)return used[idb];
    for (int i=0;i<20;i++){
        if (!used[ida[5][i]]){
            used[ida[5][i]]=true;
            y--;
            if (y==0)break;
        }
    }
    return used[idb];
}
void solve(){
    cout<<"Case #"<<++Cas<<": ";
    idcnt=0;
    id.clear();
    cin>>G>>b;
    for (int i=0;i<6;i++){
        for (int j=0;j<20;j++){
            cin>>a[i][j];
            if (id[a[i][j]]==0){
                id[a[i][j]] = ++idcnt;
            }
            ida[i][j] = id[a[i][j]];
        }
    }
    idb = id[b];
    if (idb==0){
        cout<<0<<"\n";
        return;
    }
    for (int i=0;i<=G;i++){
        if (check(i))continue;
        else{
            cout<<i<<"\n";
            return;
        }
    }
    cout<<"ADVANCED!\n";
}
int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin>>T;
    while (T--){
        solve();
    }
    return 0;
}
