#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 2000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const int blocks=1200;
int tot,tcnt,qid;
struct query
{
    int l,r,ti,id;
}Q[MAXM];
int n,q,cnt[MAXM],a[MAXN],b[MAXN],sum[MAXN];
P change[MAXN];
ll ans,res[MAXN];
bool cmp(query x,query y)
{
    if(x.l/blocks!=y.l/blocks) return x.l/blocks<y.l/blocks;
    if(x.r/blocks!=y.r/blocks) return x.r/blocks<y.r/blocks;
    if(x.r/blocks&1) return x.ti>y.ti; else return x.ti<y.ti;
}
void add(int pos)
{
    ans+=cnt[sum[pos]];
    cnt[sum[pos]]++;
}
void del(int pos)
{
    cnt[sum[pos]]--;
    ans-=cnt[sum[pos]];
}
void modify(int ti,int num)
{
    if(change[ti].F>=Q[num].l&&change[ti].F<=Q[num].r)
    {
        cnt[sum[change[ti].F]]--;
        ans-=cnt[sum[change[ti].F]];
        ans+=cnt[change[ti].S];
        cnt[change[ti].S]++;
    }
    swap(sum[change[ti].F],change[ti].S);
}
int main()
{
    while(scanf("%d%d",&n,&q)==2)
    {
        ans=0;
        for(int i=1;i<=n;i++) scanf("%d",&a[i]),b[i]=a[i];
        for(int i=1;i<=n;i++) sum[i]=sum[i-1]^a[i];
        memset(cnt,0,sizeof(cnt));
        tot=tcnt=qid=0;
        for(int i=1;i<=q;i++)
        {
            int type,l,r;
            scanf("%d%d",&type,&l);
            if(type==1) scanf("%d",&r),Q[++tot]=(query){l-1,r,tcnt,++qid};
            else
            {
                sum[l]^=a[l]; sum[l]^=a[l+1];
                change[++tcnt]=P(l,sum[l]);
                swap(a[l],a[l+1]);
            }
        }
        for(int i=1;i<=n;i++) sum[i]=sum[i-1]^b[i];
        sort(Q+1,Q+tot+1,cmp);
        int l=1,r=0,ti=0;
        for(int i=1;i<=tot;i++)
        {
            while(l>Q[i].l) add(--l);
            while(l<Q[i].l) del(l++);
            while(r<Q[i].r) add(++r);
            while(r>Q[i].r) del(r--);
            while(ti<Q[i].ti) modify(++ti,i);
            while(ti>Q[i].ti) modify(ti--,i);
            int len=Q[i].r-Q[i].l+1;
            res[Q[i].id]=1LL*len*(len-1)/2-ans;
        }
        for(int i=1;i<=qid;i++) printf("%lld\n",res[i]);
    }
    return 0;
}
