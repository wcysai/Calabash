#include <bits/stdc++.h>
using namespace std;
const int maxn = 10;
vector<pair<int,int> > ans[100];
bool used[maxn];
void cons(const vector<pair<int,int> > steps, pair<int,int> now){
    vector<pair<int,int> > s = steps;
    if (now.second != 8){
        pair<int,int> Now = {now.first,8};
        s.push_back(Now);
        if (Now.first != 8){
            s.push_back({8,8});
        }
        int cnt = s.size() -1;
        if (ans[cnt].size());
        else{
            ans[cnt] = s;
        }
    }else{
        pair<int,int> Now = {8,8};
        s.push_back(Now);
        int cnt = s.size() -1;
        if (ans[cnt].size());
        else{
            ans[cnt] = s;
        }
    }
    memset(used,0,sizeof used);
    for (pair<int,int> pii : steps){
        if (pii.second == now.second){
            used[pii.first] = 1;
        }
    }
    int canused = -1;
    for (int i=1;i<=7;i++){
        if (!used[i]){
            canused = i;
            break;
        }
    }
    if (canused== -1)return;
    s = steps;
    s.push_back({canused,now.second});
    if (now.second != 8)
    s.push_back({canused,8});
    s.push_back({8,8});
    int cnt = s.size()-1;
    /*
    if (cnt == 6){
        for (pair<int,int> pii : steps){
            printf("!  [%d,%d]\n",pii.first,pii.second);
        }
    }
    */
    if (ans[cnt].size());
    else{
        ans[cnt] = s;
    }
}
bool ok[maxn][maxn];
int main(){
    vector<pair<int,int> > steps(0);
    pair<int,int> now = {1,1};
    steps.push_back(now);
    bool Used[10];
    memset(Used,0,sizeof Used);
    Used[1] = 1;
    for (int i=1;i<=8;i++){
        cons(steps,now);
        if (i != 8){
            now = {8,now.second};
            Used[8] = 1;
            steps.push_back(now);
            cons(steps,now);
        }
        for (int i=7;i>=1;i--){
            if (Used[i])continue;
            now = {i,now.second};
            steps.push_back(now);
            Used[i] = 1;
            cons(steps,now);
        }
        memset(Used,0,sizeof Used);
        if (i <= 7){
            Used[now.first] = 1;
            now = {now.first,i+1};
            steps.push_back(now);
            cons(steps,now);
        }
    }
/*
    for (int i=2;i<=63;i++){
        if (ans[i].size() == 0){
            printf("%d\n",i);
        }
//        assert(ans[i].size() != 0);
        memset(ok,0,sizeof ok);
        for (pair<int,int> pos : ans[i]){
//            assert(ok[pos.first][pos.second] == 0);
            if (ok[pos.first][pos.second])printf("%d %d %d\n",i,pos);
            ok[pos.first][pos.second] = 1;
        }
    }
    */
    int n;
    cin>>n;
    vector<pair<int,int> > &V = ans[n];
    for (pair<int,int> pos: V){
        printf("%c%d ",pos.first +'a'-1,pos.second);
    }
    
    puts("");
    return 0;
}
