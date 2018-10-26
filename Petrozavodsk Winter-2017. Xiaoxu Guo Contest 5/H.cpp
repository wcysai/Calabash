#include <bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef vector<int> vec;
typedef vector<vec> mat;
mat mul(mat A,mat B)
{
    mat C(A.size(),vec(B[0].size()));
    for(int i=0;i<(int)A.size();i++)
        for(int k=0;k<(int)B.size();k++)
            for(int j=0;j<(int)B[0].size();j++)
                C[i][j]=(C[i][j]+1LL*A[i][k]*B[k][j])%MOD;
    return C;
}
mat pow_mod(mat A,ll n)
{
    mat B(A.size(),vec(A.size()));
    for(int i=0;i<(int)A.size();i++) B[i][i]=1;
    while(n)
    {
        if(n&1) B=mul(B,A);
        A=mul(A,A);
        n>>=1;
    }
    return B;
}
int n;
int a[20]={0,1,2,6,16,36};
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        if(n<=5) printf("%d\n",a[n]);
        else
        {
            mat A(4,vec(4));mat x(4,vec(1));
            for(int i=0;i<4;i++) for(int j=0;j<4;j++) A[i][j]=0;
            A[0][0]=3;A[0][1]=MOD-2;A[0][2]=1;A[0][3]=MOD-1;A[1][0]=1;A[2][1]=1;A[3][2]=1;
            x[0][0]=36;x[1][0]=16;x[2][0]=6;x[3][0]=2;
            A=pow_mod(A,n-5);x=mul(A,x);
            printf("%d\n",x[0][0]);
        }
    }
    return 0;
}
