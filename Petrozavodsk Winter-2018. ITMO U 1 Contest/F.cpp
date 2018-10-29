/*************************************************************************
    > File Name: F.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-10-26 14:36:44
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 2005
#define MAXM 12
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,MOD,a[MAXN],p[MAXN],f[MAXN];
int dp[MAXN][MAXN];
int d[12],tot;
map<int,int> mp;
int get_hash(vector<int> &a)
{
    int cur=0;
    for(int i=0;i<(int)a.size();i++) cur=cur*10+a[i];
    return cur;
}
void cnn(vector<int> &a)
{
    map<int,int> nmp;nmp.clear();int tot=0;
    for(auto it:a) 
        if(it!=0) 
        {
            if(nmp.find(it)!=nmp.end()) nmp[it]=++tot;
        }
    for(int i=0;i<(int)a.size();i++)
        if(a[i]!=0) a[i]=nmp[a[i]];
}
int find(int x)
{
    if(p[x]==x) return x;
    return p[x]=find(p[x]);
}
void unite(int x,int y)
{
    x=find(x);y=find(y);
    if(x==y) return;
    p[x]=y;
}
void add_case()
{
    for(int i=1;i<=m;i++) p[i]=i,f[i]=a[i];
    for(int i=1;i<=m;i++) if(i>1&&f[i]&&f[i-1]) unite(i,i-1);
    for(int i=1;i<=m;i++) if(f[i]) f[i]=f[find(i)];
    for(int i=1;i<=m;i++) printf("%d%c",f[i],i==m?'\n':' ');
    vector<int> v;
    for(int i=1;i<=m;i++) v.push_back(f[i]);
    cnn(v); int h=get_hash(v);
    if(mp.find(h)==mp.end()) mp[h]=++tot;
}
vector<int> valid;
vector<int> states[1<<20];
void gen()
{
    for(int i=0;i<(1<<m);i++)
    {
        for(int j=0;j<m-1;j++)
            if((i&(1<<j))==0)&&(i&(1<<(j+1))==0))
    }
    for(int i=0;i<(1<<m);i++)
    {

        for(int j=0;j<(1<<m);j++)
        {
            for(int k=0;k<m;k++)
            {
                if(i&(1<<k))
            }
        }
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&MOD);
    printf("%d\n",tot);
    return 0;
}

