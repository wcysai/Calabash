#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 100;
const int mod = 11092019;
pair<int,int> merge(pair<int,int> x,pair<int,int> y){
        if (x.first == y.first)return make_pair(x.first,(x.second + y.second)%mod);
        if (x.first > y.first)return x;
        else return y;
}

typedef pair<pair<int,int> *,pair<int,int> > RECORD;
RECORD record[maxn * 21];
int top;
inline int lowbit(int x){return x & -x;}
struct BIT{
    pair<int,int> Max[maxn];
    void update(int x,pair<int,int> val){
        while (x < maxn){
            record[top++] = make_pair(&Max[x],Max[x]);
            Max[x] = merge(Max[x],val);
            x += lowbit(x);
        }
    }
    pair<int,int> query(int x){
        pair<int,int> ans = {0,0};
        while (x){
            ans = merge(ans,Max[x]);
            x -= lowbit(x);
        }
        return ans;
    }

}bit;
int n;
pair<int,int> ans[maxn];
int label[maxn];
vector<int> E[maxn];
void dfs(int x){
    int pre = top;
    pair<int,int> temp = bit.query(label[x]);
    temp.first ++;
    ans[x] = temp;
    bit.update(label[x],ans[x]);
    for (int y : E[x]){
        dfs(y);
    }
    while (top != pre){
        auto pr = record[top-1];
        (*pr.first) = pr.second;
        top--;
    }
}
int main(){
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        scanf("%d",label+i);
        label[i] +=2;
    }
    bit.update(1,make_pair(0,1));
    for (int i=2;i<=n;i++){
        int p;
        scanf("%d",&p);
        E[p].push_back(i);
    }
    dfs(1);
    pair<int,int> ANS = make_pair(0,0);
    for (int i=1;i<=n;i++){
        ANS = merge(ANS,ans[i]);
    }
    cout<<ANS.first<<" "<<ANS.second<<endl;
    return 0;
}
