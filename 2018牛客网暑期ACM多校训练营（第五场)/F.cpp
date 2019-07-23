/*************************************************************************
    > File Name: F.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-08-02 12:32:22
 ************************************************************************/
 
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,d[MAXN],p[MAXN],E[MAXN];
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
struct segtree
{
    int val[4*MAXN];
    void build(int k,int l,int r)
    {
        val[k]=1;
        if(l==r) return;
        int mid=(l+r)/2;
        build(k*2,l,mid);build(k*2+1,mid+1,r);
    }
    void update(int k,int l,int r,int pos,int x)
    {
        if(l==r)
        {
            val[k]=x;
            return;
        }
        int mid=(l+r)/2;
        if(pos<=mid) update(k*2,l,mid,pos,x);
        else update(k*2+1,mid+1,r,pos,x);
        val[k]=1LL*val[k*2]*val[k*2+1]%MOD;
    }
    int query(int k,int l,int r,int x,int y)
    {
        if(x>r||l>y) return 1;
        if(l>=x&&r<=y) return val[k];
        int mid=(l+r)/2;
        int lval=query(k*2,l,mid,x,y);
        int rval=query(k*2+1,mid+1,r,x,y);
        return 1LL*lval*rval%MOD;
    }
}seg;
vector<int> v;
int main()
{
    int rev=pow_mod(100,MOD-2);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&p[i],&d[i]);
        p[i]=1LL*rev*p[i]%MOD;
        v.push_back(d[i]);
    }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    seg.build(1,1,n);
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        E[i]=p[i];
        int pos=lower_bound(v.begin(),v.end(),d[i])-v.begin()+1;
        int res=seg.query(1,1,n,pos,n);
        //printf("%d %d %d ",pos,mult,res);
        E[i]=1LL*E[i]*res%MOD;
        ans=(ans+E[i])%MOD;
        int pp=(1-p[i]+MOD)%MOD;//printf("%d\n",pp);
        seg.update(1,1,n,pos,pp);
    }
    printf("%d\n",ans);
    return 0;
}
