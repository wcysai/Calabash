#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,a[MAXN],b[MAXN],f[MAXN];
int bit[2*MAXN+1];
vector<int> v;
int sum(int i)
{
    int s=0;
    while(i>0)
    {
        s=max(s,bit[i]);
        i-=i&-i;
    }
    return s;
}
void add(int i,int x)
{
    while(i<=2*n+1)
    {
        if(x==-1) bit[i]=0;
        else bit[i]=max(bit[i],x);
        i+=i&-i;
    }
}
struct node
{
    int x,y,val;
};
bool cmp(node p,node q)
{
    return p.x<q.x;
}
vector<node> v1,v2;
void solve(int l,int r)
{
    if(l==r)
    {
        f[l]=max(f[l],1);
        return;
    }
    int mid=(l+r)/2;
    solve(l,mid); 
    v1.clear();v2.clear();
    for(int i=l;i<=mid;i++) v1.push_back((node){a[i],b[i],f[i]});
    for(int i=mid+1;i<=r;i++) v2.push_back((node){a[i],b[i],i});
    sort(v1.begin(),v1.end(),cmp); sort(v2.begin(),v2.end(),cmp);
    int now=0;
    for(int i=0;i<(int)v2.size();i++)
    {
        while(now<(int)v1.size()&&v1[now].x<v2[i].x) {add(v1[now].y,v1[now].val); now++;}
        f[v2[i].val]=max(f[v2[i].val],sum(v2[i].y-1)+1);
    }
    for(int i=0;i<now;i++) add(v1[i].y,-1);
    solve(mid+1,r);
    //printf("%d %d\n",l,r);
    //for(int i=l;i<=r;i++) printf("%d%c",pre[i],i==r?'\n':' ');
    //for(int i=l;i<=r;i++) printf("%d%c",suf[i],i==r?'\n':' ');
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);v.clear();for(int i=1;i<=n;i++) f[i]=0;
        for(int i=1;i<=n;i++) {scanf("%d",&a[i]); v.push_back(a[i]);}
        for(int i=1;i<=n;i++) {scanf("%d",&b[i]); v.push_back(b[i]);}
        sort(v.begin(),v.end());
        v.erase(unique(v.begin(),v.end()),v.end());
        for(int i=1;i<=n;i++) a[i]=lower_bound(v.begin(),v.end(),a[i])-v.begin()+1;
        for(int i=1;i<=n;i++) b[i]=lower_bound(v.begin(),v.end(),b[i])-v.begin()+1;
        solve(1,n);
        int ans=0;
        for(int i=1;i<=n;i++) ans=max(ans,f[i]);
        printf("%d\n",ans);
    }
    return 0;
}

