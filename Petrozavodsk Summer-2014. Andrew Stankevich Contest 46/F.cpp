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
mat mul(mat A,mat B)
{
    mat C((int)A.size(),vec(B[0].size()));
    for(int i=0;i<(int)A.size();i++)
        for(int k=0;k<(int)B.size();k++)
            for(int j=0;j<(int)B[0].size();j++)
                C[i][j]=(C[i][j]+1LL*A[i][k]*B[k][j])%MOD;
    return C;
}
mat pow_mod(mat A,int n)
{
    mat B((int)A.size(),vec(A.size()));
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
int main()
{
    while(scanf("%d",&n)==1)
    {
        if(!n) break;
        mat A(4,vec(4));
        for(int i=0;i<4;i++) for(int j=0;j<4;j++) A[i][j]=0;
        A[0][0]=1;A[0][1]=1;A[0][2]=1;A[1][0]=1;A[1][1]=2;A[1][2]=2;A[2][2]=1;A[2][3]=1;A[3][1]=1;A[3][2]=2;A[3][3]=1;
        mat x(4,vec(1));x[0][0]=1;x[1][0]=0;x[2][0]=0;x[3][0]=0;
        A=pow_mod(A,n);x=mul(A,x);
        printf("%d\n",x[0][0]);
    }
    return 0;
}
