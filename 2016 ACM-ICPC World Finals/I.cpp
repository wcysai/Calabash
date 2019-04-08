#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 105
#define MAXM 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef double db;
typedef vector<db> vec;
typedef vector<vec> mat;
const db eps=1e-8;
//minimize
bool eq(db a,db b)
{
    return fabs(a-b)<eps;
}
bool ls(db a,db b)
{
    return a<b&&!eq(a,b);
}
vec simplex(mat a)
{
    int n=(int)a.size()-1;
    int m=(int)a[0].size()-1;
    vec left(n+1),up(m+1);
    iota(up.begin(),up.end(),0);
    iota(left.begin(),left.end(),m);
    auto pivot=[&](int x,int y)
    {
        swap(left[x],up[y]);
        db k=a[x][y];
        a[x][y]=1;
        vector<int> vct;
        for(int j=0;j<=m;j++)
        {
            a[x][j]/=k;
            if(!eq(a[x][j],0)) vct.push_back(j);
        }
        for(int i=0;i<=n;i++) 
        {
            if(eq(a[i][y],0)||i==x) continue;
            k=a[i][y];
            a[i][y]=0;
            for(int j:vct) a[i][j]-=k*a[x][j];
        }
    };
    while(1)
    {
        int x=-1;
        for(int i=1;i<=n;i++) if(ls(a[i][0],0)&&(x==-1||a[i][0]<a[x][0])) x=i;
        if(x==-1) break;
        int y=-1;
        for(int j=1;j<=m;j++) if(ls(a[x][j],0)&&(y==-1||a[x][j]<a[x][y])) y=j;
        assert(y!=-1);
        pivot(x,y);
    }
    while(1)
    {
        int y=-1;
        for(int j=1;j<=m;j++) if(ls(0,a[0][j])&&(y==-1||a[0][j]>a[0][y])) y=j;
        if(y==-1) break;
        int x=-1;
        for(int i=1;i<=n;i++) if(ls(0,a[i][y])&&(x==-1||a[i][0]/a[i][y]<a[x][0]/a[x][y])) x=i;
        assert(x!=-1);
        pivot(x,y);
    }
    vector<double> ans(m+1);
    for(int i=1;i<=n;i++) if(left[i]<=m) ans[left[i]]=a[i][0];
    ans[0]=-a[0][0];
    return ans;
}
int n,m;
int main()
{
    scanf("%d",&n);
    mat e(n,vec(n)),id(n,vec(n,-1));
    vec len;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        {
            scanf("%lf",&e[i][j]);
            if(e[i][j]>0)
            {
                id[i][j]=m++;
                len.push_back(e[i][j]);
            }
        }
    auto getPath=[&](int s,int f)
    {
        vector<int> d(n,INF);
        vector<pair<int,int> > pr(n);
        vector<char> vis(n);
        d[s]=0;
        for(int it=0;it<n;it++)
        {
            int v=-1;
            for(int j=0;j<n;j++) if(!vis[j]&&(v==-1||d[j]<d[v])) v=j;
            vis[v]=1;
            for(int to=0;to<n;to++)
            {
                if(e[v][to]==-1) continue;
                if(d[to]>d[v]+e[v][to])
                {
                    d[to]=d[v]+e[v][to];
                    pr[to]={v,id[v][to]};
                }
            }
        }
        vector<db> res(m);
        while(f!=s)
        {
            res[pr[f].S]=1;
            f=pr[f].F;
        }
        return res;
    };
    mat a;
    int r;
    scanf("%d",&r);
    for(int i=0;i<m;i++)
    {
        vec cur(m+1);
        cur[0]=2*len[i]; cur[1+i]=1; a.push_back(cur);
        cur[0]=-len[i]; cur[1+i]=-1; a.push_back(cur);
    }
    for(int i=0;i<r;i++)
    {
        int s,f,t;
        scanf("%d%d%d",&s,&f,&t);
        auto cur=getPath(s,f);
        cur.insert(cur.begin(),t);
        a.push_back(cur);
        for(db &x:cur) x*=-1;
        a.push_back(cur);
    }
    int q;
    scanf("%d",&q);
    for(int i=0;i<q;i++)
    {
        int s,f;
        scanf("%d%d",&s,&f);
        auto cur=getPath(s,f);
        cur.insert(cur.begin(),0);
        auto ca=a;
        ca.insert(ca.begin(),cur);
        db res1=simplex(ca)[0];
        for(auto &x:ca[0]) x*=-1;
        db res2=-simplex(ca)[0];
        printf("%d %d %.15f %.15f\n",s,f,res2,res1);
    }
    return 0;
}

