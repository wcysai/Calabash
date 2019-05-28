#include<bits/stdc++.h>
#define MAXN 105
#define MAXM 20005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int V,E,k1,b1,s1,k2,b2,s2;
int h1[MAXN],h2[MAXN],d[MAXM];
int from[MAXM],to[MAXM],cost[MAXM];
void add_edge(int u,int v,int c)
{
    from[E]=u; to[E]=v; cost[E]=c;
    E++;
}
bool bellman_ford(int s)
{
    for(int i=0;i<V;i++) d[i]=INF;
    d[s]=0;
    int cnt=0;
    while(true)
    {
        bool update=false;
        for(int i=0;i<E;i++)
        {
            if(d[from[i]]!=INF&&d[to[i]]>d[from[i]]+cost[i])
            {
                d[to[i]]=d[from[i]]+cost[i];
                update=true;
            }
        }
        if(!update) return true;
        cnt++;
        if(cnt>E) return false;
    }
}
vector<int> v;
void make_equal(int l,int r,int x)
{
    l=lower_bound(v.begin(),v.end(),l)-v.begin();
    r=lower_bound(v.begin(),v.end(),r)-v.begin();
    add_edge(l,r,x); add_edge(r,l,-x);
}
int main()
{
    scanf("%d%d%d",&k1,&b1,&s1);
    for(int i=1;i<=k1;i++) scanf("%d",&h1[i]);
    scanf("%d%d%d",&k2,&b2,&s2);
    for(int i=1;i<=k2;i++) scanf("%d",&h2[i]);
    for(int i=1;i<=k1;i++) 
    {
        int l=b1+(i-1)*s1-1,r=b1+i*s1-1;
        v.push_back(l); v.push_back(r);
    }
    for(int i=1;i<=k2;i++)
    {
        int l=b2+(i-1)*s2-1,r=b2+i*s2-1;
        v.push_back(l); v.push_back(r);
    }
    v.push_back(0); v.push_back(b1-1); v.push_back(b2-1);
    v.push_back(10001);
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    make_equal(0,b1-1,0); make_equal(0,b2-1,0);
    make_equal(b1+k1*s1-1,10001,0); make_equal(b2+k2*s2-1,10001,0);
    V=(int)v.size()+1;
    for(int i=0;i<(int)v.size();i++) add_edge(V-1,i,0);
    for(int i=1;i<(int)v.size();i++) add_edge(i,i-1,0);
    for(int i=1;i<=k1;i++)
    {
        int l=b1+(i-1)*s1-1,r=b1+i*s1-1;
        make_equal(l,r,h1[i]);
    }
    for(int i=1;i<=k2;i++)
    {
        int l=b2+(i-1)*s2-1,r=b2+i*s2-1;
        make_equal(l,r,h2[i]);
    }
    if(bellman_ford(V-1)) puts("Yes"); else puts("No");
    return 0;
}
