#include<bits/stdc++.h>
#define right rrrrrrr
using namespace std;
const int maxn = 3e5+100;
typedef pair<int,int> P;
typedef long long ll;
int n;
P a[maxn];
int ans[maxn],ans_idx;
void output(){
    for (int i=0;i<n;i++){
        printf("%d ",ans[i]+1);
    }
    puts("");
}
struct Node{
    ll val;
    int id;
    bool operator <(const Node & other)const{
        return other.val < val;
    }
};
priority_queue<Node> TOP,RIGHT,TR;
int right,top;
inline void all_clear(){
    while (!TOP.empty())TOP.pop();
    while (!RIGHT.empty())RIGHT.pop();
    while (!TR.empty())TR.pop();
}
inline bool all_empty(){
    return TOP.empty() && RIGHT.empty() && TR.empty();
}
inline void adjust(){
    while (!TR.empty()){
        int id = TR.top().id;
        if (a[id].first <= right){
            TOP.push((Node){a[id].second,id});
            TR.pop();
        }else if (a[id].second <= top){
            RIGHT.push((Node){a[id].first,id});
            TR.pop();
        }else if (a[id].first <=right && a[id].second <=top){
            ans[ans_idx++] = id;
            TR.pop();
        }else break;
    }
    while (!TOP.empty()){
        int id = TOP.top().id;
        if (a[id].second <= top){
            ans[ans_idx++] = id;
            TOP.pop();
        }else break;
    }
    while (!RIGHT.empty()){
        int id = RIGHT.top().id;
        if (a[id].first <= right){
            ans[ans_idx++] = id;
            RIGHT.pop();
        }else break;
    }
}
bool check(){
    top = 1,right = 1;
    all_clear();
    ans_idx = 0;
    for (int i=0;i<n;i++){
        if (a[i].first <= 1 && a[i].second <=1){
            ans[ans_idx++] = i;
        }else if (a[i].first <= 1){
            TOP.push((Node){a[i].second,i});
        }else if (a[i].second <=1){
            RIGHT.push((Node){a[i].first,i});
        }else{
            TR.push((Node){a[i].first + a[i].second,i});
        }
    }
    while (1){
        if (all_empty()){
            return true;
        }
        //0 TOP
        //1 RIGHT
        //2 TR
        int flag = -1;
        ll val = 4e9;
        if (!TOP.empty() && TOP.top().val - top <=val){
            flag = 0;
            val = TOP.top().val - top;
        }
        if (!RIGHT.empty() && RIGHT.top().val - right <=val){
            flag = 1;
            val = RIGHT.top().val - right;
        }
        if (!TR.empty() && TR.top().val - top - right <=val){
            flag = 2;
            val = TR.top().val - top - right;
        }
        if (flag == -1)return false;
        if (flag == 0)top = TOP.top().val;
        else if (flag == 1) right = RIGHT.top().val;
        else if (flag == 2){
            int id = TR.top().id;
            top = a[id].second;
            right = a[id].first;
        }else assert(0);
        adjust();
        
    }
}
int main(){
    scanf("%d",&n);
    for (int i=0;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        a[i] = make_pair(x,y);
    }
    bool flag = check();
    assert(flag);
    output();
    return 0;
}
