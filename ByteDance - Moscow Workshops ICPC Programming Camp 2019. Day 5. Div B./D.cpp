#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 35
#define MAXM 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
int n;
ll L,R;
ll w[MAXN],v[MAXN];
struct node
{
    ll weight;
    ll value;
    int mask;
    bool operator <(const node& p) const
    {
        if(weight!=p.weight) return weight<p.weight;
        return value<p.value;
    }
};
vector<node> v1,v2;
P st[MAXM][18];
ll pre[MAXM];
P query(int l,int r)
{
    int len=r-l+1,k=pre[len];
    return max(st[l][k],st[r-(1<<k)+1][k]);
}
int main()
{
    scanf("%d%lld%lld",&n,&L,&R);
    for(int i=0;i<n;i++) scanf("%lld%lld",&w[i],&v[i]);
    for(int i=0;i<(1<<(n/2));i++)
    {
        ll sumw=0,sumv=0;
        for(int j=0;j<n/2;j++)
        {
            if(i&(1<<j))
            {
                sumw+=w[j];
                sumv+=v[j];
            }
        }
        v1.push_back((node){sumw,sumv,i});
    }
    for(int i=0;i<(1<<(n-n/2));i++)
    {
        ll sumw=0,sumv=0;
        for(int j=0;j<(n-n/2);j++)
        {
            if(i&(1<<j))
            {
                sumw+=w[n/2+j];
                sumv+=v[n/2+j];
            }
        }
        v2.push_back((node){sumw,sumv,i});
    }
    sort(v1.begin(),v1.end());sort(v2.begin(),v2.end());
    int sz=(int)v2.size();
    pre[1]=0;
    for(int i=2;i<=sz;i++) 
    {
        pre[i]=pre[i-1];
        if((1<<(pre[i]+1))==i) pre[i]++;
    }
    for(int i=sz-1;i>=0;i--)
    {
        st[i][0]=P(v2[i].value,v2[i].mask);
        for(int j=1;(i+(1<<j)-1)<sz;j++)
            st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
    }
    ll ans=-1;
    int mask1=-1,mask2=-1;
    for(int i=0;i<(int)v1.size();i++)
    {
        if(v1[i].weight>R) break;
        int l=lower_bound(v2.begin(),v2.end(),(node){L-v1[i].weight,0,0})-v2.begin();
        int r=upper_bound(v2.begin(),v2.end(),(node){R-v1[i].weight+1,0,0})-v2.begin();
        r--;
        if(l>r) continue;
        P res=query(l,r);
        if(v1[i].value+res.F>ans)
        {
            ans=v1[i].value+res.F;
            mask1=v1[i].mask;
            mask2=res.S;
        }
    }
    if(mask1==-1) {puts("0"); return 0;}
    int cnt=0;
    for(int i=0;i<(n/2);i++) if(mask1&(1<<i)) cnt++;
    for(int i=0;i<(n-n/2);i++) if(mask2&(1<<i)) cnt++;
    printf("%d\n",cnt);
    for(int i=0;i<(n/2);i++) if(mask1&(1<<i)) printf("%d ",i+1);
    for(int i=0;i<(n-n/2);i++) if(mask2&(1<<i)) printf("%d ",n/2+i+1);
    return 0;
}

