#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 100;
int n,k;
int solve(){
    map<int,int> num;
    long long days = 0;
    int ans = 0;
    for (int i=0;i<n;i++){
        int temp;
        scanf("%d",&temp);
        num[temp] ++;
    }
    ans = num.rbegin()->first - num.begin()->first;
    while (days < k && ans > 1){
        int cnt = min(num.rbegin()->second,num.begin()->second);
        days += cnt;
        int big = num.rbegin()->first;
        int small = num.begin()->first;
        num[big] -= cnt;
        num[big-1] += cnt;
        num[small] -= cnt;
        num[small+1] += cnt;
        while (num.begin()->second == 0)num.erase(num.begin()->first);
        while (num.rbegin()->second == 0)num.erase(num.rbegin()->first);
        if (days > k){
            cout<<ans<<endl;
            return 0;
        }
        ans = num.rbegin()->first - num.begin()->first;
        if (days == k){
            cout<<ans<<endl;
            return 0;
        }
    }
    cout<<num.rbegin()->first - num.begin()->first<<endl;
    return 0;
}
int main(){

    while (scanf("%d%d",&n,&k)!= EOF){
        solve();
    }
   return 0;
}
