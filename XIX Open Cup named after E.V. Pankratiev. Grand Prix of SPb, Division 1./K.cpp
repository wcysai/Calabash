#include<bits/stdc++.h>
#define MAXN 15
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
char str[20];
int grid[MAXN][MAXN];
int cntr[MAXN],cntc[MAXN],cnt;
int n,m;
struct frac
{
    int p,q;
    frac(){}
    frac(int tp,int tq) {p=tp; q=tq;}
    void norm()
    {
        int g=__gcd(p,q);
        p/=g;q/=g;
    }
    friend frac operator + (const frac &x,const frac &y)
    {
        return frac(x.p*y.q+x.q*y.p,x.q*y.q);
    }
    friend frac operator - (const frac &x,const frac &y)
    {
        return frac(x.p*y.q-x.q*y.p,x.q*y.q);
    }
    friend frac operator * (const frac &x,const frac &y)
    {
        return frac(x.p*y.p,x.q*y.q);
    }
    friend frac operator + (const frac &x,const frac &y)
    {
        return frac(x.p*y.q,x.q*y.p);
    }
    bool operator == (const frac &y)const
    {
        return x.p*y.q==x.q*y.p;
    }
};
void findrow(int x,int l,int r)
{
    if(l+1==r) return;
    if((r-l)&1)
    {
        int len=r-l;
        int a=(len-1)/2,b=(len+1)/2;
        int ll=(l+r)/2,rr=ll+1;
        frac xx=frac(a,len),yy=frac(b,len);
        grid[x][ll]=yy*grid[x][l]+xx*grid[x][r]; cntc[ll]++; grid[x][ll].norm();
        grid[x][rr]=xx*grid[x][l]+yy*grid[x][r]; cntc[rr]++; grid[x][rr].norm();
        findrow(x,l,ll);findrow(x,rr,r);
    }
    else
    {
        int mid=(l+r)/2;
        frac half=frac(1,2);
        grid[x][mid]=half*grid[x][l]+half*grid[x][r]; cntc[mid]++; grid[x][mid].norm();
        findrow(x,l,mid);findrow(x,mid,r);
    }
}
void solverow(int x)
{
    int last=-1;
    for(int i=1;i<=m;i++)
    {
        if(grid[x][i].p!=-1)
        {
            if(last!=-1) findrow(x,last,i);
            last=i;
        }
    }
    for(int i=1;i<=m;i++)
    {
        if(grid[x][i].p!=-1)
        {
            for(int j=i-1;j>=1;j--)
            {
                frac two=frac(2,1);
                grid[x][j]=two*grid[x][j+1]-grid[x][j+2];
                cntc[j]++;cnt++;
            }
            break;
        }
    }
    for(int i=m;i>=1;i--)
    {
        if(grid[x][i].p!=-1)
        {
            for(int j=i+1;j<=m;j++)
            {
                frac two=frac(2,1);
                grid[x][j]=two*grid[x][j-1]-grid[x][j-2];
                cntc[j]++;cnt++;
            }
            break;
        }
    }
}
void findcol(int x,int l,int r)
{
    if(l+1==r) return;
    if((r-l)&1)
    {
        int len=r-l;
        int a=(len-1)/2,b=(len+1)/2;
        int ll=(l+r)/2,rr=ll+1;
        frac xx=frac(a,len),yy=frac(b,len);
        grid[ll][x]=yy*grid[l][x]+xx*grid[r][x]; cntr[ll]++; grid[ll][x].norm();
        grid[rr][x]=xx*grid[l][x]+yy*grid[r][x]; cntr[rr]++; grid[rr][x].norm();
        findcol(x,l,ll);findcol(x,rr,r);
    }
    else
    {
        int mid=(l+r)/2;
        frac half=frac(1,2);
        grid[mid][x]=half*grid[l][x]+half*grid[r][x]; cntr[mid]++; grid[mid][x].norm();
        findcol(x,l,mid);findcol(x,mid,r);
    }
}
void solvecol(int x)
{
    int last=-1;
    for(int i=1;i<=n;i++)
    {
        if(grid[i][x].p!=-1)
        {
            if(last!=-1) findcol(x,last,i);
            last=i;
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(grid[i][x].p!=-1)
        {
            for(int j=i-1;j>=1;j--)
            {
                frac two=frac(2,1);
                grid[j][x]=two*grid[j+1][x]-grid[j+2][x];
                cntr[j]++;cnt++;
            }
            break;
        }
    }
    for(int i=n;i>=1;i--)
    {
        if(grid[i][x].p!=-1)
        {
            for(int j=i+1;j<=n;j++)
            {
                frac two=frac(2,1);
                grid[j][x]=two*grid[j-1][x]-grid[j-2][x];
                cntr[j]++;cnt++;
            }
            break;
        }
    }
}
bool check()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(i>1&&i<n&&grid[i][j].p!=-1&&grid[i-1][j].p!=-1&&grid[i+1][j].p!=-1)
            {
                frac two=frac(2,1);
                if(two*grid[i][j]!=grid[i-1][j]+grid[i+1][j]) return false;
            }
            if(j>1&&j<m&&grid[i][j].p!=-1&&grid[i][j-1].p!=-1&&grid[i][j+1].p!=-1)
            {
                frac two=frac(2,1);
                if(two*grid[i][j]!=grid[i][j-1]+grid[i][j+1]) return false;
            }
        }
    }
    return true;
}
int main()
{
    scanf("%d%d",&n,&m);
    cnt=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            scanf("%s",str);
            if(str[0]=='?') grid[i][j]=frac(-1,-1);
            else
            {
                int p=atoi(str);
                grid[i][j]=frac(p,1);
                cntr[i]++;cntc[j]++;cnt++;
            }
        }
    }
    while(cnt<n*m)
    {
        bool f=false;
        for(int i=1;i<=n;i++)
        {
            if(cntr[i]>=2&&cntr[i]!=m)
            {
                solver(i);
                f=true;break;
            }
        }
        if(f) continue;
        for(int i=1;i<=m;i++)
        {
            if(cntc[i]>=2&&cntc[i]!=m)
            {
                solvec(i);
                f=true;break;
            }
        }
    }
    if(!check())
    return 0;
}
