#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+100;
int nxt[maxn][26];
char s[maxn];
int n;
map<int,int> ans;
void work(int st){
    int now = 0;
    vector<pair<int,int> >  Nxt(0);
    for (int i=0;i<26;i++){
        if (nxt[st][i] != -1 && i != s[st] - 'a'){
            Nxt.push_back({nxt[st][i],i});
        }
    }
    Nxt.push_back({st,s[st] - 'a'});
    sort(Nxt.begin(),Nxt.end());
    for (int i=0;i<Nxt.size();i++){
        auto pr  = Nxt[i];
        int ch = pr.second;
        int pos = pr.first;
        now |= (1<<ch);
        int r = n;
        if (i+1 != Nxt.size()){
            r = Nxt[i+1].first-1;
        }
        int len = r - st +1;
        ans[now] = max(ans[now],len);
    }
    
}
void solve(){
    memset(nxt[n],-1,sizeof nxt[n]);
    for (int i=n-1;i>=1;i--){
        memcpy(nxt[i],nxt[i+1],sizeof nxt[i]);
        nxt[i][s[i+1]-'a'] = i+1;
    }
    for (int i=1;i<=n;i++){
        work(i);
    }
    long long Ans =0;
    for (auto pr : ans){
        Ans += __builtin_popcount(pr.first) * pr.second;
    }
    printf("%d %lld\n",(int)ans.size(),Ans);
}
int main(){
    int T;
    for (scanf("%d",&T);T;T--){
        ans.clear();
        scanf("%s",s+1);
        n = strlen(s+1);
        solve();
    }
    return 0;
}
