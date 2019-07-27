#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 100;
char s[maxn];
int sum[maxn];
int cnt[maxn][3];
int main(){
    scanf("%s",s+1);
    int n = strlen(s+1);
    cnt[0][0] = 1;
    for (int i=1;i<=n;i++){
        sum[i] = sum[i-1] + s[i] - '0';
        sum[i] %= 3;
        for (int j=0;j<3;j++){
            cnt[i][j] = cnt[i-1][j];
        }
        cnt[i][sum[i]] ++;
    }
    long long ans = 0;
    //0
    for (int i=1;i<=n;i++){
        if (s[i] == '0')ans ++;
    }
    //00
    for (int i=2;i<=n;i++){
        if (s[i] == '0' && s[i-1] == '0')ans ++;
    }
    // x00
    for (int i=3;i<=n;i++){
        if (s[i] == '0' && s[i-1] == '0'){
            int sm = sum[i-2];
            ans += cnt[i-3][sm];
        }
    }
    cout<<ans<<endl;
}
