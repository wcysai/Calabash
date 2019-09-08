#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 15
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef vector<int> vec;
typedef vector<vec> mat;
int n,m,k;
char s[MAXN],t[MAXM];
int dp[2][MAXM];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
mat mul(mat A,mat B)
{
    mat C(A.size(),vec(B[0].size()));
    for(int i=0;i<(int)A.size();i++)
        for(int k=0;k<(int)B.size();k++)
        {
            if(!A[i][k]) continue;
            for(int j=0;j<(int)B[0].size();j++)
                add(C[i][j],1LL*A[i][k]*B[k][j]%MOD);
        }
    return C;
}
int get_all()
{
    memset(dp,0,sizeof(dp));
    dp[0][0]=1;
    for(int i=0;i<n;i++)
    {
        int now=i&1,nxt=now^1;
        memset(dp[nxt],0,sizeof(dp[nxt]));
        for(int j=0;j<=m;j++)
        {
            add(dp[nxt][j],dp[now][j]);
            if(j!=m&&t[j]==s[i]) add(dp[nxt][j+1],dp[now][j]);
        }
    }
    return dp[n&1][m];
}
void add(mat &A,char ch)
{
    //printf("adding %c\n",ch);
    for(int i=m-1;i>=1;i--)
    {
        if(t[i]==ch)
            for(int j=0;j<m;j++) add(A[i][j],A[i-1][j]);
    }
}
void addinv(mat &A,char ch)
{
    for(int i=1;i<m;i++)
    {
        if(t[i]==ch)
            for(int j=0;j<m;j++) add(A[j][i-1],A[j][i]);
    }
} 
void print(mat &A)
{
    for(int i=0;i<(int)A.size();i++)
    {
        for(int j=0;j<(int)A[0].size();j++) printf("%d ",A[i][j]);
        puts("");
    }
}
mat pre[MAXN],suf[MAXN];
mat trans[26];
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    scanf("%s",s);
    scanf("%s",t);
    if(m==1) 
    {
        puts("0");
        return 0;
    }
    for(int i=0;i<26;i++)
    {
        trans[i].resize(m,vec(m));
        for(int j=0;j<m;j++) trans[i][j][j]=1;
        for(int j=1;j<m;j++)
            if(t[j]-'a'==i) trans[i][j][j-1]=1;
    }
    int ans=get_all();
    if(k==1)
    {
        printf("%d\n",ans);
        return 0;
    }
    int blocks=(n+k-2)/(k-1);
    for(int i=0;i<blocks;i++)
    {
        for(int j=i*(k-1);j<min(n,(i+1)*(k-1));j++)
            if(j==i*(k-1)) pre[j]=trans[s[j]-'a']; 
                else 
                {
                    pre[j]=pre[j-1];
                    add(pre[j],s[j]);
                }
        for(int j=min(n,(i+1)*(k-1))-1;j>=i*(k-1);j--)
            if(j==min(n,(i+1)*(k-1))-1) suf[j]=trans[s[j]-'a']; 
            else 
            {
                suf[j]=suf[j+1];
                addinv(suf[j],s[j]);
            }
    }
    for(int i=0;i<n-1;i++)
    {
        if(s[i]==t[0])
        {
            int pos=min(n-1,i+(k-1));
            if((i+1)/(k-1)==pos/(k-1)) dec(ans,suf[i+1][m-1][0]);
            else
            {
                mat x(m,vec(1));
                x[0][0]=1;
                x=mul(suf[i+1],x); x=mul(pre[pos],x);
                dec(ans,x[m-1][0]);
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}

