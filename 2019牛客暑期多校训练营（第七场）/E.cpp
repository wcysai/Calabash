#include<bits/stdc++.h>
#define MAXN 400005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int N;
int X[MAXN],Y[MAXN],L[MAXN],R[MAXN];
vector<int> v;
int X1,X2,Y1,Y2,A1,A2,B1,B2,C1,C2,M1,M2;
struct segtree
{
    ll sum[8*MAXN];
    int lazy[8*MAXN],len[8*MAXN];
    void pushup(int k)
    {
        sum[k]=sum[k*2]+sum[k*2+1];
    }
    void pushdown(int k)
    {
        if(!lazy[k]) return;
        for(int i=k*2;i<=k*2+1;i++)
        {
            lazy[i]+=lazy[k];
            sum[i]+=lazy[k]*len[i];
        }
        lazy[k]=0;
        return;
    }
    void build(int k,int l,int r)
    {
        if(l==r)
        {
            len[k]=v[l]-v[l-1];
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
        len[k]=len[k*2]+len[k*2+1];
    }
    void update(int k,int l,int r,int x,int y)
    {
        if(x>r||l>y) return;
        if(l>=x&&r<=y)
        {
            lazy[k]++;
            sum[k]+=len[k];
            return;
        }
        pushdown(k);
        int mid=(l+r)/2;
        update(k*2,l,mid,x,y); update(k*2+1,mid+1,r,x,y);
        pushup(k);
    }
    int query(int k,int l,int r,ll x)
    {
        if(l==r)
        {
            int cnt=sum[k]/len[k];
            int id=(x-1)/cnt;
            return v[l-1]+id;
        }
        pushdown(k);
        int mid=(l+r)/2;
        if(sum[k*2]>=x) return query(k*2,l,mid,x); else return query(k*2+1,mid+1,r,x-sum[k*2]);
    }
}seg;
int main()
{
    scanf("%d",&N);
    scanf("%d%d%d%d%d%d",&X1,&X2,&A1,&B1,&C1,&M1);
    scanf("%d%d%d%d%d%d",&Y1,&Y2,&A2,&B2,&C2,&M2);
    X[1]=X1; X[2]=X2; Y[1]=Y1; Y[2]=Y2;
    for(int i=3;i<=N;i++)
    {
        X[i]=(1LL*A1*X[i-1]+1LL*B1*X[i-2]+C1)%M1;
        Y[i]=(1LL*A2*Y[i-1]+1LL*B2*Y[i-2]+C2)%M2;
    }
    for(int i=1;i<=N;i++)
    {
        L[i]=min(X[i],Y[i])+1;
        R[i]=max(X[i],Y[i])+1; R[i]++;
        v.push_back(L[i]); v.push_back(R[i]);
    }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    for(int i=1;i<=N;i++)
    {
        L[i]=lower_bound(v.begin(),v.end(),L[i])-v.begin()+1;
        R[i]=lower_bound(v.begin(),v.end(),R[i])-v.begin()+1;
        R[i]--;
    }
    int sz=(int)v.size()-1;
    seg.build(1,1,sz);
    ll sum=0;
    for(int i=1;i<=N;i++)
    {
        seg.update(1,1,sz,L[i],R[i]);
        sum+=v[R[i]]-v[L[i]-1];
        printf("%d\n",seg.query(1,1,sz,(sum+1)/2));
    }
    return 0;
}
