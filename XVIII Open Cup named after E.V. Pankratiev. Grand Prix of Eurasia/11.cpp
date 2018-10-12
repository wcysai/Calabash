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
int n,m,cnt,ans;
struct edge{int to,type;};
vector<edge> G[45];
int mat[45][45];
bitset<44> table1[1<<20],table2[1<<20];
bitset<44> has1[20],has2[20];
vector<int> yes,no;
int dp1[1<<20],dp2[1<<20],opt1[1<<20],opt2[1<<20],optmask[1<<20];
bool know[43];
int solve1(int mask)
{
    if(mask==(1<<cnt)-1) return 0;
    if(table1[mask]==0) return 0;
    if(dp1[mask]!=-1) return dp1[mask];
    for(int j=0;j<cnt;j++)
    {
        if(!((mask>>j)&1))
        {
            int t=0;
            for(int i=0;i<n-1-cnt;i++) {
                if (table1[mask][i] == 0) continue;
                if (mat[yes[j]][no[i]] != 0 && mat[yes[j]][no[i]] == mat[1][yes[j]]) t++;
            }
            int to=solve1(mask|(1<<j));
            if(to+t>=dp1[mask])
            {
                dp1[mask]=to+t;
                opt1[mask]=j;
            }
        }
    }
    return dp1[mask];
}
int solve2(int mask)
{
    if(mask==0) return 0;
    if(table2[mask]==0) return 0;
    if(dp2[mask]!=-1) return dp2[mask];
    for(int i=0;i<cnt;i++)
    {
        if(table2[mask][i]==0) continue;
        int t=0,newmask=0;
        for (int j = 0; j < (n - 1 - cnt); j++)
        {
            if ((mask >> j) & 1)
            {
                if (mat[yes[i]][no[j]] != 0 && mat[1][yes[i]] == mat[yes[i]][no[j]]) t++;
                if (!mat[yes[i]][no[j]]) newmask|=(1<<j);
            }
        }
        assert(newmask!=mask);
        int to=solve2(newmask);
        if (to + t >= dp2[mask])
        {
            dp2[mask] = to + t;
            opt2[mask] = i;
            optmask[mask]=newmask;
        }
    }
    return dp2[mask];
}
int main()
{
    scanf("%d%d",&n,&m);
    memset(mat,0,sizeof(mat));
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        G[u].push_back((edge){v,w});G[v].push_back((edge){u,w});
        mat[u][v]=mat[v][u]=(w==1?1:2);
    }
    cnt=(int)G[1].size();ans=0;
    memset(know,false,sizeof(know));
    for(int i=0;i<(int)G[1].size();i++)
    {
        ans+=1-G[1][i].type;
        yes.push_back(G[1][i].to);
        know[G[1][i].to]=true;
    }
    for(int i=2;i<=n;i++) if(!know[i]) no.push_back(i);
    if(cnt==0)
    {
        printf("%.15Lf\n",(long double)ans/(n-1));
        return 0;
    }
    else if(n-1-cnt==0)
    {
        printf("%.15Lf\n",(long double)ans/(n-1));
        for(auto it:yes) printf("%d ",it);
        return 0;
    }
    if(cnt<=20)
    {
        for(int i=0;i<cnt;i++)
        {
            has1[i].reset();
            for(int j=0;j<n-1-cnt;j++)
                if(mat[yes[i]][no[j]]) has1[i].set(j);
        }
        for(int i=0;i<(1<<cnt);i++)
        {
            table1[i].reset();
            for(int j=0;j<cnt;j++) {
                if ((i >> j) & 1) table1[i] |= has1[j];
            }
            table1[i]=~table1[i];
        }
        memset(dp1,-1,sizeof(dp1));
        printf("%.15Lf\n",((long double)ans+solve1(0))/(n-1));
        int now=0;
        while(now!=(1<<cnt)-1)
        {
            printf("%d ",yes[opt1[now]]);
            now^=(1<<opt1[now]);
        }
    }
    else
    { 
        for(int i=0;i<n-1-cnt;i++)
        {
            has2[i].reset();
            for(int j=0;j<cnt;j++)
                if(mat[no[i]][yes[j]]) has2[i].set(j);
        }
        for(int i=0;i<(1<<(n-1-cnt));i++)
        {
            for(int j=0;j<(n-1-cnt);j++)
            {
                if((i>>j)&1) table2[i]|=has2[j];
            }
        }
        memset(dp2,-1,sizeof(dp2));
        printf("%.15Lf\n",((long double)ans+solve2((1<<(n-1-cnt))-1))/(n-1));
        int now=(1<<(n-cnt-1))-1;
        bool used[42];
        memset(used,false,sizeof(used));
        while(now!=0)
        {
            printf("%d ",yes[opt2[now]]);
            used[opt2[now]]=true;
            now=optmask[now];
        }
        for(int id=0;id<(int)yes.size();id++) if(!used[id]) printf("%d ",yes[id]);
    }
    return 0;
}
/*
 7 8
 1 2 0
 1 3 0
 2 4 0
 4 5 0
 3 4 1
 2 5 1
 5 7 1
 1 7 1
 */
