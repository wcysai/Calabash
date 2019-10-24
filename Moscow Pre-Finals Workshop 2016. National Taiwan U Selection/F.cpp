#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 20160519
#define MOD2 26880696
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef vector<int> vec;
typedef vector<vec> mat;
mat mul_mod(mat A,mat B,int mod)
{
    mat C(A.size(),vec(B[0].size()));
    for(int i=0;i<(int)A.size();i++)
        for(int k=0;k<(int)B.size();k++)
            for(int j=0;j<(int)B[0].size();j++)
                C[i][j]=(C[i][j]+1LL*A[i][k]*B[k][j])%mod;
    return C;
}
mat pow_mod(mat A,int n,int mod)
{
    mat B(A.size(),vec(A.size()));
    for(int i=0;i<(int)A.size();i++) B[i][i]=1;
    while(n)
    {
        if(n&1) B=mul_mod(B,A,mod);
        A=mul_mod(A,A,mod);
        n>>=1;
    }
    return B;
}
int get_fib(int x,int mod)
{
    if(x==0) return 0;
    mat A(2,vec(2));
    A[0][0]=A[0][1]=A[1][0]=1; A[1][1]=0;
    mat B(2,vec(1));
    B[0][0]=1; B[1][0]=0;
    A=pow_mod(A,x-1,mod);
    A=mul_mod(A,B,mod);
    return A[0][0];
}
int T,n;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        int y=get_fib(n,MOD2);
        printf("%d\n",get_fib(y,MOD));
    }
    return 0;
}
