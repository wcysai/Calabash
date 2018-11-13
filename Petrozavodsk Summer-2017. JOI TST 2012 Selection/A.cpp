/*************************************************************************
    > File Name: A.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-11-13 14:28:07
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef vector<int> vec;
typedef long long ll;
typedef pair<int,int> P;
int n,h[MAXN],ans;
vector<int> G[MAXN];
vector<int> up[MAXN],down[MAXN];
void merge_up(vec &a, vec &b)
{
    if((int)a.size()<(int)b.size()) swap(a,b);
    for(int i=0;i<(int)b.size();i++) a[i]=min(a[i],b[i]);
}
void merge_down(vec &a,vec &b)
{
    if((int)a.size()<(int)b.size()) swap(a,b);
    for(int i=0;i<(int)b.size();i++) a[i]=max(a[i],b[i]);
}
void calc(vec &a, vec &b,int mid)//a: up b:down
{
    if((int)a.size()<(int)b.size())
    {
        for(int i=0;i<(int)a.size();i++)
        {
            int pos=lower_bound(b.begin(),b.end(),a[i],greater<int>())-b.begin()-1;
            ans=max(ans,i+pos);
            if(a[i]<mid)
            {
                int pos=lower_bound(b.begin(),b.end(),mid,greater<int>())-b.begin()-1;
                ans=max(ans,i+pos+1);
            }
        }
    }
    else
    {
        for(int i=0;i<(int)b.size();i++)
        {
            int pos=lower_bound(a.begin(),a.end(),b[i])-a.begin()-1;
            ans=max(ans,i+pos);
            if(b[i]>mid)
            {
                int pos=lower_bound(a.begin(),a.end(),mid)-a.begin()-1;
                ans=max(ans,i+pos+1);
            }
        }
    }
}
void dfs(int v,int p)
{
    up[v].push_back(0);down[v].push_back(INF);
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i];
        if(to==p) continue;
        dfs(to,v);
        calc(up[to],down[v],h[v]);
        calc(up[v],down[to],h[v]);
        merge_up(up[v],up[to]);merge_down(down[v],down[to]);
    }
    int pos=lower_bound(up[v].begin(),up[v].end(),h[v])-up[v].begin();
    if(pos==(int)up[v].size()) up[v].push_back(h[v]); else up[v][pos]=h[v];
    pos=lower_bound(down[v].begin(),down[v].end(),h[v],greater<int>())-down[v].begin();
    if(pos==(int)down[v].size()) down[v].push_back(h[v]); else down[v][pos]=h[v];
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&h[i]);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);G[v].push_back(u);
    }
    dfs(1,0);printf("%d\n",ans);
    return 0;
}

