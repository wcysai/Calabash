#include<bits/stdc++.h>
#define MAXN 405
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef vector<int> vec;
typedef vector<vec> mat;
int T,n,K,r,c,tot;
bool valid[MAXN][MAXN];
bool vis[MAXN][MAXN];
int pool[MAXN][MAXN],prob[MAXN][MAXN],E[MAXN][MAXN];
int vari[MAXN][MAXN],deg[MAXN][MAXN];
vec coef[MAXN][MAXN];
int inv[10];
int x[MAXN],y[MAXN];
int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
mat equations;
vec res;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
vec gauss_jordan(const mat& A, const vec& b)
{
    int n=A.size();
    mat B(n,vec(n+1));
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            B[i][j]=A[i][j];

    for(int i=0;i<n;i++) B[i][n]=b[i];
    for(int i=0;i<n;i++)
    {
        int pivot=i;
        for(int j=i;j<n;j++)
            if(abs(B[j][i])>abs(B[pivot][i])) pivot=j;
        swap(B[i],B[pivot]);
        if(B[i][i]==0) return vec();
        for(int j=i+1;j<=n;j++) B[i][j]=1LL*B[i][j]*pow_mod(B[i][i],MOD-2)%MOD;
        for(int j=0;j<n;j++)
        {
            if(i!=j)
            {
                for(int k=i+1;k<=n;k++)
                    dec(B[j][k],1LL*B[j][i]*B[i][k]%MOD);
            }
        }
    }
    vec x(n);
    for(int i=0;i<n;i++)
        x[i]=B[i][n];
    return x;
}
vec add(vec x,vec y)
{
    assert(x.size()==y.size());
    vec ret(x.size());
    for(int i=0;i<(int)x.size();i++)
    {
        ret[i]=x[i];
        add(ret[i],y[i]);
    }
    return ret;
}
vec dec(vec x,vec y)
{
    assert(x.size()==y.size());
    vec ret(x.size());
    for(int i=0;i<(int)x.size();i++)
    {
        ret[i]=x[i];
        dec(ret[i],y[i]);
    }
    return ret;
}
vec mul(vec x,int lambda)
{
    vec ret(x.size());
    for(int i=0;i<(int)x.size();i++) ret[i]=1LL*x[i]*lambda%MOD;
    return ret;
}
void bfs(int r,int c)
{
    queue<P> que; que.push(P(r,c));
    vis[r][c]=true;
    while(que.size())
    {
        P p=que.front(); que.pop();
        int x=p.F,y=p.S;
        if(pool[x][y]) continue;
        for(int i=0;i<4;i++)
        {
            int nx=x+dx[i],ny=y+dy[i];
            if(nx>=1&&nx<=n&&ny>=1&&ny<=n&&!vis[nx][ny])
            {
                vis[nx][ny]=true;
                que.push(P(nx,ny));
            }
        }
    }
}
int main()
{
    for(int i=1;i<10;i++) inv[i]=pow_mod(i,MOD-2);
    scanf("%d",&T);
    while(T--)
    {
        equations.clear(); res.clear();
        scanf("%d%d",&n,&K);
        memset(vis,false,sizeof(vis));
        memset(pool,0,sizeof(pool));
        memset(vari,0,sizeof(vari));
        memset(deg,0,sizeof(deg));
        memset(prob,0,sizeof(prob));
        memset(E,0,sizeof(E));
        for(int i=0;i<K;i++)
        {
            scanf("%d%d",&x[i],&y[i]);
            pool[x[i]][y[i]]=i+1;
        }
        scanf("%d%d",&r,&c);
        bfs(r,c);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                if(vis[i][j]&!pool[i][j])
                {
                    for(int k=0;k<4;k++)
                    {
                        int nx=i+dx[k],ny=j+dy[k];
                        if(nx>=1&&nx<=n&&ny>=1&&ny<=n) deg[i][j]++;
                    }
                }
            }
        tot=0;
        for(int i=1;i<=n;i++)
        {
            bool f=false;
            for(int j=1;j<=n;j++)
            {
                if(!vis[i][j]||pool[i][j]) f=false;
                else if(f) continue;
                else
                {
                    vari[i][j]=++tot;
                    f=true;
                }
            }
        }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                coef[i][j].clear();
                coef[i][j].resize(tot+1);
                if(vari[i][j]) coef[i][j][vari[i][j]-1]=1;
            }
        for(int j=1;j<=n;j++)
        {
            for(int i=1;i<=n;i++)
            {
                if(deg[i][j])
                {
                    vec cur=coef[i][j];
                    if(i-1>=1&&deg[i-1][j]) cur=dec(cur,mul(coef[i-1][j],inv[deg[i-1][j]]));
                    if(j-1>=1&&deg[i][j-1]) cur=dec(cur,mul(coef[i][j-1],inv[deg[i][j-1]]));
                    if(i+1<=n&&deg[i+1][j]) cur=dec(cur,mul(coef[i+1][j],inv[deg[i+1][j]]));
                    if(i==r&&j==c) dec(cur[tot],1);
                    if(deg[i][j+1])
                    {
                        cur=mul(cur,deg[i][j+1]);
                        coef[i][j+1]=cur;
                    }
                    else
                    {
                        int cons=cur.back(); cur.pop_back(); cons=(MOD-cons)%MOD;
                        equations.push_back(cur); res.push_back(cons);
                    }
                }
            }
        }
        vec solu=gauss_jordan(equations,res);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                if(deg[i][j])
                {
                    for(int k=0;k<tot;k++) add(prob[i][j],1LL*solu[k]*coef[i][j][k]%MOD);
                    add(prob[i][j],coef[i][j][tot]);
                }
            }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                if(vis[i][j]&&pool[i][j])
                {
                    for(int k=0;k<4;k++)
                    {
                        int nx=i+dx[k],ny=j+dy[k];
                        if(nx>=1&&nx<=n&&ny>=1&&ny<=n&&deg[nx][ny]) add(prob[i][j],1LL*prob[nx][ny]*inv[deg[nx][ny]]%MOD);
                    }
                }
            }
        equations.clear(); res.clear();
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                coef[i][j].clear();
                coef[i][j].resize(tot+1);
                if(vari[i][j]) coef[i][j][vari[i][j]-1]=1;
            }
        for(int j=1;j<=n;j++)
        {
            for(int i=1;i<=n;i++)
            {
                if(deg[i][j])
                {
                    vec cur=coef[i][j];
                    if(i-1>=1&&deg[i-1][j])
                    {
                        cur=dec(cur,mul(coef[i-1][j],inv[deg[i-1][j]]));
                        dec(cur[tot],1LL*prob[i-1][j]*inv[deg[i-1][j]]%MOD);
                    }
                    if(j-1>=1&&deg[i][j-1])
                    {
                        cur=dec(cur,mul(coef[i][j-1],inv[deg[i][j-1]]));
                        dec(cur[tot],1LL*prob[i][j-1]*inv[deg[i][j-1]]%MOD);
                    }
                    if(i+1<=n&&deg[i+1][j])
                    {
                        cur=dec(cur,mul(coef[i+1][j],inv[deg[i+1][j]]));
                        dec(cur[tot],1LL*prob[i+1][j]*inv[deg[i+1][j]]%MOD);
                    }
                    if(i==r&&j==c) dec(cur[tot],1);
                    if(deg[i][j+1])
                    {
                        cur=mul(cur,deg[i][j+1]);
                        dec(cur[tot],prob[i][j+1]);
                        coef[i][j+1]=cur;
                    }
                    else
                    {
                        int cons=cur.back(); cur.pop_back(); cons=(MOD-cons)%MOD;
                        equations.push_back(cur); res.push_back(cons);
                    }
                }
            }
        }
        solu=gauss_jordan(equations,res);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                if(deg[i][j])
                {
                    for(int k=0;k<tot;k++) add(E[i][j],1LL*solu[k]*coef[i][j][k]%MOD);
                    add(E[i][j],coef[i][j][tot]);
                }
            }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                if(vis[i][j]&&pool[i][j])
                {
                    for(int k=0;k<4;k++)
                    {
                        int nx=i+dx[k],ny=j+dy[k];
                        if(nx>=1&&nx<=n&&ny>=1&&ny<=n&&deg[nx][ny]) add(E[i][j],1LL*(E[nx][ny]+prob[nx][ny])*inv[deg[nx][ny]]%MOD);
                    }
                }
            }
        for(int i=0;i<K;i++)
        {
            if(!vis[x[i]][y[i]]) printf("GG");
            else
            {
                int ans=1LL*E[x[i]][y[i]]*pow_mod(prob[x[i]][y[i]],MOD-2)%MOD;
                dec(ans,1);
                printf("%d",ans);
            }
            if(i!=K-1) printf(" "); else printf("\n");
        }
    }
    return 0;
}
