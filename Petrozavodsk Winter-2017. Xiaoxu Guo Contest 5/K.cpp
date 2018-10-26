#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
int n,m;
int p2[MAXN];
int k[MAXN],cur[MAXN],lv[MAXN],ord[MAXN];
struct segtree
{
    int cnt[4*MAXN],sum[4*MAXN];
    void build(int k,int l,int r)
    {
        if(l==r) {cnt[k]=cur[l]; sum[k]=p2[cnt[k]]-1; return;}
        int mid=(l+r)/2;
        build(k*2,l,mid);build(k*2+1,mid+1,r);
        pushup(k);
    }
    void pushup(int k)
    {
        cnt[k]=cnt[k*2]+cnt[k*2+1];if(cnt[k]>=MOD) cnt[k]-=MOD;
        sum[k]=sum[k*2]+sum[k*2+1];if(sum[k]>=MOD) sum[k]-=MOD;
    }
    void update(int k,int l,int r,int p)
    {
        if(l==r) {cnt[k]=cur[l]; sum[k]=p2[cnt[k]]-1; return;}
        int mid=(l+r)/2;
        if(p<=mid) update(k*2,l,mid,p); else update(k*2+1,mid+1,r,p);
        pushup(k);
    }
    int query(int k,int l,int r,int x,int y)
    {
        if(l>y||x>r) return 0;
        if(l>=x&&r<=y) return sum[k];
        int mid=(l+r)/2;
        int ans=query(k*2,l,mid,x,y);
        add(ans,query(k*2+1,mid+1,r,x,y));
        return ans;
    }
}seg;
int main()
{
    p2[0]=1;
    for(int i=1;i<=200000;i++) p2[i]=2LL*p2[i-1]%MOD;
    while(scanf("%d%d",&n,&m)!=EOF) {
        for (int i = 1; i <= m; i++) lv[i] = INF;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &k[i]);
            for (int j = 1; j <= k[i]; j++) {
                int x;
                scanf("%d", &x);
                lv[x] = min(lv[x], j);
            }
        }
        for(int i=1;i<=m;i++) cur[i]=0;
        for (int i = 1; i <= m; i++) if (lv[i] != INF) cur[lv[i]]++;
        seg.build(1, 1, m);
        int ans = 1;
        for (int i=1;i<=m;i++) scanf("%d",&ord[i]);
        for (int i=1;i<=m;i++)
        {
            int x=lv[ord[i]];
            if(x==INF) add(ans,seg.query(1,1,m,1,m)+1);
            else
            {
                add(ans,seg.query(1,1,m,1,x-1)+1);
                cur[x]--;
                add(ans,p2[cur[x]]-1);
                seg.update(1,1,m,x);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
