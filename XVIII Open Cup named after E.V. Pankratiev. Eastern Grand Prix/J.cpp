//
// Created by calabash on 10/31/18.
//
#include <bits/stdc++.h>
#define int ll
using namespace std;
typedef long long ll;
const int maxn = 86400+100;
struct Seg{
    ll Max[maxn*4];
    void up(int x){
        Max[x] = max(Max[x<<1],Max[x<<1|1]);
    }
    void update(int x,int l,int r,int pos,ll val){
        if (l == r){
            Max[x] = val;
            return ;
        }
        int mid = l + r >>1;
        if (pos <= mid)update(x<<1,l,mid,pos,val);
        else update(x<<1|1,mid+1,r,pos,val);
        up(x);
    }
    ll query(int x,int l,int r,int L,int R){
        if (l >R || L>R)return 0ll;
        if (L<=l && r<=R)return Max[x];
        int mid = l + r >>1;
        return max(query(x<<1,l,mid,L,R),query(x<<1|1,mid+1,r,L,R));
    }
}tree;
int n,c;
char s[100];
vector<pair<int,ll> > segs[maxn];
int get_stamp(int h,int m,int s){
    return h * 60* 60 + m * 60 + s +1 ;
}
signed main(){
    scanf("%lld%lld",&n,&c);
    for (int i=1;i<=n;i++){
        int h,m,s;
        scanf("%lld:%lld:%lld",&h,&m,&s);
        int l = get_stamp(h,m,s);
        scanf("%lld:%lld:%lld",&h,&m,&s);
        int r = get_stamp(h,m,s);
        ll p;
        scanf("%lld",&p);
        p -= 1ll * (r-l) * c;
        p = max(p,0ll);
        cerr<<l<<","<<r<<":"<<p<<endl;
        segs[r].push_back({l,p});
    }
    ll ans =0;
    for (int i=1;i<=86400;i++){
        ll temp = 0;
        for (auto pr : segs[i]){
            int l = pr.first;
            int r = i;
            ll p = pr.second;
            ll tmp = p + tree.query(1,0,86400,0,l);
            temp = max(temp,tmp);
        }
        ans = max(ans,temp);
        tree.update(1,0,86400,i,temp);
    }
    cout<<ans<<endl;
}
/*

 */
