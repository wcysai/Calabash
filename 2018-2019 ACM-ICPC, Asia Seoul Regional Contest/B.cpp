#include<bits/stdc++.h>
#define MAXN 505
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define rank dasokdsao
using namespace std;
int n,m;
int rank[MAXN][MAXN];
int prefer[MAXN][MAXN];
int s[MAXN][MAXN];
vector<int> ans;
int main()
{
    scanf("%d%d",&m,&n);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++) scanf("%d",&rank[i][j]);
        for(int j=1;j<=m;j++)
            for(int k=j+1;k<=m;k++)
            {
                if(rank[i][j]==rank[i][k]) continue;
                if(rank[i][j]==0||rank[i][k]==0)
                {
                    if(rank[i][j]==0) prefer[k][j]++; else prefer[j][k]++;
                    continue;
                }
                if(rank[i][j]<rank[i][k]) prefer[j][k]++; else prefer[k][j]++;
            }
    }
    for(int i=1;i<=m;i++)
        for(int j=1;j<=m;j++)
            if(prefer[i][j]>prefer[j][i]) s[i][j]=prefer[i][j]; else s[i][j]=0;
    for(int k=1;k<=m;k++)
        for(int i=1;i<=m;i++)
            for(int j=1;j<=m;j++)
                s[i][j]=max(s[i][j],min(s[i][k],s[k][j]));
    for(int i=1;i<=m;i++)
    {
        bool f=true;
        for(int j=1;j<=m;j++)
        {
            if(i==j) continue;
            if(s[j][i]>s[i][j]) {f=false; break;}
        }
        if(f) ans.push_back(i);
    }
    for(auto x:ans) printf("%d ",x);
    puts("");           
    return 0;
}
