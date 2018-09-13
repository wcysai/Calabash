/*************************************************************************
    > File Name: J.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-07-28 14:57:11
 ************************************************************************/
 
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 400005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,a[MAXN],sum[MAXN];
int p[MAXN],rk[MAXN];
P pos[MAXN];
bool used[MAXN];
P merge(P x,P y)
{
    //if(x.F>=n&&x.S>=n) x.F-=n,x.S-=n;
    //if(y.F>=n&&y.S>=n) y.F-=n,y.S-=n;
    if(x.F>y.F) swap(x,y);
    if(x.S+1==y.F) return P(x.F,y.S);
    x.F+=n;x.S+=n; assert(y.S+1==x.F); return P(y.F,x.S);
}
void init(int n)
{
    for(int i=0;i<n;i++)
    {
        p[i]=i;
        rk[i]=0;
        pos[i].F=pos[i].S=i;
        used[i]=false;
    }
}
int find(int x)
{
    if(p[x]==x) return x;
    else return p[x]=find(p[x]);
}
void unite(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x==y) return;
    if(rk[x]<rk[y])
    {
        p[x]=y;
        pos[y]=merge(pos[x],pos[y]);
    }
    else
    {
        p[y]=x;
        if(rk[x]==rk[y]) rk[x]++;
        pos[x]=merge(pos[x],pos[y]);
    }
}
bool same(int x,int y)
{
    return find(x)==find(y);
}
void update(int x)
{
    used[x]=true;int t=x;
    x=find(x);
    int lastpos=(pos[x].F%n-1+n)%n;
    while(used[lastpos])
    {
        if(same(x,lastpos)) break;
        //printf("united%d %d\n",x,lastpos);
        unite(x,lastpos);
        x=find(x),lastpos=(pos[x].F%n-1+n)%n;
        //printf("%d %d\n",pos[x].F,pos[x].S);
    }
    x=find(t);
    int edpos=(pos[x].S+1)%n;
    while(used[edpos])
    {
        if(same(x,edpos)) break;
        //printf("unite%d %d\n",x,edpos);
        unite(x,edpos);
        x=find(x),edpos=(pos[x].S%n+1)%n;
    }
}
int main()
{
    scanf("%d",&t);
    set<P> s;
    vector<int> ans;
    while(t--)
    {
        s.clear();ans.clear();
        scanf("%d",&n);
        int cnt=0;
        init(n);
        for(int i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
            if(a[i]==-1) continue;
            cnt++;
            if(a[i]%n==i) {s.insert(P(a[i],i));}
        }
        bool f=true;
        for(int i=0;i<cnt;i++)
        {
            if(s.size()==0) {f=false; break;}
            P p=*(s.begin());
            s.erase(s.begin());
            ans.push_back(p.F);
            if(i==cnt-1) break;
            update(p.S);
            int x=find(p.S);
            int edpos=(pos[x].S%n+1)%n;
            if(used[a[edpos]%n]&&same(a[edpos]%n,(edpos-1+n)%n)) s.insert(P(a[edpos],edpos));
        }
        if(f)
        {
            for(int i=0;i<(int)ans.size();i++)
            {
                if(i==(int)ans.size()-1) printf("%d",ans[i]);
                else printf("%d ",ans[i]);
            }
            puts("");
        }
        else puts("-1");
    }
    return 0;
}
