#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef vector<int> vec;
typedef vector<vec> mat;
char str[MAXN];
int n;
vec S[MAXN],D[MAXN];
mat id(53,vec(53));
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int getnum(char ch)
{
    if(ch>='a'&&ch<='z') return ch-'a';
    else return ch-'A'+26;
}
void compute_S()
{
    for(int i=0;i<=n;i++) S[i].resize(53);
    for(int i=0;i<53;i++) S[0][i]=1;
    mat u=id;
    for(int i=1;i<=n;i++)
    {
        int x=getnum(str[i]);
        for(int j=0;j<53;j++)
        {
            add(S[i][j],2LL*S[i-1][j]%MOD);
            dec(S[i][j],u[x][j]);
            int dif=S[i][j]; dec(dif,S[i-1][j]);
            add(u[x][j],dif);
        }
    }
}
void compute_D()
{
    for(int i=0;i<=n;i++) D[i].resize(53);
    mat u=id;
    for(int i=1;i<=n;i++)
    {
        int x=getnum(str[i]);
        for(int j=0;j<53;j++) D[i][j]=u[x][j];
        for(int j=0;j<53;j++)
        {
            u[x][j]=2LL*u[x][j]%MOD;
            dec(u[x][j],D[i-1][j]);
        }
    }
}
int Q,a0,b0,p,q,r;
int get_ans(int l,int r)
{
    vec tmp(53);
    tmp[52]=1;
    for(int i=0;i<53;i++) dec(tmp[i],D[l-1][i]);
    int ans=0;
    for(int i=0;i<53;i++) add(ans,1LL*S[r][i]*tmp[i]%MOD);
    return ans;
}
int main()
{
    for(int i=0;i<53;i++) id[i][i]=1;
    scanf("%s",str+1);
    n=strlen(str+1); 
    compute_S(); compute_D();
    scanf("%d%d%d%d%d%d",&Q,&a0,&b0,&p,&q,&r);
    int a,b,x,y,z;
    a=a0; b=b0; z=0;
    for(int i=0;i<Q;i++)
    {
        int ta=(1LL*p*a+1LL*q*b+z+r)%MOD;
        int tb=(1LL*p*b+1LL*q*a+z+r)%MOD;
        x=min(ta%n,tb%n)+1;
        y=max(ta%n,tb%n)+1;
        z=get_ans(x,y);
        a=ta; b=tb;
    }
    printf("%d\n",z);
}
