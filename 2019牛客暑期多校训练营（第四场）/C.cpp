#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 3000005
#define INF 5000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN],b[MAXN];
ll sum[MAXN];

inline bool scan_d(int &num)
{
        char in;bool IsN=false;
        in=getchar();
        if(in==EOF) return false;
        while(in!='-'&&(in<'0'||in>'9')) in=getchar();
        if(in=='-'){ IsN=true;num=0;}
        else num=in-'0';
        while(in=getchar(),in>='0'&&in<='9'){
                num*=10,num+=in-'0';
        }
        if(IsN) num=-num;
        return true;
}
struct segtree
{
    ll maxi[4*MAXN],mini[4*MAXN];
    void pushup(int k)
    {
        maxi[k]=max(maxi[k*2],maxi[k*2+1]);
        mini[k]=min(mini[k*2],mini[k*2+1]);
    }
    void build(int k,int l,int r)
    {
        if(l==r)
        {
            maxi[k]=mini[k]=sum[l];
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    ll query_max(int k,int l,int r,int x,int y)
    {
        if(x>r||l>y) return -INF;
        if(l>=x&&r<=y) return maxi[k];
        int mid=(l+r)/2;
        return max(query_max(k*2,l,mid,x,y),query_max(k*2+1,mid+1,r,x,y));
    }
    ll query_min(int k,int l,int r,int x,int y)
    {
        if(x>r||l>y) return INF;
        if(l>=x&&r<=y) return mini[k];
        int mid=(l+r)/2;
        return min(query_min(k*2,l,mid,x,y),query_min(k*2+1,mid+1,r,x,y));
    }
}seg;
int L[MAXN],R[MAXN];
int st[MAXN];
int main()
{
    scan_d(n);
    for(int i=1;i<=n;i++) scan_d(a[i]);
    for(int i=1;i<=n;i++) scan_d(b[i]);
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+b[i];
    seg.build(1,1,n);
	int t=0;
	for(int i=1;i<=n;i++)
	{
		while(t>0&&a[st[t-1]]>=a[i]) t--;
		L[i]=t==0?0:st[t-1];
		st[t++]=i;
	}
	t=0;
	for(int i=n;i>=1;i--)
	{
		while(t>0&&a[st[t-1]]>=a[i]) t--;
		R[i]=t==0?n+1:st[t-1];
		st[t++]=i;
	}
	ll ans=-INF;
	for(int i=1;i<=n;i++)
    {
        if(a[i]<=0)
        {
            ll minx=seg.query_min(1,1,n,i,R[i]-1);
            ll maxx=seg.query_max(1,1,n,max(1,L[i]),i-1);
            if(L[i]==0) maxx=max(0LL,maxx);
            ans=max(ans,1LL*a[i]*(minx-maxx));
        }
        else
        {
            ll maxx=seg.query_max(1,1,n,i,R[i]-1);
            ll minx=seg.query_min(1,1,n,max(1,L[i]),i-1);
            if(L[i]==0) minx=min(0LL,minx);
            ans=max(ans,1LL*a[i]*(maxx-minx));
        }
    }
    printf("%lld\n",ans);
    return 0;
}
