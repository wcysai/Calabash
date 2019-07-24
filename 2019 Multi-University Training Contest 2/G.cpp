#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
//0: . 1: O 2: X
int T,n;
int p3[10];
char str[10];
double dp[(1<<18)];
int getval(char ch)
{
    if(ch=='.'||ch=='#') return 0;
    if(ch=='O') return 1;
    return 2;
}

double getans(double l,double r)
{
    assert(l<r);
    assert(!(l==0&&r==0));
    if(l==-INF&&r==INF) return 0;
    if(l==-INF) return r-1;
    if(r==INF) return l+1;
    if(l<0&&r>0) return 0.0;
    if(l<0&&r<=0) return -getans(-r,-l);
    double res=1.0;
    while(true)
    {
        double t=0.0;
        while(t<=l) t+=res;
        if(t<r) return t;
        res/=2.0;
    }
    assert(0);
}
bool check(int mask)
{
    for(int i=0;i<9;i++)
    {
        int res=(mask>>(2*i))&3;
        if(res==3) return false;
    }
    return true;
}
void erasebit(int &mask,int x,int y)
{
    if(x<0||x>=3||y<0||y>=3) return;
    int b=x*3+y;
    int val=(1<<18)-1;
    val^=(1<<(2*b)); val^=(1<<(2*b+1));
    mask&=val;
}
int main()
{
    for(int mask=0;mask<(1<<18);mask++) dp[mask]=0.0;
    for(int mask=0;mask<(1<<18);mask++)
    {
        if(!check(mask)) continue;
        bool f=true;
        for(int i=0;i<9;i++) if(((mask>>(2*i))&3)==1) {f=false; break;}
        if(f)
        {
            int cnt=0;
            for(int i=0;i<9;i++) if(((mask>>(2*i))&3)==2) cnt++;
            dp[mask]=-cnt;
            continue;
        }
        double l=-INF,r=INF;
        for(int i=0;i<9;i++)
        {
            int v=(mask>>(2*i))&3;
            if(v!=1) continue;
            int x=i/3,y=i%3;
            int newmask=mask; erasebit(newmask,x,y); erasebit(newmask,x,y-1); erasebit(newmask,x,y+1); l=max(l,dp[newmask]);
            newmask=mask; erasebit(newmask,x,y); erasebit(newmask,x-1,y); erasebit(newmask,x+1,y); l=max(l,dp[newmask]);
            newmask=mask; erasebit(newmask,x,y); erasebit(newmask,x-1,y); erasebit(newmask,x+1,y); erasebit(newmask,x,y-1); erasebit(newmask,x,y+1); l=max(l,dp[newmask]);
        }
        for(int i=0;i<9;i++)
        {
            int v=(mask>>(2*i))&3;
            if(v!=2) continue;
            int x=i/3,y=i%3;
            int newmask=mask; erasebit(newmask,x,y); r=min(r,dp[newmask]);
        }
        dp[mask]=getans(l,r);
    }
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        double ans=0.0;
        for(int i=0;i<n;i++)
        {
            int mask=0;
            vector<int> v; v.clear();
            for(int j=0;j<3;j++) 
            {
                scanf("%s",str);
                v.push_back(getval(str[0]));
                v.push_back(getval(str[2]));
                v.push_back(getval(str[4]));
            }
            reverse(v.begin(),v.end());
            for(int j=0;j<9;j++) mask=(mask<<2)+v[j];
            ans+=dp[mask];
        }
        if(ans>0.0) puts("Alice"); else if(ans<0.0) puts("Bob"); else puts("Second");
    }
    return 0;
}
