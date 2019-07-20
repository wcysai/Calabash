#include<bits/stdc++.h>
#define MAXN 50000
#define MAXM 10
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef vector<int> vec;
typedef vector<vec> mat;
int N,M,Q;
int a[MAXN][MAXM];
mat mul(mat A,mat B)
{
    mat C(A.size(),vec(B[0].size()));
    for(int i=0;i<(int)A.size();i++)
        for(int k=0;k<(int)B.size();k++)
            for(int j=0;j<(int)B[0].size();j++)
                C[i][j]=(C[i][j]+1LL*A[i][k]*B[k][j])%MOD;
    return C;
}
mat pow_(mat A,ll n)
{
    mat B(A.size(),vec(A.size()));
    for(int i=0;i<(int)A.size();i++)
        B[i][i]=1;
    while(n>0)
    {
        if(n&1) B=mul(B,A);
        A=mul(A,A);
        n>>=1;
    }
    return B;
}
mat construct(int x)
{
    mat A(M,vec(M));
    for(int i=0;i<M;i++)
    {
        if(a[x][i]==0)
        {
            int l=i,r=i;
            while(l>0&&a[x][l-1]==0) l--;
            while(r+1<M&&a[x][r+1]==0) r++;
            for(int j=l;j<=r;j++) A[i][j]=1;
        }
    }
    return A;
}
void flip(int x,int y)
{
    a[x][y]^=1;
}
struct segtree
{
    mat res[4*MAXN+10];
    void pushup(int k)
    {
        res[k]=mul(res[k*2],res[k*2+1]);
    }
    void build(int k,int l,int r)
    {
        if(l==r)
        {
            res[k]=construct(l-1);
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    void modify(int k,int l,int r,int p)
    {
        if(l==r)
        {
            res[k]=construct(l-1);
            return;
        }
        int mid=(l+r)/2;
        if(p<=mid) modify(k*2,l,mid,p); else modify(k*2+1,mid+1,r,p);
        pushup(k);
    }
}seg;
string str;
int main()
{
    scanf("%d%d%d",&N,&M,&Q);
    for(int i=0;i<N;i++)
    {       
        cin>>str;
        for(int j=0;j<M;j++) a[i][j]=str[j]-'0';
    }
    seg.build(1,1,N);
    for(int i=0;i<Q;i++)
    {
        int type,a,b;
        scanf("%d%d%d",&type,&a,&b);
        a--; b--;
        if(type==1)
        {
            flip(a,b);
            seg.modify(1,1,N,a+1);
        }
        else
        {
            mat ret=seg.res[1];
            printf("%d\n",ret[a][b]);
        }
    }
    return 0;
}
