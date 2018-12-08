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
ll cntr[MAXN],cntc[MAXN],cnt;
ll dummy,dumr[MAXN],dumc[MAXN];
ll n,m;
struct frac
{
    ll p,q;
    frac(){}
    frac(ll tp,ll tq) {p=tp; q=tq;}
    void norm()
    {
        ll g=__gcd(p,q);
        p/=g;q/=g;
        if(q<0) {p*=-1; q*=-1;}
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
    friend frac operator / (const frac &x,const frac &y)
    {
        return frac(x.p*y.q,x.q*y.p);
    }
    bool operator == (const frac &y)const
    {
        return p*y.q==q*y.p;
    }
    bool operator != (const frac &y)const
    {
        return p*y.q!=q*y.p;
    }
    void print()
    {
        printf("%lld/%lld",p,q);
    }
};
frac grid[MAXN][MAXN];
frac ori[MAXN][MAXN];
void findrow(ll x,ll l,ll r)
{
    if(l+1==r) return;
    if((r-l)&1)
    {
        ll len=r-l;
        ll a=(len-1)/2,b=(len+1)/2;
        ll ll=(l+r)/2,rr=ll+1;
        frac xx=frac(a,len),yy=frac(b,len);
        grid[x][ll]=yy*grid[x][l]+xx*grid[x][r]; cntc[ll]++; cnt++; grid[x][ll].norm();
        grid[x][rr]=xx*grid[x][l]+yy*grid[x][r]; cntc[rr]++; cnt++; grid[x][rr].norm();
        findrow(x,l,ll);findrow(x,rr,r);
    }
    else
    {
        ll mid=(l+r)/2;
        frac half=frac(1,2);
        grid[x][mid]=half*grid[x][l]+half*grid[x][r]; cntc[mid]++; cnt++; grid[x][mid].norm();
        findrow(x,l,mid);findrow(x,mid,r);
    }
}
void solverow(ll x)
{
    ll last=-1;
    for(ll i=1;i<=m;i++)
    {
        if(grid[x][i].q!=-1)
        {
            if(last!=-1) findrow(x,last,i);
            last=i;
        }
    }
    for(ll i=1;i<=m;i++)
    {
        if(grid[x][i].q!=-1)
        {
            for(ll j=i-1;j>=1;j--)
            {
                frac two=frac(2,1);
                grid[x][j]=two*grid[x][j+1]-grid[x][j+2]; grid[x][j].norm();
                cntc[j]++;cnt++;
            }
            break;
        }
    }
    for(ll i=m;i>=1;i--)
    {
        if(grid[x][i].q!=-1)
        {
            for(ll j=i+1;j<=m;j++)
            {
                frac two=frac(2,1);
                grid[x][j]=two*grid[x][j-1]-grid[x][j-2]; grid[x][j].norm();
                cntc[j]++;cnt++;
            }
            break;
        }
    }
}
void findcol(ll x,ll l,ll r)
{
    if(l+1==r) return;
    if((r-l)&1)
    {
        ll len=r-l;
        ll a=(len-1)/2,b=(len+1)/2;
        ll ll=(l+r)/2,rr=ll+1;
        frac xx=frac(a,len),yy=frac(b,len);
        grid[ll][x]=yy*grid[l][x]+xx*grid[r][x]; cntr[ll]++; cnt++; grid[ll][x].norm();
        grid[rr][x]=xx*grid[l][x]+yy*grid[r][x]; cntr[rr]++; cnt++; grid[rr][x].norm();
        findcol(x,l,ll);findcol(x,rr,r);
    }
    else
    {
        ll mid=(l+r)/2;
        frac half=frac(1,2);
        grid[mid][x]=half*grid[l][x]+half*grid[r][x]; cntr[mid]++; cnt++; grid[mid][x].norm();
        findcol(x,l,mid);findcol(x,mid,r);
    }
}
void solvecol(ll x)
{
    ll last=-1;
    for(ll i=1;i<=n;i++)
    {
        if(grid[i][x].q!=-1)
        {
            if(last!=-1) findcol(x,last,i);
            last=i;
        }
    }
    for(ll i=1;i<=n;i++)
    {
        if(grid[i][x].q!=-1)
        {
            for(ll j=i-1;j>=1;j--)
            {
                frac two=frac(2,1);
                grid[j][x]=two*grid[j+1][x]-grid[j+2][x]; grid[j][x].norm();
                cntr[j]++;cnt++;
            }
            break;
        }
    }
    for(ll i=n;i>=1;i--)
    {
        if(grid[i][x].q!=-1)
        {
            for(ll j=i+1;j<=n;j++)
            {
                frac two=frac(2,1);
                grid[j][x]=two*grid[j-1][x]-grid[j-2][x];grid[j][x].norm();
                cntr[j]++;cnt++;
            }
            break;
        }
    }
}
void try_to_fill(ll x)
{
    for(ll i=1;i<=n;i++)
        for(ll j=1;j<=m;j++)
        {
            if(grid[i][j].q==-1)
            {
                grid[i][j]=frac(x,1);cnt++;cntr[i]++;cntc[j]++;
                return;
            }
        }
}
void update()
{
    while(cnt<n*m)
    {
        bool f=false;
        for(ll i=1;i<=n;i++)
        {
            if(cntr[i]>=2&&cntr[i]!=m)
            {
                solverow(i);cntr[i]=m;
                f=true;break;
            }
        }
        if(f) continue;
        for(ll i=1;i<=m;i++)
        {
            if(cntc[i]>=2&&cntc[i]!=n)
            {
                solvecol(i);cntc[i]=n;
                f=true;break;
            }
        }
        if(!f) break;
    }
}
void complete()
{
    while(cnt<n*m)
    {
        try_to_fill(1);
        update();
    }
}
bool check()
{
    for(ll i=1;i<=n;i++)
    {
        for(ll j=1;j<=m;j++)
        {
            if(i>1&&i<n&&grid[i][j].q!=-1&&grid[i-1][j].q!=-1&&grid[i+1][j].q!=-1)
            {
                frac two=frac(2,1);
                if(two*grid[i][j]!=grid[i-1][j]+grid[i+1][j]) return false;
            }
            if(j>1&&j<m&&grid[i][j].q!=-1&&grid[i][j-1].q!=-1&&grid[i][j+1].q!=-1)
            {
                frac two=frac(2,1);
                if(two*grid[i][j]!=grid[i][j-1]+grid[i][j+1]) return false;
            }
        }
    }
    return true;
}
void output()
{
    for(ll i=1;i<=n;i++)
    {
        for(ll j=1;j<=m;j++)
        {
            grid[i][j].print();
            if(j==m) printf("\n"); else printf(" ");
        }
    }
}
void record()
{
    dummy=cnt;
    for(ll i=1;i<=n;i++) dumr[i]=cntr[i];
    for(ll i=1;i<=m;i++) dumc[i]=cntc[i];
    for(ll i=1;i<=n;i++)
        for(ll j=1;j<=m;j++)
            ori[i][j]=grid[i][j];
}
void rollback()
{
    cnt=dummy;
    for(ll i=1;i<=n;i++) cntr[i]=dumr[i];
    for(ll i=1;i<=m;i++) cntc[i]=dumc[i];
    for(ll i=1;i<=n;i++)
        for(ll j=1;j<=m;j++)
            grid[i][j]=ori[i][j];
}
int main()
{
    scanf("%lld%lld",&n,&m);
    cnt=0;
    for(ll i=1;i<=n;i++)
    {
        for(ll j=1;j<=m;j++)
        {
            scanf("%s",str);
            if(str[0]=='?') grid[i][j]=frac(-1,-1);
            else
            {
                ll p=atoi(str);
                grid[i][j]=frac(p,1);grid[i][j].norm();
                cntr[i]++;cntc[j]++;cnt++;
            }
        }
    }
    update();
    if(!check()) {puts("None"); return 0;}
    else if(cnt==n*m)
    {
        puts("Unique");output();
        return 0;
    }
    else
    {
        puts("Multiple");
        record();try_to_fill(1);update();complete();output();
        puts("and");
        rollback();try_to_fill(2);update();complete();output();
    }
    return 0;
}
