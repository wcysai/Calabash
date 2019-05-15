#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
vector<uint64_t> ans;
string s;
int perm[20];
vector<char> chs;
int ID[10000];
int main(){
    cin>>s;
    for (int i=0;i<10;i++){
        perm[i] = i;
    }
    for (char ch : s){
        chs.push_back(ch);
    }
    sort(chs.begin(),chs.end());
    chs.erase(unique(chs.begin(),chs.end()),chs.end());
    assert(chs.size() == 10);
    for (int i=0;i<10;i++){
        ID[chs[i]] = i;
    }
    int tot=0;
    do{
        tot++;
        uint64_t mask = 0;
        for (int i=1;i<s.size();i++){
            int now = s[i];
            int pre = s[i-1];
            now = ID[now];
            pre = ID[pre];
            now = perm[now];
            pre = perm[pre];
            if (now == pre){
                mask = mask * 3 + 1;
            }else if (now > pre){
                mask = mask * 3 + 0; 
            }else{
                mask = mask * 3 + 2;
            }
        }
        ans.push_back(mask);
    }while (next_permutation(perm,perm + 10));
    sort(ans.begin(), ans.end()); 
    for (int i = 0; i < ans.size(); i++) {
        if (i and ans[i] == ans[i-1]) continue;
        if (i < ans.size()- 1 and ans[i] == ans[i+1]) continue;
        uint32_t mask = ans[i];
        string ops;
        for (int i = 1; i < s.size(); i++) {
            int cur = mask % 3; mask /= 3;
            if (cur == 0) ops.push_back('>');
            if (cur == 1) ops.push_back('=');
            if (cur == 2) ops.push_back('<');
        }
        reverse(ops.begin(), ops.end());
        for (int i = 0; i < s.size(); i++) {
            if (i) cout << ops[i-1] << ' ';
            cout << s[i] << ' ';
        }
        cout << endl;return 0;
    }
    puts("Impossible");
    return 0;
 }
