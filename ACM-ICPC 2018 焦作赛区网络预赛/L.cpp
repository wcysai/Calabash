/*************************************************************************
    > File Name: L.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-09-15 12:05:04
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
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
typedef long long ll;
mat mul(mat A,mat B)
{
    mat C(A.size(),vec(B[0].size()));
    for(int i=0;i<(int)A.size();i++)
        for(int k=0;k<(int)B.size();k++)
            for(int j=0;j<(int)B[0].size();j++)
                C[i][j]=(C[i][j]+1LL*A[i][k]*B[k][j])%MOD;
    return C;
}
mat _pow(mat A,ll n)
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
int T;
ll n;
//11:0
//12:1
//13:2
//21:3
//22:4
//23:5
//31:6
//32:7
//33:8
int main()
{
    scanf("%d",&T);
    mat A(9,vec(9));
    for(int i=0;i<9;i++) for(int j=0;j<9;j++) A[i][j]=0;
    A[0][3]=1;A[0][6]=1;
    A[1][0]=1;A[1][6]=1;
    A[2][0]=1;A[2][3]=1;A[2][6]=1;
    A[3][1]=1;A[3][4]=1;
    A[4][1]=1;A[4][7]=1;
    A[5][4]=1;A[5][7]=1;
    A[6][2]=1;A[6][5]=1;A[6][8]=1;
    A[7][2]=1;A[7][8]=1;
    A[8][2]=1;A[8][5]=1;
    while(T--)
    {
        scanf("%lld",&n);
        if(n==1) puts("3");
        else if(n==2) puts("9");
        else
        {
            mat x(9,vec(1));
            for(int i=0;i<9;i++) x[i][0]=1;
            mat C=_pow(A,n-2);
            x=mul(C,x);
            int ans=0;
            for(int i=0;i<9;i++)
            {
                ans+=x[i][0];
                if(ans>=MOD) ans-=MOD;
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}
