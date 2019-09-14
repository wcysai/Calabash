#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 2000000000
#define MOD 1025436931
#define P 472634375
#define X 236317188
#define Y 789119744
#define PINV 94526875
#define F first
#define S second
#define x1 csdaokdo
#define y1 dsakodkaso9
#define x2 dosakdos
#define y2 adskodasdas
using namespace std;
typedef long long ll;
int T,n,m,r1,c1,r2,c2,ans;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
int get_sum(int n)
{
    int x=pow_mod(X,n+1); dec(x,X); x=1LL*x*pow_mod(X-1,MOD-2)%MOD;
    int y=pow_mod(Y,n+1); dec(y,Y); y=1LL*y*pow_mod(Y-1,MOD-2)%MOD;
    dec(x,y); x=1LL*x*PINV%MOD;
    return x;
}
int get_dist(int x1,int y1,int x2,int y2)
{
    return abs(x1-x2)+abs(y1-y2);
}
void check_corner(int x,int y)
{
    if(get_dist(x,y,r1,c1)<=get_dist(x,y,r2,c2)) return;
    int d=get_dist(x,y,r1,c1);
    ans=max(ans,d-1);
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d%d%d",&n,&m,&r1,&c1,&r2,&c2);
        if(n>m)
        {
            swap(n,m);
            swap(r1,c1);
            swap(r2,c2);
        }
        if(n==1)
        {
            if((c2==1&&c1==2)||(c2==m&&c1==m-1))
            {
                puts("1");
                continue;
            }
            ans=1;
            check_corner(1,1); check_corner(1,m);
            if(((r1+c1)&1)!=((r2+c2)&1)) ans++;
            printf("%d\n",get_sum(ans));
            continue;
        }
        if(n!=1&&(((r1+c1)&1)!=((r2+c2)&1))) {puts("countless"); continue;}
        ans=1;
        check_corner(1,1); check_corner(1,m); check_corner(n,1); check_corner(n,m);
        printf("%d\n",get_sum(ans));
    }
    return 0;
}
