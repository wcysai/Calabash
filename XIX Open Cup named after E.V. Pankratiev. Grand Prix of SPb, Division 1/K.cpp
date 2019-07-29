/*************************************************************************
    > File Name: KK.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-12-08 15:35:10
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 15
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
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
typedef vector<frac> vec;
typedef vector<vec> mat;
int N,M;
char str[MAXN];
frac grid[MAXN][MAXN];
vector<vector<frac> >v;
vector<int> id(4);
vector<int> f;
vec ans;
int pivot;
void add(int a,int b,int c,int d,int e)
{
    v.push_back({(frac){a,1},(frac){b,1},(frac){c,1},(frac){d,1}});
    ans.push_back((frac){e,1});
}
// the matrix can be uniquely determined by four entries, which are, respectively:
// number in the left upper corner
// difference of adjacent elements in the first column
// difference of adjacent elements in the first row
// difference increase between the first and second row
void gauss_jordan(const mat& A, const vec& b)
{
    int n=A.size();
    mat B(n,vec(5));
    for(int i=0;i<n;i++)
        for(int j=0;j<4;j++)
            B[i][j]=A[i][j],B[i][j].norm();

    for(int i=0;i<n;i++) B[i][4]=b[i],B[i][4].norm();
    pivot=0;
    for(int i=0;i<4;i++)
    {
        for(int j=pivot;j<n;j++)
        {
            if(B[j][i].p!=0) 
            {
                swap(B[j],B[pivot]);
                break;
            }
        }
        if(pivot==n||B[pivot][i].p==0)
        {
            id[i]=-1;
            f.push_back(i);
            continue;
        }
        id[i]=pivot;
        for(int j=0;j<n;j++)
        {
            if(j==pivot) continue;
            frac cf=B[j][i]/B[pivot][i];cf.norm();
            for(int k=0;k<5;k++) B[j][k]=B[j][k]-B[pivot][k]*cf,B[j][k].norm();
        }
        pivot++;
    }
    for(int i=pivot;i<n;i++)
    {
        if(B[i][4].p!=0)
        {
            puts("None");
            return;
        }
    }
    if(f.size()==0) puts("Unique"); else puts("Multiple");
    for(int value=0;;value++)
    {
        vector<frac> ans(4);
        for(int i=0;i<4;i++)
        {
            if(id[i]==-1) ans[i]=frac(value,1);
            else 
            {
                ans[i]=B[id[i]][4]/B[id[i]][i];
                ans[i].norm();
                for(int k:f)  ans[i]=ans[i]-frac(value,1)*B[id[i]][k]/B[id[i]][i],ans[i].norm();
            }
        }
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<M;j++)
            {
                frac r=ans[0]+ans[1]*frac(i,1)+ans[2]*frac(j,1)+ans[3]*frac(i,1)*frac(j,1);
                r.norm();
                r.print();
                if(j==M-1) printf("\n"); else printf(" "); 
            }
        }
        if(value==1) return;
        if(f.size()==0) return;
        puts("and");
    }
}
int main()
{
    scanf("%d%d",&N,&M);
    if(N==1)
    {
        add(0,1,0,0,0);
        add(0,0,0,1,0);
    }
    if(M==1)
    {
        add(0,0,1,0,0);
        add(0,0,0,1,0);
    }
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++)
        {
            scanf("%s",str);
            if(str[0]!='?') add(1,i,j,i*j,atoi(str));
        }
    /*for(int i=0;i<(int)v.size();i++)
    {
        for(int j=0;j<(int)v[i].size();j++)
        {
            v[i][j].print();
            if(j==(int)v[i].size()-1) puts(""); else printf(" ");
        }
    }*/
    gauss_jordan(v,ans);
    return 0;
}

