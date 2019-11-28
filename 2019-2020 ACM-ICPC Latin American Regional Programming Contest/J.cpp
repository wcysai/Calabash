#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
int a[MAXN];
struct segtree
{
    int maxi[4*MAXN];
    void pushup(int k)
    {
        maxi[k]=max(maxi[k*2],maxi[k*2+1]);
    }
    void build(int k,int l,int r)
    {
        if(l==r)
        {
            maxi[k]=a[l];
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    void update(int k,int l,int r,int pos,int v)
    {
        if(l==r)
        {
            maxi[k]=v;
            return;
        }
        int mid=(l+r)/2;
        if(pos<=mid) update(k*2,l,mid,pos,v); else update(k*2+1,mid+1,r,pos,v);
        pushup(k);
    }
    int query(int k,int l,int r,int x,int y)
    {
        if(l>y||x>r) return -1;
        if(l>=x&&r<=y) return maxi[k];
        int mid=(l+r)/2;
        return max(query(k*2,l,mid,x,y),query(k*2+1,mid+1,r,x,y));
    }
    int find_prev(int k,int l,int r,int pos,int v)
    {
        if(r<=pos)
        {
            if(maxi[k]<=v) return -1;
            if(l==r) return l;
            int mid=(l+r)/2;
            if(maxi[k*2+1]>v) return find_prev(k*2+1,mid+1,r,pos,v); else return find_prev(k*2,l,mid,pos,v);
        }
        int mid=(l+r)/2;
        if(mid+1<=pos)
        {
            int x=find_prev(k*2+1,mid+1,r,pos,v);
            if(x!=-1) return x;
        }
        return find_prev(k*2,l,mid,pos,v);
    }
    int find_next(int k,int l,int r,int pos,int v)
    {
        if(l>=pos)
        {
            if(maxi[k]<=v) return -1;
            if(l==r) return l;
            int mid=(l+r)/2;
            if(maxi[k*2]>v) return find_next(k*2,l,mid,pos,v); else return find_next(k*2+1,mid+1,r,pos,v);
        }
        int mid=(l+r)/2;
        if(mid>=pos)
        {
            int x=find_next(k*2,l,mid,pos,v);
            if(x!=-1) return x;
        }
        return find_next(k*2+1,mid+1,r,pos,v);
    }
}seg;
string str;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    seg.build(1,1,n);
    for(int i=0;i<m;i++)
    {
        int x,y;
        cin>>str;
        if(str[0]=='U')
        {
            scanf("%d%d",&x,&y);
            seg.update(1,1,n,x,y); a[x]=y;
        }
        else
        {
            scanf("%d",&x);
            if(str[0]=='L'&&seg.query(1,1,n,1,x)==a[x]) {printf("%d\n",x); continue;}
            if(str[0]=='R'&&seg.query(1,1,n,x,n)==a[x]) {printf("%d\n",x); continue;}
            int lhs=seg.query(1,1,n,1,x),rhs=seg.query(1,1,n,x,n);
            if(lhs<rhs) printf("%d\n",seg.find_next(1,1,n,x+1,lhs));
            else printf("%d\n",seg.find_prev(1,1,n,x-1,rhs));
        }
    }
    return 0;
}
