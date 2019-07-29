#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAXN 300005
#define INF 1000000001
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,a[MAXN];
int bit[MAXN+1];
int pref[MAXN],preg[MAXN];
int suff[MAXN],sufg[MAXN];
int f[MAXN],g[MAXN];
int sum(int i)
{
    int s=0;
    while(i>0)
    {
        s+=bit[i];
        i-=i&-i;
    }
    return s;
}
void add(int i,int x)
{
    while(i<=n)
    {
        bit[i]+=x;
        i+=i&-i;
    }
}
void clear()
{
    memset(bit,0,sizeof(bit));
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    ll inv=0;
    for(int i=1;i<=n;i++)
    {
        pref[i]=sum(a[i]);
        preg[i]=i-1-pref[i];
        add(a[i],1);
        inv+=preg[i];
    }
    clear();
    for(int i=n;i>=1;i--)
    {
        suff[i]=sum(a[i]);
        sufg[i]=n-i-suff[i];
        add(a[i],1);
    }
    for(int i=1;i<=n;i++) f[i]=pref[i]-preg[i]+(i-1)-2*a[i];
    for(int i=n;i>=1;i--) g[i]=sufg[i]-suff[i]+(n-i)+2*a[i];
    for(int i=2;i<=n;i++) f[i]=min(f[i],f[i-1]);
    for(int i=n-1;i>=1;i--) g[i]=min(g[i],g[i+1]);
    ll ans=inv;
    for(int i=1;i<=n-1;i++)
        ans=min(ans,inv+f[i]+g[i+1]+2);
    printf("%lld\n",ans);
    return 0;
}
