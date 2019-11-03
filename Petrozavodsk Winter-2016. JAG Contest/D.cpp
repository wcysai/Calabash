#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 100;
int n;
char s[maxn];
vector<int> Rs,Ls;
int solve(){
    Rs.clear();Ls.clear();
    for (int i=1;i<=n;i++){
        if (s[i] == '>')Rs.push_back(i);
        else Ls.push_back(i);
    }
    int ans = 1;
    for (int i=1;i<=n;i++){
        if (s[i] == '>'){
            int idxL = lower_bound(Rs.begin(),Rs.end(),i) - Rs.begin();
            int cntL = idxL + 1;
            int idxR = lower_bound(Ls.begin(),Ls.end(),i) - Ls.begin();
            int cntR = Ls.size() - idxR;
            if (cntR >= cntL){
                ans = max(ans,Ls[idxR + cntL - 1]);
            }else{
                ans = max(ans,n - (Rs[idxL -cntR]) + 1);
            }
        }
    }
    return ans;
}
int main(){
    cin>>n;
    cin>>s+1;
    int ans = solve();
    reverse(s + 1,s + 1+ n);
    for (int i=1;i<=n;i++){
        if (s[i] == '<')s[i] = '>';
        else s[i] = '<';
    }
    ans = max(ans,solve());
    cout<<ans<<endl;
    return 0;
}
