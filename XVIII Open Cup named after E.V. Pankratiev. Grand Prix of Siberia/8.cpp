#include<bits/stdc++.h>
#define MAXN 130005
#define MAXM 10000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,q,tot, rg;
int res[MAXN];//array for persistent segment tree
int root[MAXN],lson[MAXM],rson[MAXM],cnt[MAXM],rang;
ll sum[MAXM];
vector<int> v;
void pushup(int k)
{
    cnt[k]=cnt[lson[k]]+cnt[rson[k]];
    sum[k]=sum[lson[k]]+sum[rson[k]];
}
void build(int &k,int l,int r)
{
    k=++tot;
    if(l==r) 
    {
        cnt[k]=sum[k]=0;
        return;
    }
    int mid=(l+r)/2;
    build(lson[k],l,mid); build(rson[k],mid+1,r);
    pushup(k);
}
void insert(int &k,int last,int l,int r,int p)
{
    k=++tot;
    cnt[k]=cnt[last]; sum[k]=sum[last];
    if(l==r)
    {
        cnt[k]++;
        sum[k]+=v[l-1];
        return;
    }
    lson[k]=lson[last]; rson[k]=rson[last];
    int mid=(l+r)/2;
    if(p<=mid) insert(lson[k],lson[last],l,mid,p); else insert(rson[k],rson[last],mid+1,r,p);
    pushup(k);
}
ll query_mink(int last,int k,int l,int r,int num)
{
    if(l==r) return 1LL*num*v[l-1];
    int mid=(l+r)/2;
    if(cnt[lson[k]]-cnt[lson[last]]<num) 
        return query_mink(rson[last],rson[k],mid+1,r,num-(cnt[lson[k]]-cnt[lson[last]]))+(sum[lson[k]]-sum[lson[last]]);
    else return query_mink(lson[last],lson[k],l,mid,num);
}
ll query_maxk(int last,int k,int l,int r,int num)
{
    if(l==r) return 1LL*num*v[l-1];
    int mid=(l+r)/2;
    if(cnt[rson[k]]-cnt[rson[last]]<num) 
        return query_maxk(lson[last],lson[k],l,mid,num-(cnt[rson[k]]-cnt[rson[last]]))+(sum[rson[k]]-sum[rson[last]]);
    else return query_maxk(rson[last],rson[k],mid+1,r,num);
}
//usage:
//for the sum of minimum k values in [l,r]: query_mink(root[l-1],root[r],1,rg,k)
//for the sum of maximum k values in [l,r]: query_maxk(root[l-1],root[r],1,rg,k)
void init()
{
    for(int i=1;i<=n;i++) v.push_back(res[i]);
    sort(v.begin(),v.end()); v.erase(unique(v.begin(),v.end()),v.end());
    for(int i=1;i<=n;i++) res[i]=lower_bound(v.begin(),v.end(),res[i])-v.begin()+1;
    rg=(int)v.size();
    build(root[0],1,rg);
    for(int i=1;i<=n;i++) insert(root[i],root[i-1],1,rg,res[i]);

}

typedef long long LL;
#define rep(i, n) for (int i = 0; i < n ; i++)
int main()
{
    //code here
    //save the needed value in array res with value range [1,m] and length 
    int m; scanf("%d", &n);
    vector<int> a(n), b(n);
    vector<LL> psum(n+1);
    rep (i, n) scanf("%d", &a[i]);
    rep (i, n) scanf("%d", &b[i]);
    rep (i, n) {
        psum[i+1] = a[i] + b[i];
    }
    partial_sum(psum.begin(), psum.end(), psum.begin());
    rep (i, n) {
        res[i+1] = a[i] - b[i];
//        cout << res[i+1] << ' ' ;
    } 
 //   cout << endl;
    init();
    scanf("%d", &m);
    while (m--) {
        int l, r; scanf("%d%d", &l, &r);
        LL ans = psum[r] - psum[l-1];
        int len = (r + 1 - l) / 3;
        ans += query_maxk(root[l-1], root[r], 1, rg, len);
        ans -= query_mink(root[l-1], root[r], 1, rg, len);
        printf("%lld%s\n", ans / 2, ((ans & 1) ? ".5" : "" ));
    }
    
    return 0;
}
