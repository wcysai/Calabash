#include <bits/stdc++.h>
using namespace std;
const int maxn = 100000 + 100;
struct SegmentTree{
    int Max[maxn<<2];
    int Lazy[maxn<<2];
    void build(int x,int l,int r){
        Max[x] = 0;
        Lazy[x] = 0;
        if (l == r)return;
        int mid = l + r >> 1;
        build(x<<1,l,mid);
        build(x<<1|1,mid+1,r);
        up(x);
    }
    void up(int x){
        Max[x] = max(Max[x<<1],Max[x<<1|1]);
    }
    void down(int x){
        if (Lazy[x] == 0)return;
        Max[x<<1] += Lazy[x];
        Max[x<<1|1] += Lazy[x];
        Lazy[x<<1] += Lazy[x];
        Lazy[x<<1|1] += Lazy[x];
        Lazy[x] = 0;
    }
    int query(){
        return Max[1];
    }
    void update(int x,int l,int r,int L,int R,int val){
        if (l > R || L > r)return;
        if (L <= l && r <= R){
            Max[x] += val;
            Lazy[x] += val;
            return;
        }
        int mid = l + r >> 1;
        down(x);
        update(x<<1,l,mid,L,R,val);
        update(x<<1|1,mid+1,r,L,R,val);
        up(x);
    }
}tree;
vector<pair<int,int> > a;
int main(){
    int n;
    scanf("%d",&n);
    int ans = INT_MAX;
    int LEN = 100001;
    tree.build(1,1,LEN);
    for (int i=0;i<n;i++){
        int l,r;
        scanf("%d%d",&l,&r);
        r--;
        a.push_back(make_pair(l,r));
        tree.update(1,1,LEN,l,r,1);
    }
    for (int i=0;i<n;i++){
        int l,r;
        tie(l,r) = a[i];
        tree.update(1,1,LEN,l,r,-1);
        ans = min(ans,tree.query());
        tree.update(1,1,LEN,l,r,1);
    }
    cout<<ans<<endl;
    return 0;
}
