#include<bits/stdc++.h>
#define MAXN 15
#define MAXM 205
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef pair<int,int> P;
bool has[MAXM];
int in[MAXM],out[MAXM],notin[MAXM],notout[MAXM];
int n,k,tot,ans;
P edges[MAXM];
int a[MAXN][MAXN];
void dfs(int now)
{
    if(now==tot)
    {
        ans++;
        return;
    }
    int x=edges[now].F,y=edges[now].S;
    if(!(out[x]&in[y]))
    {
        notout[x]^=(1<<y); notin[y]^=(1<<x);
        dfs(now+1);
        notout[x]^=(1<<y); notin[y]^=(1<<x);
    }
    if(!(notout[x]&out[y])&&!(in[x]&notin[y])&&a[x][y])
    {
        out[x]^=(1<<y); in[y]^=(1<<x);
        dfs(now+1);
        out[x]^=(1<<y); in[y]^=(1<<x);
    }
}
void solve(int lmask,int rmask)
{
    vector<int> v; v.clear();
    for(int i=0;i<n;i++) if(((lmask^rmask)>>i)&1) v.push_back(i);
    int sz=(int)v.size();
    for(int i=0;i<sz;i++)
        for(int j=0;j<sz;j++)
            a[i][j]=1;
    for(int i=0;i<(1<<n);i++)
    {
        if(!has[i]) continue;
        if((lmask&i)!=lmask) return;
        if((rmask&i)!=i) return;
        for(int j=0;j<sz;j++)
            for(int k=0;k<sz;k++)
                if(((i>>v[j])&1)&&!((i>>v[k])&1)) a[k][j]=0;
    }
    for(int i=0;i<sz;i++) notin[i]=notout[i]=0,in[i]=out[i]=(1<<i);
    tot=0;
    for(int i=0;i<sz;i++)
    {
        for(int j=0;j<i;j++)
        {
            edges[tot++]=P(j,i);
            edges[tot++]=P(i,j);
        }
    }
    dfs(0);
}
int main()
{
    scanf("%d%d",&n,&k);
    memset(has,false,sizeof(has));
    for(int i=0;i<k;i++)
    {
        int x;
        scanf("%d",&x);
        has[x]=true;
    }
    ans=0;
    for(int i=0;i<(1<<n);i++)
    {
        for(int j=0;j<(1<<n);j++)
        {
            if((i&j)!=i) continue;
            solve(i,j);
        }
    }
    printf("%d\n",ans);
    return 0;
}


