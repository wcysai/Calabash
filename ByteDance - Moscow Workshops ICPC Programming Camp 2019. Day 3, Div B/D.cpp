#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 4005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef vector<int> vec;
typedef vector<vec> mat;
typedef long long ll;
typedef bitset<4000> bit;
typedef vector<bit> vb;
int n;
mat mul(mat A,mat B)
{
    mat C(A.size(),vec(B[0].size()));
    for(int i=0;i<(int)A.size();i++)
        for(int k=0;k<(int)B.size();k++)
            for(int j=0;j<(int)B[0].size();j++)
                C[i][j]=C[i][j]+(A[i][k]&B[k][j]);
    return C;
}
vb mul(vb A,vb B)
{
    vb C;
    C.resize(n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(A[i][j]) C[i]^=B[j];
    return C;
}
mt19937 wcy(time(NULL));
char str[1005];
int get(char ch)
{
    if(ch>='0'&&ch<='9') return ch-'0';
    return ch-'A'+10;
}
int main()
{
    scanf("%d",&n);
    vb A(n),B(n),C(n);
    int cnt=(n-1)/4+1;
    for(int i=0;i<n;i++)
    {
        scanf("%s",str);
        for(int j=0;j<cnt;j++)
        {
            int x=get(str[j]);
            for(int k=(j+1)*4-1;k>=j*4;k--)
            {
                if(k<n) A[i][k]=x&1;
                x>>=1;
            }
        }
    }
    /*for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            printf("%d ",A[i][j]);
        puts("");
    }*/
    for(int i=0;i<n;i++)
    {
        scanf("%s",str);
        for(int j=0;j<cnt;j++)
        {
            int x=get(str[j]);
            for(int k=(j+1)*4-1;k>=j*4;k--)
            {
                if(k<n) B[i][k]=x&1;
                x>>=1;
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        scanf("%s",str);
        for(int j=0;j<cnt;j++)
        {
            int x=get(str[j]);
            for(int k=(j+1)*4-1;k>=j*4;k--)
            {
                if(k<n) C[i][k]=x&1;
                x>>=1;
            }
        }
    }
    bool f=true;
    vb res=mul(A,B);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(res[i][j]!=C[i][j])
            {
                f=false;
                break;
            }
        }
        if(!f) break;
    }
    if(f) puts("YES"); else puts("NO");
    return 0;
}
