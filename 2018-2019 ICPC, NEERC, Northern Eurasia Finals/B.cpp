#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int V,n,m,x,y,fore,rear,cnt,ans,father[MAXN],f[MAXN],path[MAXN],tra[MAXN],que[MAXN],match[MAXN];
bool a[MAXN][MAXN],check[MAXN],treec[MAXN],pathc[MAXN];
inline void push(int x)
{
    que[++rear]=x;
    check[x]=true;
    if(!treec[x])
    {
        tra[++cnt]=x;
        treec[x]=true;
    }
}
int root(int x) {return f[x]?f[x]=root(f[x]):x;}
void clear()
{
    for(int i=1,j;i<=cnt;++i)
    {
        j=tra[i];
        check[j]=treec[j]=false;
        father[j]=0,f[j]=0;
    }
}
int lca(int u,int v)
{
    int len=0;
    for(;u;u=father[match[u]])
    {
        u=root(u);
        path[++len]=u;
        pathc[u]=true;
    }
    for(;;v=father[match[v]])
    {
        v=root(v);
        if(pathc[v]) break;
    }
    for(int i=1;i<=len;++i)
    {
        pathc[path[i]]=false;
    }
    return v;
}
void reset(int u,int p)
{
    for(int v;root(u)!=p;)
    {
        if(!check[v=match[u]]) push(v);
        if(f[u]==0) f[u]=p;
        if(f[v]==0) f[v]=p;
        u=father[v];
        if(root(u)!=p) father[u]=v;
    }
}
void flower(int u,int v)
{
    int p=lca(u,v);
    if(root(u)!=p) father[u]=v;
    if(root(v)!=p) father[v]=u;
    reset(u,p);reset(v,p);
}
bool find(int x)
{
    fore=rear=cnt=0,push(x);
    while(fore++<rear)
    {
        int i=que[fore];
        for(int j=1;j<=V;j++)
        {
            if(a[i][j]&&root(i)!=root(j)&&match[j]!=i)
                if(match[j]&&father[match[j]])
                    flower(i,j);
                else if(father[j]==0)
                {
                    father[j]=i;
                    tra[++cnt]=j;
                    treec[j]=true;
                    if(match[j]) push(match[j]);
                    else
                    {
                        for(int k=i,l=j,p;k;l=p,k=father[l])
                        {
                            p=match[k];
                            match[k]=l;
                            match[l]=k;
                        }
                        return true;
                    }
                }
        }
    }
    return false;
}
int t;
void matching()
{
    for(int i=1;i<=V;i++)
        if(match[i]==0)
        {
            if(find(i)) ans++;
            clear();
        }
}
//1..m: ladies
//m+1..m+n cavalier 1
//m+n+1..m+2n cavalier 2
void add_edge(int u,int v) {a[u][v]=a[v][u]=true;}
char mp[200][200];
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);V=2*n+m;
        memset(a,false,sizeof(a));
        for(int i=1;i<=n;i++) add_edge(m+i,m+n+i);
        for(int i=1;i<=n;i++)
        {
            scanf("%s",mp[i]+1);
            for(int j=1;j<=m;j++)
            {
                int x;
                if(mp[i][j]=='1') {add_edge(j,m+i); add_edge(j,m+n+i);}
            }
        }
        cnt=0;fore=0;rear=0;
        memset(match,0,sizeof(match));
        memset(father,0,sizeof(father));
        memset(f,0,sizeof(f));
        memset(path,0,sizeof(path));
        memset(tra,0,sizeof(tra));
        memset(que,0,sizeof(que));
        ans=0;
        matching();
        printf("%d\n",ans-n);
    }
    return 0;
}
