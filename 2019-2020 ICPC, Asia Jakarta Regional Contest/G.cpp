#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 100;
int sum[maxn];
vector<int> people[maxn];
struct SegmentTree{
    int Min[maxn*4];
    int Lazy[maxn*4];
    void down(int x){
        Min[x<<1] += Lazy[x];
        Min[x<<1|1] += Lazy[x];
        Lazy[x<<1] += Lazy[x];
        Lazy[x<<1|1] += Lazy[x];
        Lazy[x] = 0;
    }
    void up(int x){
        Min[x] = min(Min[x<<1],Min[x<<1|1]);
    }
    void build(int x,int l,int r,int *a){
        if (l == r){
            Min[x] = a[l];
            Lazy[x] = 0;
            return ;
        }
        Lazy[x] = 0;
        int mid = l + r >> 1;
        build(x<<1,l,mid,a);
        build(x<<1|1,mid+1,r,a);
        Min[x] = min(Min[x<<1],Min[x<<1|1]);
    }
    int query(int x,int l,int r,int L,int R){
        if (l > R || L > r)return INT_MAX;
        if (L <= l && r <= R)return Min[x];
        int mid = l + r >> 1;
        down(x);
        return min(query(x<<1,l,mid,L,R),query(x<<1|1,mid+1,r,L,R));
    }
    void update(int x,int l,int r,int L,int R,int del){
        if (l > R || L > r)return;
        if (L <= l && r <= R){
            Min[x] += del;
            Lazy[x] += del;
            return;
        }
        int mid = l + r >> 1;
        down(x);
        update(x<<1,l,mid,L,R,del);
        update(x<<1|1,mid+1,r,L,R,del);
        up(x);
    }
}tree;
int me;
int n,m,q;
int a[maxn];
int main(){
    scanf("%d%d%d",&n,&m,&q);
    for (int i=1;i<=n;i++){
        scanf("%d",a+i);
    }
    me = a[1];
    for (int i=2;i<=n;i++){
        sum[0] += a[i] < me;
    }
    for (int i=1;i<=m;i++){
        int r;
        scanf("%d",&r);
        int cnt = 0;
        sum[i-1] -= r;
        for (int j=0;j<r;j++){
            int x;
            scanf("%d",&x);
            x = x < me;
            cnt += x;
            people[i].push_back(x);
        }   
        sum[i] = sum[i-1] + cnt;
    }    
    tree.build(1,0,m,sum);
    while (q--){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        y--;
        z = z < me;
        int &ori = people[x][y];
        int del = 0;
        if (ori == 1 && z == 0){
            del = -1;
            ori = z;
        }else if (ori == 0 && z == 1){
            del = 1;
            ori = z;
        }
        tree.update(1,0,m,x,m,del);
        int min_val = tree.query(1,0,m,0,m-1);
        if (min_val < 0){
            puts("0");
        }else{
            puts("1");
        }
    }
    return 0;
}
