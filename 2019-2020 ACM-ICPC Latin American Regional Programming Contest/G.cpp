#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 100;
struct SegmentTree{
    int Min[maxn * 4];
    void up(int x){
        Min[x] = min(Min[x<<1],Min[x<<1|1]);
    }
    void build(int x,int l,int r){
        Min[x] = INT_MAX;
        if (l == r){
            return;
        }
        int mid = l + r >> 1;
        build(x<<1,l,mid);
        build(x<<1|1,mid+1,r);
        up(x);
    }
    int query(int x,int l,int r,int L,int R){
        if (l > R || L > r)return INT_MAX;
        if (L <= l && r <= R)return Min[x];
        int mid = l + r >> 1;
        return min(query(x<<1,l,mid,L,R),query(x<<1|1,mid+1,r,L,R));
    }
    void update(int x,int l,int r,int pos,int val){
        if (l == r){
            Min[x] = min(Min[x],val);
            return;
        }
        int mid = l + r >> 1;
        if (pos <= mid)update(x<<1,l,mid,pos,val);
        else update(x<<1|1,mid+1,r,pos,val);
        up(x);
    }
}tree;
struct SAM{
    int nxt[maxn * 2][26],fa[maxn*2],l[maxn*2];
    int dp[maxn];
    int last,cnt;
    void clear(){
        last = cnt = 1;
        fa[1] = l[1] = 0;
        memset(nxt[1],0,sizeof nxt[1]);
    }
    SAM(){clear();}
    void init(const string &s){
        for (char ch : s){
            add(ch - 'A');
        }
    }
    void add(int c){
        int p = last;
        int np = ++cnt;
        memset(nxt[cnt],0,sizeof nxt[cnt]);
        l[np] = l[p] + 1;
        last = np;
        while (p && !nxt[p][c]) nxt[p][c] = np, p = fa[p];
        if (!p) fa[np] = 1;
        else{
            int q = nxt[p][c];
            if (l[q] == l[p] + 1)fa[np] = q;
            else{
                int nq = ++cnt;
                l[nq] = l[p] + 1;
                memcpy(nxt[nq],nxt[q],sizeof nxt[q]);
                fa[nq] = fa[q];fa[np] = fa[q] = nq;
                while (nxt[p][c] == q)nxt[p][c] = nq,p = fa[p];
            }
        }
    }
    int run(const string &t){
        int len = t.length();
        tree.build(1,0,len);
        tree.update(1,0,len,0,0);
        int now = 1;
        int LEN = 0;
        for (int i=1;i<=len;i++){
            int ch = t[i-1] - 'A';
            while (now != 1 and !nxt[now][ch]){
                 now = fa[now];
                 LEN = min(LEN,l[now]);
            }
            if (!nxt[now][ch])return -1;
            now = nxt[now][ch];
            LEN++;
            int dp_val = tree.query(1,0,len,i-LEN,i-1) + 1;

            tree.update(1,0,len,i,dp_val);
        }
        return tree.query(1,0,len,len,len);
    }
}sam;
string s;
int main(){
    cin>>s;
    sam.init(s);
    int T;
    cin>>T;
    while (T--){
        string t;
        cin>>t;
        cout<<sam.run(t)<<endl;
    }
    return 0;
}
