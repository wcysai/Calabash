/*************************************************************************
    > File Name: J.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-08-25 12:33:10
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,tot,ans;
struct node
{
    int x,y,v;
}a[MAXN];
bool cmp(node p,node q)
{
    if(p.x!=q.x) return p.x<q.x;
    return p.y<q.y;
}
vector<int> G;
vector<int> save;
int bit[2*MAXN+1];
int sum(int i)
{
    int s=0;
    while(i>0)
    {
        s=max(s,bit[i]);
        i-=i&-i;
    }
    return s;
}
void add(int i,int x)
{
    while(i<=n)
    {
        bit[i]=max(bit[i],x);
        i+=i&-i;
    }
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) bit[i]=0;
        G.clear();
        tot=0;
        for(int i=1;i<=n;i++) 
        {
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            if(x==0||y==0) continue;
            ++tot;
            a[tot].x=x;a[tot].y=y;a[tot].v=z;
            G.push_back(x);G.push_back(y);
        }
        sort(a+1,a+tot+1,cmp);
        sort(G.begin(),G.end());
        G.erase(unique(G.begin(),G.end()),G.end());
        for(int i=1;i<=tot;i++) 
        {
            a[i].x=lower_bound(G.begin(),G.end(),a[i].x)-G.begin()+1;
            a[i].y=lower_bound(G.begin(),G.end(),a[i].y)-G.begin()+1;
        }
        int last=1,ans=0;
        a[tot+1].x=INF+1;
        for(int i=1;i<=tot;i++)
        {
            if(a[i].x!=a[i+1].x)
            {
                save.clear();
                for(int j=last;j<=i;j++)
                {
                    int res=sum(a[j].y-1);
                    ans=max(ans,res+a[j].v);
                    save.push_back(res+a[j].v);
                }
                for(int j=last;j<=i;j++) add(a[j].y,save[j-last]);
                last=i+1;
            }
            else continue;
        }
        printf("%d\n",ans);
    }
    return 0;
}
