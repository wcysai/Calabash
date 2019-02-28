#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+100;
vector<int> nums[maxn];
int n;
int a[maxn];
struct BIT{
    int sum[maxn];
    int lowbit(int x){
        return x & (-x);
    }
    void add(int x){
        while (x<maxn){
            sum[x] ++;
            x += lowbit(x);
        }
    }
    int query(int x){
        int res = 0;
        while (x){
            res += sum[x];
            x -= lowbit(x);
        }
        return res;
    }
    int query(int l,int r){
        return query(r) - query(l-1);
    }
}bit;
int work(int x){
    int l_ans = x-1 - bit.query(1,x-1);
    int r_ans = n-x - bit.query(x+1,n);
    return min(l_ans,r_ans);
}
bool used[maxn];
int main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        scanf("%d",a+i);
        nums[a[i]].push_back(i);
    }
    long long ans = 0;
    for (int i=1;i<=1e5;i++){
        vector<int> ord(0);
        vector<int> rord(0);
        for (int x : nums[i]){
            ord.push_back(x);
        }
        rord = ord;
        reverse(rord.begin(),rord.end());
        int idx = 0,ridx = 0;
        while (idx < ord.size() && ridx < rord.size() ){
            while (idx < ord.size() && used[ord[idx]])idx ++;
            while (ridx < rord.size() && used[rord[ridx]]) ridx ++;
            if (idx >= ord.size()) break;
            int x = ord[idx];
            int y = rord[ridx];
            int ans_x = work(x);
            int ans_y = work(y);
            if (ans_x<ans_y){
                ans += ans_x;
                used[x] = 1;
                bit.add(x);
            }else{
                ans += ans_y;
                used[y] = 1;
                bit.add(y);
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
        

