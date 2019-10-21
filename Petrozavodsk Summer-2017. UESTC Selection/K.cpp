#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T;
ll A,B,C,D;
int dp[65][(1<<4)][4][4];
//3: greater
//2: 1 larger
//1: equal
//0: 1 smaller
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
int trans(int a,int b)
{
    if(a==3) return 3;
    if(a==2)
    {
        if(b==-2) return 1;
        else if(b==-1) return 2;
        else return 3;
    }
    if(a==1) return b+1;
    if(a==0)
    {
        if(b==2) return 1;
        else if(b==1) return 0;
        else return -1;
    }
}
int solve(int now,int mask,int f1,int f2)
{
    if(now==-1) return (f1>=2&&f2>=1);
    if(dp[now][mask][f1][f2]!=-1) return dp[now][mask][f1][f2];
    int &res=dp[now][mask][f1][f2];
    res=0;
    int limita=(mask&8)?1:((A>>now)&1),limitb=(mask&4)?1:((B>>now)&1),limitc=(mask&2)?1:((C>>now)&1),limitd=(mask&1)?1:((D>>now)&1);
    for(int a=0;a<=limita;a++)
        for(int b=0;b<=limitb;b++)
            for(int c=0;c<=limitc;c++)
                for(int d=0;d<=limitd;d++)
                {
                    int nmask=0;
                    if(a<limita) nmask|=8;
                    if(b<limitb) nmask|=4;
                    if(c<limitc) nmask|=2;
                    if(d<limitd) nmask|=1;
                    int x=trans(f1,a+c-b-d),y=trans(f2,a+d-b-c);
                    if(x==-1||y==-1) continue;
                    add(res,solve(now-1,mask|nmask,x,y));
                }
    return res;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld%lld%lld%lld",&A,&B,&C,&D);
        memset(dp,-1,sizeof(dp));
        printf("%d\n",solve(61,0,1,1));
    }
    return 0;
}
