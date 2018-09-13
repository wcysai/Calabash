/*************************************************************************
    > File Name: C.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-06-15 23:24:57
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define x first
#define y second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,id[MAXN],ans[MAXN];
vector<int> v;
int abx(int x) 
{
    return x<0?360+x:x;
}
struct node
{
    P p[MAXN];
    int q[MAXN],val[MAXN];
    int pre[MAXN],suf[MAXN];
    void init()
    {
        for(int i=0;i<n;i++)
        {
            pre[i]=(i-1+n)%n;
            suf[i]=(i+1)%n;
        }
        for(int i=0;i<n;i++)
            q[p[i].y]=i;
    }
    void del(int i)
    {
        i=q[i];
        suf[pre[i]]=suf[i];
        pre[suf[i]]=pre[i];
    }
    void update(int i)
    {
        if(p[pre[i]].x==p[i].x||p[suf[i]].x==p[i].x) val[i]=0;
        else val[i]=(abx(p[i].x-p[pre[i]].x)+abx(p[suf[i]].x-p[i].x));
        //printf("update %d %d %d %d\n",p[i].x,p[pre[i]].x,p[suf[i]].x,val[i]);
    }
    int find_val(int i)
    {
        return val[q[i]];
    }
    void modify(int i)
    {
        i=q[i];
        update(pre[i]);
        update(suf[i]);
        v.push_back(p[pre[i]].y);v.push_back(p[suf[i]].y);
    }
}r,g,b;
map<int,int> mp;
set<P> s;
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d%d%d%d",&r.p[i].x,&g.p[i].x,&b.p[i].x,&id[i]);
        r.p[i].y=g.p[i].y=b.p[i].y=i;
        mp[id[i]]=i;
    }
    //puts("");
    sort(r.p,r.p+n);sort(g.p,g.p+n);sort(b.p,b.p+n);
    r.init();g.init();b.init();
    for(int i=0;i<n;i++)
        r.update(i),g.update(i),b.update(i);
    for(int i=0;i<n;i++)
    {
        ans[i]=r.find_val(i)+g.find_val(i)+b.find_val(i);
        s.insert(P(ans[i],-id[i]));
    }
   /* puts("");
    for(int i=0;i<n;i++)
        printf("%d %d %d\n",r.find_val(i),g.find_val(i),b.find_val(i));
    puts("");*/
    for(int i=0;i<n;i++)
    {
        auto it=s.begin();
        int o=mp[-(it->y)];
        printf("%d\n",-(it->y));
        s.erase(s.begin());
        r.del(o);g.del(o);b.del(o);
        v.clear();
        r.modify(o);g.modify(o);b.modify(o);
        for(int j=0;j<(int)v.size();j++)
        {
            int t=v[j];
            if(s.count(P(ans[t],-id[t]))) s.erase(P(ans[t],-id[t]));
        }
        for(int j=0;j<(int)v.size();j++)
        {
            int t=v[j];
            ans[t]=r.find_val(t)+g.find_val(t)+b.find_val(t);
            s.insert(P(ans[t],-id[t]));
        }
    }
    return 0;
}
