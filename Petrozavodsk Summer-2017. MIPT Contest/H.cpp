#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define y1 dsaijdfosai
#define x1 saoipjfdpiosa
#define x2 fdjfiosdk
#define y2 djaksiofjsd
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct segtree
{
    int sum[4*MAXN];
    bool rev[4*MAXN];
    void pushup(int k) {sum[k]=sum[k*2]+sum[k*2+1];}
    void pushdown(int k,int l,int r)
    {
        if(!rev[k]) return;
        int mid=(l+r)/2;
        rev[k*2]=!rev[k*2];sum[k*2]=(mid-l+1)-sum[k*2];
        rev[k*2+1]=!rev[k*2+1];sum[k*2+1]=(r-mid)-sum[k*2+1];
        rev[k]=false;
    }
    void build(int k,int l,int r)
    {
        sum[k]=0;rev[k]=false;
        if(l==r) return;
        int mid=(l+r)/2;
        build(k*2,l,mid);build(k*2+1,mid+1,r);
    }
    void update(int k,int l,int r,int x,int y)
    {
        if(x>r||l>y) return;
        if(l>=x&&r<=y)
        {
            rev[k]=!rev[k];
            sum[k]=(r-l+1)-sum[k];
            return;
        }
        pushdown(k,l,r);
        int mid=(l+r)/2;
        update(k*2,l,mid,x,y);update(k*2+1,mid+1,r,x,y);
        pushup(k);
    }
    int query(int k,int l,int r,int x,int y)
    {
        if(x>r||l>y) return 0;
        if(l>=x&&r<=y) return sum[k];
        pushdown(k,l,r);
        int mid=(l+r)/2;
        return query(k*2,l,mid,x,y)+query(k*2+1,mid+1,r,x,y);
    }
}seg;
int n,m,q;
int x1,y1,x2,y2;
struct query
{
    int l,r;
};
vector<query> qq[MAXN];
int row[MAXN],col[MAXN];
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=0;i<q;i++)
    {
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        if((x2-x1+1)&1) {col[y1]++; col[y2+1]--;}
        if((y2-y1+1)&1) {row[x1]++; row[x2+1]--;}
        qq[x1].push_back((query){y1,y2});
        qq[x2+1].push_back((query){y1,y2});
    }
    int hodd=0,heven=0,vodd=0,veven=0;
    for(int i=1;i<=n;i++) {row[i]+=row[i-1]; if(row[i]&1) hodd++; else heven++;}
    for(int i=1;i<=m;i++) {col[i]+=col[i-1]; if(col[i]&1) vodd++; else veven++;}
    ll ans=0;
    seg.build(1,1,m);
    for(int i=1;i<=n;i++)
    {
        for(auto op:qq[i]) seg.update(1,1,m,op.l,op.r);
        ans+=seg.query(1,1,m,1,m);
    }
    if(vodd==0&&hodd==0)
    {
        printf("%lld\n",ans);
        return 0;
    }
    else if(veven==0&&heven==0)
    {
        printf("%lld\n",ans);
        return 0;
    }
    else if(n%2==1&&m%2==1)
    {
        puts("-1");
    }
    else if(n%2==0&&m%2==0)
    {
        ans+=1LL*hodd*veven+1LL*heven*vodd;
        if((hodd+vodd)&1) ans+=1LL*n*m;
        printf("%lld\n",ans);
    }
    else
    {
        ans+=1LL*hodd*veven+1LL*heven*vodd;
        if(n%2==0)
        {
            swap(n,m);
            swap(heven,veven);
            swap(hodd,vodd);
        }
        if(veven!=0&&veven!=m) puts("-1");
        else
        {
            if(veven==0)
            {
                if(heven&1) puts("-1");
                else printf("%lld\n",ans);
            }
            else
            {
                if(hodd&1) puts("-1");
                else printf("%lld\n",ans);
            }
        }
    }
    return 0;
}
