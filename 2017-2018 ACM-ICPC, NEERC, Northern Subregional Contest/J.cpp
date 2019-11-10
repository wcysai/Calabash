#include<bits/stdc++.h>
#define MAXN 50005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef pair<int,int> pi;
typedef long double db;
typedef long long ll;
const int blocks=100;
int n,m,c[MAXN];
int a[MAXN],b[MAXN];
int adda[MAXN],addb[MAXN];
int P,Q;
struct node
{
    int pos,f,s;
};
bool cmp(node x,node y)
{
    return x.f<y.f;
}
vector<node> convex_hull[MAXN];
bool need[MAXN];
bool check(node x,node y,node z)
{
    return (db)1.0*(z.s-y.s)/(z.f-y.f)>(db)1.0*(y.s-x.s)/(y.f-x.f);
}
ll get(int id,int pos)
{
    return 1LL*Q*(convex_hull[id][pos].f+adda[id])+1LL*P*(convex_hull[id][pos].s+addb[id]);
}
void build(int id)
{
    convex_hull[id].clear();
    int st=id*blocks+1,ed=min(n,(id+1)*blocks);
    if(adda[id])
    {
        for(int i=st;i<=ed;i++) a[i]+=adda[id];
        adda[id]=0;
    }
    if(addb[id])
    {
        for(int i=st;i<=ed;i++) b[i]+=addb[id];
        addb[id]=0;
    }
    convex_hull[id].clear();
    vector<node> tmp;
    for(int i=st;i<=ed;i++) tmp.push_back((node){i,a[i],b[i]});
    sort(tmp.begin(),tmp.end(),cmp);
    for(auto p:tmp)
    {
        int t=(int)convex_hull[id].size();
        while(t>=2&&check(convex_hull[id][t-2],convex_hull[id][t-1],p))
        {
            convex_hull[id].pop_back();
            t--;
        }
        convex_hull[id].push_back(p); t++;
    }
    need[id]=false;
}
pair<int,ll> query(int id)
{
    if(need[id]) build(id);
    int t=(int)convex_hull[id].size();
    int l=-1,r=t-1;
    while(r-l>1)
    {
        int mid=(l+r)/2;
        if(get(id,mid)<get(id,mid+1)) l=mid;
        else r=mid;
    }
    return make_pair(convex_hull[id][r].pos,get(id,r));
}
void change_suffix_a(int pos,int delta)
{
    int l=pos,r=n;
    while(l<=r&&l%blocks!=1) {need[(l-1)/blocks]=true; a[l]+=delta; l++;}
    while(l<=r&&r%blocks!=0) {need[(r-1)/blocks]=true; a[r]+=delta; r--;}
    while(l<r)
    {
        adda[(l-1)/blocks]+=delta;
        l+=blocks;
    }
}
void change_suffix_b(int pos,int delta)
{
    int l=pos,r=n;
    while(l<=r&&l%blocks!=1) {need[(l-1)/blocks]=true; b[l]+=delta; l++;}
    while(l<=r&&r%blocks!=0) {need[(r-1)/blocks]=true; b[r]+=delta; r--;}
    while(l<r)
    {
        addb[(l-1)/blocks]+=delta;
        l+=blocks;
    }
}
int get_ans()
{
    ll res=-INF;
    int id=-1;
    for(int i=0;i<=(n-1)/blocks;i++)
    {
        pair<int,ll> p=query(i);
        if(p.S>res)
        {
            res=p.S;
            id=p.F;
        }
    }
    return id;
}
int main()
{
    freopen("joker.in","r",stdin);
    freopen("joker.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&c[i]);
        if(c[i]>0) P+=c[i]; else Q-=c[i];
        a[i]=a[i-1]; b[i]=b[i-1];
        if(c[i]>0) a[i]+=c[i]; else b[i]+=c[i];
    }
  //  printf("P=%d Q=%d\n",P,Q);
  //  for(int i=1;i<=n;i++) printf("%d %d %d %d\n",i,a[i],b[i],Q*a[i]+P*b[i]);
    for(int i=0;i<=(n-1)/blocks;i++) build(i);
    printf("%d\n",get_ans());
    for(int i=0;i<m;i++)
    {
        int p,v;
        scanf("%d%d",&p,&v);
        if(c[p]>0)
        {
            change_suffix_a(p,-c[p]);
            P-=c[p];
        }
        else
        {
            change_suffix_b(p,-c[p]);
            Q+=c[p];
        }
        c[p]=v;
        if(c[p]>0)
        {
            change_suffix_a(p,c[p]);
            P+=c[p];
        }
        else
        {
            change_suffix_b(p,c[p]);
            Q-=c[p];
        }
        printf("%d\n",get_ans());
    }
    return 0;
}
