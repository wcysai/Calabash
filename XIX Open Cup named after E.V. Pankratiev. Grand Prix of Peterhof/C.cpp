#include<bits/stdc++.h>
#define int long long
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define x1 dksaodska
#define y1 akoodsakdo
#define x2 dakoadsad
#define y2 aksodksa
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int x1,y1,x2,y2;
signed main()
{
    scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
    if(x1>x2)
    {
        swap(x1,x2);
        swap(y1,y2);
    }
    int res=abs(x1-x2)+abs(y1-y2);
    int xx=x1%5,yy=y1%5;
    while(xx>0) xx--,yy-=3;
    while(yy<0) yy+=5;
    yy=yy%5;
    assert(yy!=0); 
    int type=yy,ans=res;
    if(y2<y1)
    {
        int nxt;
        if(type==1) nxt=x1+2;
        else if(type==2) nxt=x1+4;
        else if(type==3) nxt=x1+1;
        else nxt=x1+3;
        int moves=(nxt-1)+abs(y2-y1)*3;
        if(moves<x2) ans=max(ans,res+2*((x2-moves-1)/5+1));
        if(type==1) nxt=y1-1;
        else if(type==2) nxt=y1-2;
        else if(type==3) nxt=y1-3;
        else if(type==4) nxt=y1-4;
        moves=(nxt+1)-abs(x2-x1)*2;
        if(moves>y2) ans=max(ans,res+2*((moves-y2-1)/5+1));
    }
    else if(y2>=y1)
    {
        int nxt;
        if(type==1) nxt=x1+2;
        else if(type==2) nxt=x1+4;
        else if(type==3) nxt=x1+1;
        else nxt=x1+3;
        int moves=(nxt-1)+abs(y2-y1)*2;
        if(moves<x2) ans=max(ans,res+2*((x2-moves-1)/5+1));
        if(type==1) nxt=y1+4;
        else if(type==2) nxt=y1+3;
        else if(type==3) nxt=y1+2;
        else if(type==4) nxt=y1+1;
        moves=(nxt-1)+abs(x2-x1)*3;
        if(moves<y2) ans=max(ans,res+2*((y2-moves-1)/5+1));
    }
    printf("%lld\n",ans);
    return 0;
}
