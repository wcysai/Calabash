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
int n,c,w,tot,cnt=0;
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
    puts("decline");cnt++;assert(cnt<=1000);
    fflush(stdout);
}
void accept()
{
    puts("accept");cnt++;assert(cnt<=1000);
    fflush(stdout);
}
void stop()
{
    puts("stop");cnt++;assert(cnt<=1000);
    fflush(stdout);
    exit(0);
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
    for(int j=0;j<n;j++) 
    {
        if(a[j]==abs(x))
        {
            if(x<0&&has[j]&&!opt[j])
            {
                has[j]=false;
                accept();w+=x;
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
    decline();
}
int main()
{
    scanf("%d%d%d",&n,&c,&w);
    accept();
    while(w>0)
    {
        int x=read();
        if(x<w) 
        {
            accept();w=x;
        }
        else decline();
    }
    tot=0;
    while(tot<n)
    {
        int x=read();
        if(x>w)
        {
            a[tot++]=x-w;
            accept();w=x;
        }
        else decline();
    }
    memset(has,true,sizeof(has));
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
                    accept();w+=x;f=true;
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

