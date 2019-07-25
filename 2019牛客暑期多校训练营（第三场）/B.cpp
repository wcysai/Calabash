#include <bits/stdc++.h>
#define left jlkdasfjklajdf
using namespace std;
const int maxn = 1e5 + 100;
char s[maxn];
map<int,int> left;
int n;
int main(){
    cin>>n;
    cin>>s+1;
    int cnt0 = 0,cnt1 = 0;
    for (int i=1;i<=n;i++){
        if (s[i] == '0'){
            cnt0 ++;
        }else{
            cnt1 ++;
        }
    }
    int ans2 = 2 * min(cnt0,cnt1);
    int sum = 0;
    left[sum] = 0;
    int ans1 = 0;
    for (int i=1;i<=n;i++){
        if (s[i] == '0'){
            sum --;
        }else{
            sum ++;
        }
        if (left.find(sum) != left.end()){
            int pre = left[sum];
            ans1 = max(ans1,i - pre);
        }else{
            left[sum] = i;
        }
         
    }
    cout<<ans1<<" "<<ans2<<endl;
    return 0;
}
