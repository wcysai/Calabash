#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 25
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,c,w,tot;
int a[MAXN];
map<int,int> mp;
bool has[MAXN],opt[MAXN];
int read()
{
    int x;
    scanf("%d",&x);
    return x;
}
void decline()
{
    puts("decline");
    fflush(stdout);
}
void accept()
{
    puts("accept");
    fflush(stdout);
}
void stop()
{
    puts("stop");
    fflush(stdout);
    exit(0);
}
void montecarlo()
{
    int x=read(),d=x-w;
    mp[d]++;decline();
}
int findopt()
{
    int ans=-1;
    for(int i=0;i<(1<<n);i++)
    {
        int sum=0;
        for(int j=0;j<n;j++)
            if(i&(1<<j)) sum+=a[j];
        if(sum>c) continue;
        if(sum>ans)
        {
            ans=sum;
            for(int j=0;j<n;j++) if(i&(1<<j)) opt[j]=true; else opt[j]=false;
        }
    }
    return ans;
}
void move(int x)
{
    bool f=false;
    for(int j=0;j<n;j++) 
    {
        if(a[j]==abs(x))
        {
            f=true;
            if(x<0&&has[j]&&!opt[j])
            {
                has[j]=false;
                accept();w-=x;
                return;
            }
            if(x>0&&!has[j]&&opt[j])
            {
                has[j]=true;
                accept();w+=x;
                return;
            }
        }
    }
    assert(f);
    decline();
}
int main()
{
    scanf("%d%d%d",&n,&c,&w);
    accept();
    for(int i=0;i<35*n;i++) montecarlo();
    tot=0;
    for(auto p:mp)
    {
        int cnt=p.S,v=cnt/35;
        if((v+1)*35-cnt<=cnt-v*35) v++;
        for(int j=0;j<v;j++) 
        {
            a[tot]=abs(p.F);
            has[tot++]=(p.F<0?true:false);
        }
    }
    assert(tot==n);
    int ans=findopt();
    if(ans==w)
    {
        int x=read()-w;
        bool f=false;
        for(int j=0;j<n;j++)
        {
            if(a[j]==abs(x))
            {
                if(x<0&&has[j])
                {
                    has[j]=false;
                    accept();w-=x;f=true;
                    break;
                }
                if(x>0&&!has[j])
                {
                    has[j]=true;
                    accept();w+=x;f=true;
                    break;
                }
            }
        }
        assert(f);
    }
    while(true)
    {
        int x=read();
        if(x==ans) stop();
        else move(x-w);
    }
    return 0;
}

