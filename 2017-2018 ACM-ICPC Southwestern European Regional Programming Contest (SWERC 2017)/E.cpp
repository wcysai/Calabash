//
// Created by calabash_boy on 18-5-29.
//
#include<bits/stdc++.h>
#define MP(x,y) make_pair(x,y)
using namespace std;
typedef pair<int,int> PII;
const int maxn = 1e6+100;
const int maxm = 1e4+100;
map<string,int>id;int idcnt;
int B,N;
int dp[maxm];
string a[maxn];
int cost[maxn],value[maxn];
vector<pair<PII,PII> >E[maxm];
void solve(int x){
    if(cost[x]&&value[x])return;
    if(E[x].size()==0)return;
    PII ans = MP(0x3f3f3f3f,0);
    for (auto temp:E[x]){
        solve(temp.first.first);
        solve(temp.first.second);
        PII tt = MP(cost[temp.first.first]+cost[temp.first.second]+temp.second.first,value[temp.first.first]+value[temp.first.second]+temp.second.second);
        if(tt.first<ans.first){
            ans = tt;
        }else if (tt.first==ans.first&&tt.second>ans.second){
            ans = tt;
        }
    }
    cost[x] = ans.first;
    value[x] = ans.second;
}
int main(){
    cin.tie(0);
    ios::sync_with_stdio(0);
    cin>>B>>N;
    for (int i=0;i<N;i++){
        string a1,a2,a3;
        int c,v;
        cin>>a1>>a2>>a3>>c>>v;
        if(!id[a1])id[a1]=++idcnt;
        if(!id[a2])id[a2]=++idcnt;
        if(!id[a3])id[a3]=++idcnt;
        a[i] = a1;
        E[id[a1]].push_back(MP(MP(id[a2],id[a3]),MP(c,v)));
    }
    for (int i=1;i<=idcnt;i++){
        solve(i);
    }
    for (int i=1;i<=idcnt;i++){
        if(cost[i]&&value[i]){
            for (int j=B;j>=cost[i];j--){
                if(dp[j]<dp[j-cost[i]]+value[i]){
                    dp[j] = dp[j-cost[i]]+value[i];
                }
            }
        }
    }
    int ans1 = dp[B];
    int ans2 = B+1;
    for (int i=B;i>=0;i--){
        if(dp[i]==ans1){
            ans2=i;
        }
    }
    cout<<ans1<<"\n"<<ans2<<endl;
    return 0;
}
