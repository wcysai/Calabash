//
// Created by calabash_boy on 18-7-7.
// query_kth_element
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+100;
typedef pair<int,int> pii;
pair<pii,int> Q[maxn];
int ans[maxn];
int a[maxn];
int m,n;
inline int read(){
    char c = getchar();
    int ret =0;
    while (c<'0'||c>'9')c = getchar();
    while (c>='0'&&c<='9')ret = ret*10+c-'0',c = getchar();
    return ret;
}
struct BIT{
    int val[maxn];
    int lowbit(int x){
        return x&(-x);
    }
    void init(){
        memset(val,0,sizeof val);
    }
    void add(int x,int delta){
        while (x<maxn){
            val[x]+=delta;
            x+=lowbit(x);
        }
    }
    int query(int x){
        int ret = 0;
        while (x){
            ret+=val[x];
            x-=lowbit(x);
        }
        return ret;
    }
    int Query(int l,int r){
        return query(r)-query(l-1);
    }
}tree;
pii ind[maxn];
bool cmp(pair<pii,int>& a,pair<pii,int>& b){
    return a.first.second<b.first.second;
}
int main(){
    int T =1;
    while (scanf("%d%d",&n,&m)!=EOF){
        T++;
        for (int i=1;i<=n;i++){
            a[i] = read();
            a[i+n] = a[i];
        }
        for (int i=1;i<=m;i++){
            int l=read(),r=read();
            Q[i].first.first = r;
            Q[i].first.second = n+l;
            Q[i].second =i;
        }
        sort(Q+1,Q+1+m,cmp);
        for (int i=1,j=1;i<=2*n;i++){
            tree.add(i,1);
            if (ind[a[i]].first==T){
                tree.add(ind[a[i]].second,-1);
            }
            ind[a[i]] = {T,i};
            while (j<=m&&Q[j].first.second==i){
                ans[Q[j].second] = tree.Query(Q[j].first.first,Q[j].first.second);
                j++;
            }
            if (j>m)break;
 
        }
        for (int i=1;i<=m;i++){
            printf("%d\n",ans[i]);
        }
        for (int i=0;i<=2*n;i++){
            tree.val[i] =0;
        }
    }
    return 0;
}
