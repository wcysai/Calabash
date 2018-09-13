/*************************************************************************
    > File Name: D.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-07-19 12:54:29
 ************************************************************************/
 
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 15
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m1,m2;
int perm[MAXN];
vector<P> E1,E2;
set<vector<int> > s;
bool connected[MAXN][MAXN],connected2[MAXN][MAXN];
int main()
{
    memset(connected,false,sizeof(connected));
    memset(connected2,false,sizeof(connected2));
    while(scanf("%d%d%d",&n,&m1,&m2)==3)
    {
        E1.clear();E2.clear();s.clear();
        for(int i=0;i<m1;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            E1.push_back(P(u,v));
        }
        for(int i=0;i<m2;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            E2.push_back(P(u,v));
            connected[u][v]=connected[v][u]=true;
        }
        for(int i=1;i<=n;i++) perm[i]=i;
        do
        {
            bool f=true;
            for(int i=0;i<m1;i++)
            {
                P p=E1[i];
                int u=perm[p.F],v=perm[p.S];
                connected2[u][v]=connected2[v][u]=true;
                if(!connected[u][v]) {f=false; break;}
            }
            if(f)
            {
                vector<int> vv(m2);
                for(int i=0;i<m2;i++)
                {
                    P p=E2[i];
                    int u=p.F,v=p.S;
                    if(connected2[u][v]||connected2[v][u]) vv[i]=1; else vv[i]=0;
                }
                s.insert(vv);
            }
            for(int i=0;i<m1;i++)
            {
                P p=E1[i];
                int u=perm[p.F],v=perm[p.S];
                connected2[u][v]=connected2[v][u]=false;
            }
        }while(next_permutation(perm+1,perm+n+1));
        printf("%d\n",(int)s.size());
        for(int i=0;i<m2;i++)
        {
            P p=E2[i];
            int u=p.F,v=p.S;
            connected[u][v]=connected[v][u]=false;
        }
    }
    return 0;
}
