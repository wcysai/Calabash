#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef vector<int> vec;
typedef array<array<int, 5>, 5> mat;
int n,Q;
char str[MAXN];
map<char,int> mp;
mat type[5],id;
mat mul(mat A,mat B)
{
    mat C{{0}};
    for(int i=0;i<(int)A.size();i++)
        for(int j=0;j<(int)B[0].size();j++)
            C[i][j]=INF;
    for(int i=0;i<(int)A.size();i++)
        for(int k=0;k<(int)B.size();k++)
            for(int j=0;j<(int)B[0].size();j++)
                C[i][j]=min(C[i][j],A[i][k]+B[k][j]);
    return C;
}
struct segtree
{
    mat res[4*MAXN];
    void pushup(int k)
    {
        res[k]=mul(res[k*2+1],res[k*2]);
    }
    void build(int k,int l,int r)
    {
        if(l==r)
        {
            if(mp.find(str[l])==mp.end()) res[k]=id;
            else res[k]=type[mp[str[l]]];
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    mat query(int k,int l,int r,int x,int y)
    {
        if(l>y||x>r) return id;
        if(l>=x&&r<=y) return res[k];
        int mid=(l+r)/2;
        return mul(query(k*2+1,mid+1,r,x,y),query(k*2,l,mid,x,y));
    }
}seg;
void print(mat &A)
{
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
            printf("%d ",A[i][j]);
        puts("");
    }
}
int main()
{
//    id.resize(5,vec(5));
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            id[i][j]=(i==j?0:INF);
    mp['2']=0; mp['0']=1; mp['1']=2; mp['9']=3; mp['8']=4;
    for(int i=0;i<5;i++)
    {
 //       type[i].resize(5,vec(5));
        for(int j=0;j<5;j++)
            for(int k=0;k<5;k++)
                type[i][j][k]=(j==k?0:INF);
    }
    type[0][0][0]=1; type[0][1][0]=0;
    type[1][1][1]=1; type[1][2][1]=0;
    type[2][2][2]=1; type[2][3][2]=0;
    type[3][3][3]=1; type[3][4][3]=0;
    type[4][3][3]=1; type[4][4][4]=1;
    scanf("%d%d",&n,&Q);
    scanf("%s",str+1);
    reverse(str+1,str+n+1);
    seg.build(1,1,n);
    for(int i=1;i<=Q;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        l=n-l+1; r=n-r+1;
        swap(l,r);
        mat ans=seg.query(1,1,n,l,r);
        if(ans[4][0]==INF) puts("-1"); else printf("%d\n",ans[4][0]);
    }
    return 0;
}
