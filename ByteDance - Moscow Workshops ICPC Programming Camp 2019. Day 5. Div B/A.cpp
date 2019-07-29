#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 35
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
struct box
{
    int a,b,c,it;
};
bool cmp(box p,box q)
{
    if(p.a!=q.a) return p.a>q.a;
    if(p.b!=q.b) return p.b>q.b;
    return p.c>q.c;
}
int n,ans;
box p[MAXN];
vector<P> v;
vector<P> best;
void solve(int now,int x,int y,int h)
{
    if(now==n+1) 
    {
        if(h>ans)
        {
            ans=h;
            best=v;
        }
        return;
    }
    int res=h;
    for(int i=now;i<=n;i++)
    {
        int cur=0;
        if((p[i].a<=x&&p[i].b<=y)||(p[i].a<=y&&p[i].b<=x)) cur=max(cur,p[i].c);
        if((p[i].b<=x&&p[i].c<=y)||(p[i].b<=y&&p[i].c<=x)) cur=max(cur,p[i].a);
        if((p[i].c<=x&&p[i].a<=y)||(p[i].c<=y&&p[i].a<=x)) cur=max(cur,p[i].b);
        res+=cur;
    }
    if(res<=ans) return;
    solve(now+1,x,y,h);
    if((p[now].a<=x&&p[now].b<=y)||(p[now].a<=y&&p[now].b<=x)) 
    {
        v.push_back(P(now,p[now].c));
        solve(now+1,p[now].a,p[now].b,h+p[now].c);
        v.pop_back();
    }
    if((p[now].b<=x&&p[now].c<=y)||(p[now].b<=y&&p[now].c<=x)) 
    {
        v.push_back(P(now,p[now].a));
        solve(now+1,p[now].b,p[now].c,h+p[now].a);
        v.pop_back();
    }
    if((p[now].a<=x&&p[now].c<=y)||(p[now].a<=y&&p[now].c<=x)) 
    {
        v.push_back(P(now,p[now].b));
        solve(now+1,p[now].a,p[now].c,h+p[now].b);
        v.pop_back();
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) 
    {
        scanf("%d%d%d",&p[i].a,&p[i].b,&p[i].c);
        p[i].it=i;
    }
    sort(p+1,p+n+1,cmp);
    solve(1,INF,INF,0);
    printf("%d\n",ans);
    printf("%d\n",(int)best.size());
    int x=INF,y=INF;
    for(auto pp:best)
    {
        int id=pp.F;
        if(pp.S==p[id].b) swap(p[id].b,p[id].c);
        else if(pp.S==p[id].a) swap(p[id].a,p[id].c);
        printf("%d ",p[id].it);
        if(p[id].a<=x&&p[id].b<=y)
        {
            printf("%d %d %d\n",p[id].a,p[id].b,p[id].c);
            x=p[id].a;y=p[id].b;
        }
        else
        {
            printf("%d %d %d\n",p[id].b,p[id].a,p[id].c);
            x=p[id].b;y=p[id].a;
        }
    }
    return 0;
}

