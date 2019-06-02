#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S seond
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int H,W,N;
int row[MAXN],col[MAXN];
//0: white 1: red -1: not set
int dp1[MAXN][4][2],dp2[MAXN][4][2];
int all1,all2,nsame1,nsame2;
//0: exists neither
//1: exist two consecutive white
//2: exist two consecutive red
//3: both exists
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int main()
{
    memset(row,-1,sizeof(row));
    memset(col,-1,sizeof(col));
    scanf("%d%d",&H,&W);
    scanf("%d",&N);
    bool flag=true;
    for(int i=1;i<=N;i++)
    {
        int r,c,d,x,y;
        scanf("%d%d%d",&r,&c,&d);
        if(d==1)
        {
            x=0; y=0;
        }
        else if(d==2)
        {
            x=1; y=0;
        }
        else if(d==3)
        {
            x=1; y=1;
        }
        else
        {
            x=0; y=1;
        }
        x^=(c+1)&1; y^=(r+1)&1;
        if(row[r]!=-1&&row[r]!=x) flag=false;
        if(col[c]!=-1&&col[c]!=y) flag=false;
        row[r]=x; col[c]=y;
    }
    if(!flag) {puts("0"); return 0;}
    memset(dp1,0,sizeof(dp1));
    memset(dp2,0,sizeof(dp2));
    if(row[1]==-1) dp1[1][0][0]=dp1[1][0][1]=1; else dp1[1][0][row[1]]=1;
    for(int i=1;i<H;i++)
    {
        for(int j=0;j<4;j++)
        {
            for(int k=0;k<2;k++)
            {
                if(!dp1[i][j][k]) continue;
                for(int l=0;l<2;l++)
                {
                    if(row[i+1]!=-1&&l!=row[i+1]) continue;
                    int newmask=j;
                    if(l==k) 
                    {
                        if(newmask&(1<<l)) continue;
                        newmask|=(1<<l);
                    }
                    add(dp1[i+1][newmask][l],dp1[i][j][k]);
                }
            }
        }
    }
    if(col[1]==-1) dp2[1][0][0]=dp2[1][0][1]=1; else dp2[1][0][col[1]]=1;
    for(int i=1;i<W;i++)
    {
        for(int j=0;j<4;j++)
        {
            for(int k=0;k<2;k++)
            {
                if(!dp2[i][j][k]) continue;
                for(int l=0;l<2;l++)
                {
                    if(col[i+1]!=-1&&l!=col[i+1]) continue;
                    int newmask=j;
                    if(l==k) 
                    {
                        if(newmask&(1<<l)) continue;
                        newmask|=(1<<l);
                    }
                    add(dp2[i+1][newmask][l],dp2[i][j][k]);
                }
            }
        }
    }
    all1=all2=1;
    for(int i=1;i<=H;i++) if(row[i]==-1) all1=2LL*all1%MOD;
    for(int i=1;i<=W;i++) if(col[i]==-1) all2=2LL*all2%MOD;
    nsame1=dp1[H][0][0]+dp1[H][0][1];
    nsame2=dp2[W][0][0]+dp2[W][0][1];
    //printf("%d %d %d %d\n",all1,all2,nsame1,nsame2);
    int ans=0;
    add(ans,1LL*nsame1*all2%MOD);
    add(ans,1LL*nsame2*all1%MOD);
    dec(ans,1LL*nsame1*nsame2%MOD);
    for(int mask1=1;mask1<3;mask1++)
        for(int mask2=1;mask2<3;mask2++)
        {
            if(mask1&mask2) continue;
            for(int j=0;j<2;j++)
                for(int k=0;k<2;k++)
                    add(ans,1LL*dp1[H][mask1][j]*dp2[W][mask2][k]%MOD);
        }
    if(ans==6) ans=12;
    printf("%d\n",ans);
    return 0;
}
