#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
int w[MAXN],q[MAXN];
vector<int> dis;
int bit[MAXN];
int offset=1000000;
int sum(int i)
{
    i=offset-i;
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
    i=offset-i;
    while(i<=1000000)
    {
        bit[i]=max(bit[i],x);
        i+=i&-i;
    }
}
int angry[MAXN];
int main()
{
    memset(bit,0,sizeof(bit));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&w[i]);
        q[i]=w[i]+m;
        dis.push_back(w[i]); dis.push_back(q[i]);
    }
    sort(dis.begin(),dis.end());
    dis.erase(unique(dis.begin(),dis.end()),dis.end());
    for(int i=1;i<=n;i++)
    {
        w[i]=lower_bound(dis.begin(),dis.end(),w[i])-dis.begin()+1;
        q[i]=lower_bound(dis.begin(),dis.end(),q[i])-dis.begin()+1;
    }
    memset(angry,-1,sizeof(angry));
    for(int i=n;i>=1;i--)
    {
        int nxt=sum(q[i]);
        if(nxt) angry[i]=nxt-i-1;
        add(w[i],i);
    }
    for(int i=1;i<=n;i++) printf("%d%c",angry[i],i==n?'\n':' ');
    return 0;
}
