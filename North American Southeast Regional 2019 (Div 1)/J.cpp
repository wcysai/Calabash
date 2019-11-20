#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 100;
struct SegmentTree{
    pair<int,int> Min[maxn * 4];
    void up(int x){
        Min[x] = min(Min[x<<1],Min[x<<1|1]);
    }
    void build(int x,int l,int r,int *a){
        if (l == r){
            Min[x] = make_pair(a[l],l);
            return;
        }
        int mid = l + r >> 1;
        build(x << 1,l,mid,a);
        build(x << 1 | 1,mid+1,r,a);
        up(x);
    }
    pair<int,int> query(int x,int l,int r,int L,int R){
        if (l > R || L > r)return make_pair(INT_MAX,-1);
        if (L <= l && r <= R)return Min[x];
        int mid = l + r >> 1;
        return min(query(x<<1,l,mid,L,R),query(x<<1|1,mid+1,r,L,R));
    }
    void update(int x,int l,int r,int pos,pair<int,int> val){
        if (l == r){
            Min[x] = val;
            return;
        }
        int mid = l + r >> 1;
        if (pos <= mid)update(x<<1,l,mid,pos,val);
        else update(x<<1|1,mid+1,r,pos,val);
        up(x);
    }
}tree;
set<pair<int,int> > st;
vector<int> pos[maxn];
int a[maxn];
int ans[maxn];
int now;
bool used[maxn];
int main(){
    int n,k;
    cin>>n>>k;
    for (int i=1;i<=n;i++){
        cin>>a[i];
        pos[a[i]].push_back(i);
    }
    tree.build(1,1,n,a);
    for (int i=1;i<=k;i++){
        st.insert(make_pair(pos[i].back(),i));
    }
    int last = 0;
    for (int i=1;i<=k;i++){
        while (!st.empty() and used[st.begin()->second])st.erase(st.begin());
        pair<int,int> target = make_pair(INT_MAX,-1);
        int bound = st.begin() ->first;
        auto pr = tree.query(1,1,n,last + 1,bound - 1);
        target = min(target,pr);
        if (st.begin()->second < target.first){
            int v = st.begin()->second;
            int idx = lower_bound(pos[v].begin(),pos[v].end(),last + 1) - pos[v].begin();
            target = min(target,make_pair(v,pos[v][idx]));
        }
        ans[i] = target.first;
        used[target.first] = 1;
        for (int x  : pos[target.first]){
            tree.update(1,1,n,x,make_pair(INT_MAX,-1));
        }
        last = target.second;
    }
    for (int i=1;i<=k;i++){
        printf("%d ",ans[i]);
    }
    puts("");
    return 0;
}
