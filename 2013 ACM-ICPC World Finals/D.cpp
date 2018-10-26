//
// Created by calabash on 10/24/18.
//
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll prime[] = {2, 3, 5, 7, 11,
                13, 17, 19, 23, 29,
                31, 37, 41, 43, 47,
                53, 59, 61, 67, 71};
const ll ptot = 20;
map<ll,ll> ans;
vector<int> Vec[100];

ll calc(vector<int> vec){
    ll res =1;
    for (int i =0;i<20;i++){
        for (int j=0;j< vec[i];j++){
            if (__builtin_mul_overflow(res,prime[i],&res))return -1;
        }
    }
    //for (int i=0;i<20;i++){
    //    cout<<(int)vec[i]<<" ";
    //}
    //cout<<endl<<(ll)res<<endl;
    return res;
}
void update(vector<int> all,ll num,int sum){
    if (num == 1)return;
    vector<int> vec = Vec[sum];
    for (int x : all){
        for (int i=0;i< 20;i++){
            vec[i] -= Vec[x][i];
        }
    }
    ll n = calc(vec);
    if (n == -1)return ;
    ll N = n;
    if (ans.find(N) == ans.end()){
        ans[N] = num;
    }else{
        ans[N] = min(ans[N],num);
    }
}
ll power(ll x,int y){
    ll res = 1;
    for (int i=1;i<=y;i++){
        if (__builtin_mul_overflow(res,x,&res))return -1;
    }
    return res;
}
void dfs(ll num,int i,vector<int> all,int sum){
    int top = -1;
    if (all.size() == 0){
        top = 62;
    }else{
        top = all[all.size()-1];
    }
    top = min(top,62 - sum);
    update(all,num,sum);
    if (i == 20)return;
    for (int j=1;j<=top;j++){
        ll pow = power(prime[i],j);
        if (pow == -1)break;
        ll x;
        if (__builtin_mul_overflow(pow,num,&x))break;
        vector<int> nxt = all;
        nxt.push_back(j);
        dfs(pow*num,i+1,nxt,sum+j);
    }
}
int main(){
    Vec[0].resize(20);
    for (int i=0;i<20;i++)Vec[0][i] = 0;
    for (int i=1;i<=62;i++){
        Vec[i].resize(20);
        int now = i;
        for (int j=0;j<20;j++){
            while (now % prime[j] == 0){
                now /= prime[j];
                Vec[i][j] ++;
            }
        }
        for (int j=0;j<20;j++){
            Vec[i][j] += Vec[i-1][j];
        }
    }
    dfs(1,0,vector<int>(0),0);
    /*for (auto pr : ans){
        cout<<"ans["<<pr.first<<"]="<<pr.second<<endl;
    }
    */
    //cout<<"tot: "<<ans.size()<<endl;
    ll n;
    while (scanf("%lld",&n)!=EOF){
        printf("%lld %lld\n",n,ans[n]);
    }
    return 0;
}
