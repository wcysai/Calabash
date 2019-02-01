#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN (1<<20)
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,N,m,n,x,ans;
char str[22];
int a[MAXN]; 
bool valid[MAXN];
int last[MAXN],dis[MAXN];
P res[MAXN];
int p[MAXN],r[MAXN],cnt;
void init(int n)
{
    for(int i=0;i<n;i++)
    {
        p[i]=i;
        r[i]=0;
    }
}
int find(int x)
{
    if(p[x]==x) return x;
    else return p[x]=find(p[x]);
}
void unite(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x==y) return;
    if(r[x]<r[y]) p[x]=y;
    else
    {
        p[y]=x;
        if(r[x]==r[y]) r[x]++;
    }
}
inline bool same(int x,int y)
{
    return find(x)==find(y);
}
inline int boruvka()
{
    ans=0;
    while(cnt>1)
    {
        memset(dis,-1,sizeof(dis));
        for(int i=0;i<n;i++) res[i]=P(INF,0);
        queue<int> que;
        for(int i=0;i<n;i++) if(valid[i]) {que.push(i); dis[i]=0; last[i]=find(p[i]);}
        while(que.size())
        {
            int mask=que.front();que.pop();
            for(int i=0;i<m;i++)
            {
                int to=mask^(1<<i);
                if(dis[to]==-1) {dis[to]=dis[mask]+1; last[to]=last[mask]; que.push(to);}
                else if(last[to]==last[mask]) continue;
                else res[last[mask]]=min(res[last[mask]],P(dis[mask]+dis[to]+1,last[to]));
            }
        }
        for(int i=0;i<n;i++)
        {
            if(res[i].F<INF)
            {
                if(same(i,res[i].S)) continue;
                else 
                {
                    ans+=res[i].F;
                    unite(i,res[i].S);
                    cnt--;
                }
            }
        }
    }
    return ans;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&m,&N);
        memset(valid,false,sizeof(valid));
        cnt=0;
        for(int i=0;i<N;i++)
        {
            scanf("%s",str);
            x=0;
            for(int j=0;j<m;j++) if(str[j]=='L') x=x*2; else x=x*2+1;
            if(!valid[x]) cnt++;
            valid[x]=true;
        }
        n=(1<<m);
        init(n);
        printf("%d\n",boruvka());
    }
    return 0;
}

