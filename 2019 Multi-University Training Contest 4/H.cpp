#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+100;
int a[maxn];
int root[maxn];int cnt,m,n,T;
struct Chairman_Tree{
    struct Node{int L,R,val;}tree[maxn*60];
    void init(){
        memset(root,0,sizeof root);
        cnt =0;
    }
    /* 建T0空树 */
    int buildT0(int l, int r){
        int k = cnt++;
        tree[k].val =0;
        if (l==r) return k;
        int mid = l+r >>1;
        tree[k].L = buildT0(l, mid);tree[k].R = buildT0(mid + 1, r);
        return k;
    }
    /* 上一个版本节点P，【ppos】+=del 返回新版本节点*/
    int update (int P,int l,int r,int ppos,int del){
        int k = cnt++;
        tree[k].val = tree[P].val +del;
        if (l==r) return k;
        int mid = l+r >>1;
        if (ppos<=mid){
            tree[k].L = update(tree[P].L,l,mid,ppos,del);
            tree[k].R = tree[P].R;
        }else{
            tree[k].L = tree[P].L;
            tree[k].R = update(tree[P].R,mid+1,r,ppos,del);
        }
        return k;
    }
    int query_sum(int lt,int rt,int l,int r,int L,int R){
        if (l > R || L > r)return 0;
        if (L <= l && r <= R)return tree[rt].val - tree[lt].val;
        int mid = l + r >> 1;
        return query_sum(tree[lt].L,tree[rt].L,l,mid,L,R) + query_sum(tree[lt].R, tree[rt].R, mid+1, r, L, R);
    }
}tree;
int ANS = 0;
int check(int l,int r,int p,int Mid){
    int sm = max(1,p - Mid);
    int bg = min(1000000,p + Mid);
    int cnt = tree.query_sum(root[l-1], root[r], 1, 1000000, sm, bg);
    //cerr<<l<<" "<<r<<" "<<p<<" "<<Mid<<" "<<cnt<<endl;
    return cnt;
}
int gao(int l,int r,int p,int k){
    int L = 0;
    int R = 1000000;
    while (R - L > 1){
        int Mid = L +R >> 1;
        if (check(l,r,p,Mid) >= k){
            R = Mid;
        }else{
            L = Mid;
        }
    }
    for (int i=L;i<=R;i++){
        if (check(l,r,p,i) >=k)return i;
    }
    assert(0);
}
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d",&n,&m);
        for (int i=1;i<=n;i++)root[i] = 0;
        cnt = 0;
        ANS = 0;
        for (int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        root[0] = tree.buildT0(1, 1000000);
        for (int i=1;i<=n;i++){
            root[i] = tree.update(root[i-1], 1, 1000000, a[i], 1);
        }
        while (m--){

            int l,r,k,p;scanf("%d%d%d%d",&l,&r,&p,&k);
            l ^= ANS;
            r ^= ANS;
            k ^= ANS;
            p ^= ANS;
            printf("%d\n",ANS =gao(l,r,p,k));
        }
    }
    return 0;
}
/*
 2
 5 2
 31 2 5 45 4
 1 5 5 1
 2 5 3 2
 5 2
 31 2 5 45 4
 1 5 5 1
 2 5 3 2

 */
