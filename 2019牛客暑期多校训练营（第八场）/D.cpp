#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef vector<int> vec;
typedef vector<vec> mat;
typedef vector<mat> cube;
const int blocks=2000;
int n,m,h,q;
int type[MAXN],x[MAXN],y[MAXN],z[MAXN],ans[MAXN];
struct node
{
    int x,y,z;
};
void rebuild(cube &A);
vector<node> v,save;
int main()
{
    scanf("%d%d%d%d",&n,&m,&h,&q);
    cube A(n,mat(m,vec(h)));
    for(int i=0;i<q;i++)
    {
        scanf("%d%d%d%d",&type[i],&x[i],&y[i],&z[i]);
        x[i]--; y[i]--; z[i]--;
    }
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            for(int k=0;k<h;k++)
                A[i][j][k]=INF;
    for(int i=0;i<(q-1)/blocks+1;i++)
    {
        v.clear();
        for(int j=i*blocks;j<min((i+1)*blocks,q);j++)
        {
            if(type[j]==1)
            {
                v.push_back((node){x[j],y[j],z[j]});
                save.push_back((node){x[j],y[j],z[j]});
            }
            else
            {
                ans[j]=A[x[j]][y[j]][z[j]];
                for(int k=0;k<(int)v.size();k++) ans[j]=min(ans[j],abs(x[j]-v[k].x)+abs(y[j]-v[k].y)+abs(z[j]-v[k].z));
            }
        }
        rebuild(A);
    }
    for(int i=0;i<q;i++) if(type[i]==2) printf("%d\n",ans[i]);
    return 0;
}
int dx[6]={0,0,0,0,-1,1},dy[6]={0,0,-1,1,0,0},dz[6]={-1,1,0,0,0,0};
void rebuild(cube &A)
{
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            for(int k=0;k<h;k++)
                A[i][j][k]=INF;
    queue<node> que;
    for(auto p:save)
    {
        que.push(p);
        A[p.x][p.y][p.z]=0;
    }
    int tot=0;
    while(que.size())
    {
        node p=que.front(); que.pop();
        for(int i=0;i<6;i++)
        {
            int nx=p.x+dx[i],ny=p.y+dy[i],nz=p.z+dz[i];
            if(nx>=0&&nx<n&&ny>=0&&ny<m&&nz>=0&&nz<h&&A[nx][ny][nz]==INF)
            {
                A[nx][ny][nz]=A[p.x][p.y][p.z]+1;
                que.push((node){nx,ny,nz});
            }
        }
    }
}
