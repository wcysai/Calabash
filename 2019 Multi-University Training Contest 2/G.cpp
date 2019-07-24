#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
struct node
{
    int type,x,y;
};
typedef vector<node> vec;
typedef vector<vec> mat;
//0: . 1: O 2: X
mat op;
int T,n;
int p3[10];
char str[10];
double dp[(1<<18)];
struct node
{
    int x;
    void setbit(int b,int v)
    {

    }
}
P getpos(int x)
{
    return make_pair(x/3,x%3);
}
P getid(P p)
{
    return 3*p.F+p.S;
}

double getans(double lmaxi,double rmini)
{
    assert(!(lmaxi==0&&rmini==0));
    if(lmaxi==-INF&&rmini==INF) return 0;
    if(lmaxi==-INF) return rmini-1;
    if(rmini==INF) return lmaxi+1;
    if(lmaxi<0&&rmini>0) return 0.0;
    if(lmaxi<0&&rmini<0) return -getans(-rmini,-lmaxi);
    double res=1.0;
    while(true)
    {
        double t=0.0;
        while(t<=lmaxi) t+=res;
        if(t<rmini) return t;
        res/=2.0;
    }
    assert(0);
}
double dfs()
{ 
    double lmaxi=-INF,rmini=INF;
    bool f=true;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(mp[i][j]=='O')
            {
                f=false;
                block(i,j,1); lmaxi=max(lmaxi,dfs()); rollback();
                block(i,j,2); lmaxi=max(lmaxi,dfs()); rollback();
                block(i,j,3); lmaxi=max(lmaxi,dfs()); rollback();
            }
        }
    }
    if(!f)
    {
        int cnt=0;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(mp[i][j]=='X') cnt++;
        return -cnt;
    }
    else
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(mp[i][j]=='X')
                {
                    block(i,j,0); 
                    rmini=min(rmini,dfs()); 
                    rollback();
                }
            }
        }
    }
    return getans(lmaxi,rmini);
}
int main()
{
    p3[0]=1;
    for(int i=1;i<=9;i++) p3[i]=3*p3[i-1];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        double ans=0.0;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<3;j++) 
            {
                scanf("%s",str);
                mp[j][0]=str[0];
                mp[j][1]=str[2];
                mp[j][2]=str[4];
            }
            ans+=dfs();
        }
        if(ans>0.0) puts("Alice"); else if(ans<0.0) puts("Bob"); else puts("Second");
    }
    return 0;
}
