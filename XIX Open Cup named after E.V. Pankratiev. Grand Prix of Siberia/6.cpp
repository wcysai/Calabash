#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 205
#define INF 1e12
#define MOD 1000000007
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
int n;
double v;
double x[MAXN],y[MAXN],p[MAXN];
double d[2*MAXN][2*MAXN];
void add_edge(int u,int v,double w)
{
    d[u][v]=min(d[u][v],w);
}
double dist2(int i,int j)
{
    return (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
}
double dist(int i,int j)
{
    return sqrt(dist2(i,j));
}
void floyd_warshall()
{
    for(int k=1;k<=2*n;k++)
        for(int i=1;i<=2*n;i++)
          for(int j=1;j<=2*n;j++) d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
}
int main()
{
    scanf("%d%lf",&n,&v);
    for(int i=1;i<=n;i++)
    {
        scanf("%lf%lf%lf",&x[i],&y[i],&p[i]);
    }
    for(int i=1;i<=2*n;i++)
        for(int j=1;j<=2*n;j++)
            d[i][j]=(i==j?0:INF);
    for(int i=1;i<=n;i++) add_edge(i,n+i,v*p[i]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(i==j) continue;
            if(v*v>=dist2(i,j)) add_edge(i,j,dist(i,j)*p[i]);
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(i==j) continue;
            if(v*v>=dist2(i,j)) add_edge(n+i,n+j,dist(i,j)*p[j]);
        }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(i==j) continue;
            for(int k=1;k<=n;k++)
            {
                if(k==i||k==j) continue;
                if(v*v>=dist2(i,k)&&v*v>=dist2(k,j)&&dist(i,k)+dist(k,j)>v) add_edge(n+i,j,(dist(i,k)+dist(k,j)-v)*p[k]);
            }
        }
    }
    /*for(int i=1;i<=2*n;i++)
    {
        for(int j=1;j<=2*n;j++)
            printf("%6f ",d[i][j]);
        puts("");
    }*/
    floyd_warshall();
    double ans=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(i==j) continue;
            ans+=d[i][j];
        }
    printf("%.15f\n",ans/(n*(n-1)));
    return 0;
}

