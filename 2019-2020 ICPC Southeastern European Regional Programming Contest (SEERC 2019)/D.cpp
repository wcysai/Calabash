#include <bits/stdc++.h>
using namespace std;
const int maxn = 1000000 + 5;
int cnt[1000];
char s[maxn];
char ans[maxn];
set<int> chars;
int main(){
    cin>>s + 1;
    int n = strlen(s + 1);
    n /= 2;
    for (int i=1;i<=2 * n;i ++){
        cnt[s[i]]++;
    }
    int number = 0;
    int biggest = 'a';
    for (int i='a';i<='z';i++){
        if (cnt[i] > cnt[biggest])biggest = i;
        number += cnt[i] != 0;
        if (cnt[i])chars.insert(i);
    }
    if (cnt[biggest]<=n){
        cout<<"YES"<<endl;
        int now = 1;
        for (int i='a';i<='z';i++){
            for (int o = 0;o < cnt[i];o ++)ans[now++] = i;
        }
        cout<<ans+1<<endl;
        return 0;
    }
    if (cnt[biggest] >= 2 * n - 1 || cnt[biggest] == 2 * n - 2 && number == 2){
        cout<<"NO"<<endl;
        return 0;
    }
    chars.erase(biggest);
    int now = 1;
    for (int i=0;i<n-1;i++){
        ans[now++] = biggest;
        cnt[biggest] --;
    }
    int t = *chars.begin();
    ans[now++] = t;
    cnt[t] --;
    while (cnt[biggest]){
        ans[now++] = biggest;
        cnt[biggest] --;
    }
    for (int i='a';i<='z';i++){
        for (int t = 0;t < cnt[i];t ++){
            ans[now++] = i;
        }
    }
    cout<<"YES"<<endl;
    cout<<ans+1<<endl;
    return 0;
}
