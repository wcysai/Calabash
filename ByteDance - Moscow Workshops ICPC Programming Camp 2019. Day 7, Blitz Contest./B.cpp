//
// Created by bytedance on 19-2-23.
//

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 55;
const ll root = (1ll << maxn) - 1;
map<ll,int> cnt;
vector<ll > patha,pathb;
void work(ll root,int dep,ll tar,ll temp,vector<ll> & path){

   // cout<<root<<" "<<tar<<endl;

    cnt[root] ++;
    path.push_back(root);
    if (temp == root)return;
    if (dep < 0)return;
    ll sz = (1ll<< dep);
    if (tar <root){
        work(root - sz , dep -1,tar,temp,path);
    }else{
        work(root+ sz,dep-1,tar ,temp,path);
    }
}
int main(){
    ll a,b;
    cin>>a>>b;
    work(root,maxn-1,a,a,patha);
    //cout<<endl;
    work(root,maxn-1,b,b,pathb);
    ll ans = 0;
    for (auto pr : cnt){
        if (pr.second == 1){
            ans += pr.first;
        }
    }

    patha.push_back(-1);
    pathb.push_back(-2);
    int sz = min(patha.size(),pathb.size());
    for (int i=0;i<sz;i++){
        if (patha[i] == pathb[i])continue;
        else{
            ans += patha[i-1];
            break;
        }
    }
    cout<<ans<<endl;
    return 0;
}
/*
 *
/home/bytedance/workspace/CLionProject/cmake-build-debug/CLionProject
1 5
36028797018963967
18014398509481983
9007199254740991
4503599627370495
2251799813685247
1125899906842623
562949953421311
281474976710655
140737488355327
70368744177663
35184372088831
17592186044415
8796093022207
4398046511103
2199023255551
1099511627775
549755813887
274877906943
137438953471
68719476735
34359738367
17179869183
8589934591
4294967295
2147483647
1073741823
536870911
268435455
134217727
67108863
33554431
16777215
8388607
4194303
2097151
1048575
524287
262143
131071
65535
32767
16383
8191
4095
2047
1023
511
255
127
63
31
15
7
3
1

36028797018963967
18014398509481983
9007199254740991
4503599627370495
2251799813685247
1125899906842623
562949953421311
281474976710655
140737488355327
70368744177663
35184372088831
17592186044415
8796093022207
4398046511103
2199023255551
1099511627775
549755813887
274877906943
137438953471
68719476735
34359738367
17179869183
8589934591
4294967295
2147483647
1073741823
536870911
268435455
134217727
67108863
33554431
16777215
8388607
4194303
2097151
1048575
524287
262143
131071
65535
32767
16383
8191
4095
2047
1023
511
255
127
63
31
15
7
11
9
10
-36028797018963944

Process finished with exit code 0

 */
