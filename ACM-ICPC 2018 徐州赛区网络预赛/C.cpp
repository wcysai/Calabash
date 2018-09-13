#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef long long LL;
typedef long double db;
int score[] = {0,0,0,0,0,0,10000,36,720,360,80,252,108,72,54,180,72,180,119,36,360,1080,144,1800,3600};
int cd[8][3] = {
        1,2,3,
        4,5,6,
        7,8,9,
        1,4,7,
        2,5,8,
        3,6,9,
        1,5,9,
        3,5,7
};
LL ans =0;
char mp[30][40];
bool used[100];
set<int> num;
int cnt;
//int ans =0;
LL cd_ans[8];
int a[10];
vector<int> stars,pounds;
inline bool is_num(int x){
    return x >='0' && x <='9';
}
inline bool is_star(int x){
    return x == '*';
}
void dfs_pound(int dep){
    if (dep == pounds.size()){
        for (int i=0;i<8;i++){
            int sum =0;
            for (int j=0;j<3;j++){
                sum += a[cd[i][j]-1];
            }
            assert(sum >=6 && sum <= 24);
            cd_ans[i] += score[sum];
        }
        return ;
    }
    int id = pounds[dep];
    set<int> tmp = num;
    for (auto dig : tmp){
        a[id] = dig;
        num.erase(dig);
        dfs_pound(dep+1);
        num.insert(dig);
    }
}

void dfs_star(int dep){
    if (dep == stars.size()){
        memset(cd_ans,0,sizeof cd_ans);
        dfs_pound(0);
        LL temp_ans =0;
        for (int i=0;i<8;i++){
            temp_ans = max(temp_ans,cd_ans[i]);
        }
        ans += temp_ans;
        return ;
    }
    int id = stars[dep];
    set<int> tmp = num;
    for (auto dig : tmp){
        a[id] = dig;
        num.erase(dig);
        dfs_star(dep+1);
        num.insert(dig);
    }
}
int fac[100];
void solve(){
    for (int i=0;i<3;i++){
        scanf("%s",mp+i);
    }
    int num_of_pound = 0;
    stars.clear();
    pounds.clear();
    memset(used,0,sizeof used);
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            int id = i*3+j;
            a[id] =0;
            if (is_num(mp[i][j])){
                used[mp[i][j]-'0'] = 1;
                a[id] = mp[i][j] - '0';
            }else if (is_star(mp[i][j])){
                stars.push_back(id);
                num_of_pound++;
            }else{
                num_of_pound++;
                pounds.push_back(id);
            }
        }
    }
    num.clear();
    for (int i=1;i<=9;i++){
        if (!used[i]){
            num.insert(i);
        }
    }
    ans =0;
    dfs_star(0);
    double true_ans = ans*1.0/fac[num_of_pound];
    printf("%.8lf\n",true_ans);
}
int main(){
    fac[0] = 1;
    for (int i=1;i<10;i++){
        fac[i] = fac[i-1] * i;
    }
    int T;
    for (scanf("%d",&T);T;T--){
        solve();
    }
    return 0;
}
