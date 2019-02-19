//
// Created by bytedance on 19-2-19.
//
#include <bits/stdc++.h>
using namespace std;
const int maxn = 6e5+100;
typedef long long ll;
char s[maxn];
int ch[maxn];
int lc[maxn];
int n;
int N;
void manacher(){
    N = 2 * n + 1;
    ch[N] = '#';
    for (int i=n;i>=1;i--){
        ch[i*2] = s[i];
        ch[i*2-1] = '#';
    }
    ch[0] = 'z'+1;
    ch[N+1] = '\0';
    lc[1] = 1;
    int k=1;
    for (int i=2;i<=N;i++){
        int p = k + lc[k] - 1;
        if (i <= p){
            lc[i] = min(lc[2*k-i],p-i+1);
        }else{
            lc[i] = 1;
        }
        while (ch[i+lc[i]] == ch[i-lc[i]])lc[i] ++;
        if (i + lc[i] > k + lc[k]) k = i;
    }
    //for (int i=1;i<=N;i++){
    //    printf("lc[%d]=%d\n",i,lc[i]);
    //}
    //for (int i=1;i<=N;i++){
    //    printf("%c ",ch[i]);
    //}
    //puts("");
}
ll ans[maxn];
struct QUERY{
    int l,mid,r,id;
};
struct Seg_Tree{
    ll sum[maxn*4];
    ll lazy[maxn*4];
    void up(int x){
        sum[x] = sum[x<<1] + sum[x<<1|1];
    }
    void down(int x,int l,int mid,int r){
        if (lazy[x]){
            lazy[x<<1] += lazy[x];
            lazy[x<<1|1] += lazy[x];
            sum[x<<1] += 1ll * lazy[x] * (mid-l+1);
            sum[x<<1|1] += 1ll * lazy[x] * (r - mid);
            lazy[x] = 0;
        }
    }
    void build(int x,int l,int r){
        sum[x] = 0;
        lazy[x] = 0;
        if (l == r)return;
        int mid = l + r >> 1;
        build(x<<1,l,mid);
        build(x<<1|1,mid+1,r);
    }
    void add(int x,int l,int r,int L,int R,ll val){
        if (l > R || L > r)return;
        if (L<= l && r <= R){
            sum[x] += 1ll * (r-l + 1) * val;
            lazy[x] += val;
            return;
        }
        int mid = l + r >> 1;
        down(x,l,mid,r);
        add(x<<1,l,mid,L,R,val);
        add(x<<1|1,mid+1,r,L,R,val);
        up(x);
    }
    ll query(int x,int l,int r,int L,int R){
        if (l > R || L > r)return 0;
        if (L <= l && r <= R)return sum[x];
        int mid = l +r >> 1;
        down(x,l,mid,r);
        return query(x<<1,l,mid,L,R) + query(x<<1|1,mid+1,r,L,R);
    }
}segtree;
vector<QUERY> query;
void workl(){
    segtree.build(1,1,N);
    sort(query.begin(),query.end(),[](const QUERY x ,const QUERY y){
        return x.mid < y.mid;
    });
    for (int i=1,j=0;i<=N && j < query.size();i++){
        while (j < query.size() && query[j].mid == i ){
            ans[query[j].id] += segtree.query(1,1,N,query[j].l,query[j].mid-1);
            j++;
        }
        segtree.add(1,1,N,i-lc[i] + 1,i,1);
    }
}
void workr(){
    segtree.build(1,1,N);
    sort(query.begin(),query.end(),[](const QUERY x ,const QUERY y){
        return x.mid > y.mid;
    });
    for (int i=N,j=0;i>=1 && j < query.size();i--){
        while (j < query.size() && query[j].mid == i){
            ans[query[j].id] += segtree.query(1,1,N,query[j].mid+1,query[j].r);
            j++;
        }
        segtree.add(1,1,N,i,i+lc[i] -1,1);
    }
}
void workmid(){
    sort(query.begin(),query.end(),[](const QUERY x ,const QUERY y){
        return x.mid < y.mid;
    });
    for (int i=1,j=0;i<=N&& j < query.size();i++){
        while (query[j].mid == i){
            ans[query[j].id] += min(lc[i],query[j].mid - query[j].l + 1);
            j++;
        }
    }
}
void debug(int q){
    for (int i=1;i<=q;i++){
        printf("ans[%d]=%lld\n",i,ans[i]);
    }
}
int main(){
    scanf("%s",s+1);
    n = strlen(s+1);
    manacher();
    int q;
    scanf("%d",&q);
    for (int i=1;i<=q;i++){
        int l,r;
        scanf("%d%d",&l,&r);
        ans[i] = - (r-l+2);
        l = 2*l-1;
        r = 2 * r + 1;
        int mid = l + r >> 1;
        query.push_back((QUERY){l,mid,r,i});
    }
    workl();
    //debug(q);
    workr();
    workmid();
    for (int i=1;i<=q;i++){
        printf("%lld\n",ans[i]/2);
    }
    return 0;
}
