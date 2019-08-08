#include <bits/stdc++.h>
using namespace std;
const int maxn = 205;
char s[maxn];
char t[maxn];
int T;
int n;
int dp[maxn];
int pre[maxn];
int min_rep(char *s, int l) {
    int i=0 ,j=1,k=0;
    while(i<l && j<l && k<l) {
        if(s[i+k]==s[j+k]) k++;
        else {
            if(s[i+k]<s[j+k]) j+=k+1;
            else i+=k+1;
            k=0;
            if(i==j) k++;
        }
    }
    return min(i,j);
}
bool check(int l,int r){
    r++;
    int len = r - l ;
    for (int i=l,idx = 0;i<r;i++,idx ++){
        s[idx] = t[i];
    }
    s[len] = '\0';
    //puts(s);
    int st = min_rep(s,len);
    //cout<<st<<endl;
    for (int o = 0;o < len;o ++){
        int ii = l + o;
        int jj = (st + o) % len;
        if (t[ii] != s[jj])return false;
    }
    return true;
}
int main(){
    scanf("%d",&T);
    while (T--){
        scanf("%s",t+1);
        n = strlen(t+1);
        if (check(1,n)){
            puts(t+1);
            continue;
        }
        for (int i=0;i<=n;i++)dp[i] = 0x3f3f3f3f,pre[i] = -1;
//        for (int i=0;i<n;i++){
//            if (check(0,i+1))dp[i] = 1,pre[i] = 0;
//        }
        dp[0] = 0;
        for (int i=1;i<=n;i++){
            for (int j = 1;j <=i;j++){
                if (check(j,i)){
                   // cerr<<"ok "<<j<<","<<i<<endl;
                    int dp_new = dp[j-1] + 1;
                    if (dp_new < dp[i]){
                        dp[i] = dp_new;
                        pre[i] = j-1;
                    }
                }
            }
        }
     //   cerr<<dp[n]<<endl;
        vector<pair<int,int> > ans(0);
        int now = n;
        while (now){
            int Pre = pre[now];
            ans.push_back(make_pair(Pre + 1,now));
            now = Pre;
        }
        reverse(ans.begin(), ans.end());
        for (auto pr : ans){

            int l,r;
            tie(l,r) = pr;
           // cerr<<l<<" "<<r<<endl;
            for (int i=l;i<=r;i++){
                printf("%c",t[i]);
            }
            printf(" ");
        }
        puts("");
    }
    return 0;
}
