#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define MAXLOGN 18
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN];
int l[MAXLOGN][MAXN],r[MAXLOGN][MAXN];
int larr[MAXN],rarr[MAXN];
int pr[MAXN],pre[MAXN],suf[MAXN];
int st[MAXLOGN][MAXN][MAXLOGN];
void init(int n,int k)
{
    for(int i=n;i>=1;i--)
    {
        st[k][i][0]=larr[i];
        for(int j=1;(i+(1<<j)-1)<=n;++j) st[k][i][j]=min(st[k][i][j-1],st[k][i+(1<<j-1)][j-1]);
    }
}
int query(int k,int l,int r)
{
    int len=r-l+1,kk=pr[len];
    return min(st[k][l][kk],st[k][r-(1<<kk)+1][kk]);
}
struct segtree
{
    int maxi[4*MAXN];
    void pushup(int k)
    {
        maxi[k]=max(maxi[k*2],maxi[k*2+1]);
        //mini[k]=min(mini[k*2],mini[k*2+1]);
    }
    void build(int k,int l,int r)
    {
        if(l==r)
        {
          //  mini[k]=larr[l];
            maxi[k]=rarr[l];
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    int querymax(int k,int l,int r,int x,int y)
    {
        if(x>r||l>y) return 0;
        if(l>=x&&r<=y) return maxi[k];
        int mid=(l+r)/2;
        return max(querymax(k*2,l,mid,x,y),querymax(k*2+1,mid+1,r,x,y));
    }
   /* int querymin(int k,int l,int r,int x,int y)
    {
        if(x>r||l>y) return n+1;
        if(l>=x&&r<=y) return mini[k];
        int mid=(l+r)/2;
        return min(querymin(k*2,l,mid,x,y),querymin(k*2+1,mid+1,r,x,y));
    } */
}seg[MAXLOGN];
int curl[MAXN],curr[MAXN];
int tmpl[MAXN],tmpr[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) l[0][i]=max(1,i-a[i]),r[0][i]=min(n,i+a[i]);
    pr[1]=0;
    for(int i=2;i<=n;i++)
    {
        pr[i]=pr[i-1];
        if((1<<pr[i]+1)==i) ++pr[i];
    }
    for(int k=0;(1<<k)<n;k++)
    {
        for(int i=1;i<=n;i++) larr[i]=l[k][i],rarr[i]=r[k][i];
        seg[k].build(1,1,n); init(n,k);
        for(int i=1;i<=n;i++) 
        {
            l[k+1][i]=(l[k][i]==1?1:query(k,l[k][i],r[k][i]));
            r[k+1][i]=(r[k][i]==n?n:seg[k].querymax(1,1,n,l[k][i],r[k][i]));
        }
    }
    int ans=0;
    int t=0;
    while((1<<t)<n) t++;
    for(int i=1;i<=n;i++) curl[i]=i,curr[i]=i;
    for(int k=t-1;k>=0;k--)
    {
        for(int i=1;i<=n;i++)
        {
            tmpl[i]=(curl[i]==1?1:query(k,curl[i],curr[i]));
            tmpr[i]=(curr[i]==n?n:seg[k].querymax(1,1,n,curl[i],curr[i]));
        }
        bool f=true;
        for(int i=1;i<=n;i++) suf[i]=(i==1?tmpr[i]:min(suf[i-1],tmpr[i]));
        for(int i=n;i>=1;i--) pre[i]=(i==n?tmpl[i]:max(pre[i+1],tmpl[i]));
        for(int i=1;i<=n;i++)
        {
            if(tmpl[i]>1&&suf[tmpl[i]-1]<i) {f=false; break;}
            if(tmpr[i]<n&&pre[tmpr[i]+1]>i) {f=false; break;}
        }
        if(!f)
        {
            ans+=(1<<k);
            for(int i=1;i<=n;i++) curl[i]=tmpl[i],curr[i]=tmpr[i];
        } 
    }
    printf("%d\n",ans+1);
    return 0;
}
