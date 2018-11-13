/*************************************************************************
    > File Name: E.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-11-13 21:56:04
 ************************************************************************/

#pragma GCC optimize(3)// Thanks,Acesrc!
#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q,cnt[MAXN][MAXN],tot;
char str[MAXN+1];
int nxt[MAXN*MAXN*4];
char ch[MAXN*MAXN*4];
int inv(int x)
{
    return x^1;
}
int trans(int x)
{
    return x^2;
}
int origin(int x)
{
    return (x>>2);
}
void link(int x,int y)
{
    nxt[x]=y;
    nxt[inv(y)]=inv(x);
}
int go(int x,int y)
{
    int now=x;
    while(y--) now=nxt[now];
    return now;
}
void work(int st1,int st2,int dist,int e,int *U,int *u)
{
    int cur=go(st1,dist);
    for(int i=1;i<=e;i++,cur=nxt[cur]) U[i]=trans(cur);
    cur=go(st2,dist);
    for(int i=1;i<=e;i++,cur=nxt[cur]) u[i]=trans(cur);
    for(int i=1;i<=e;i++)
    {
        if(origin(nxt[u[i]])==origin(U[i])) u[i]=inv(u[i]);
        if(origin(nxt[U[i]])!=origin(u[i])) U[i]=inv(U[i]);
    }
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=0;i<=n;i++)
    {
        if(i) scanf("%s",str+1);
        for(int j=0;j<=n;j++)
        {
            cnt[i][j]=++tot;
            if(i!=0&&j!=0) ch[tot]=str[j];
        }
    }
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=n;j++)
        {
            if(j!=n) link(cnt[i][j]*4,cnt[i][j+1]*4);
            if(i!=n) link(cnt[i][j]*4+2,cnt[i+1][j]*4+2);
        }
    }
    for(int i=0;i<q;i++)
    {
        int x,y,e;
        scanf("%d%d%d",&x,&y,&e);
        static int u[MAXN],U[MAXN],l[MAXN],L[MAXN],r[MAXN],R[MAXN],d[MAXN],D[MAXN];
        work(cnt[x-1][0]*4,cnt[x][0]*4,y,e,U,u);
        work(cnt[0][y+e]*4+2,cnt[0][y+e-1]*4+2,x,e,R,r);
        work(cnt[x+e][0]*4,cnt[x+e-1][0]*4,y,e,D,d);
        work(cnt[0][y-1]*4+2,cnt[0][y]*4+2,x,e,L,l);
        for(int i=1;i<=e;i++)
        {
            link(U[i],r[i]);
            link(R[i],d[e-i+1]);
            link(D[i],l[i]);
            link(L[i],u[e-i+1]);
        }
    }
    for(int i=1;i<=n;i++)
    {
        int u=cnt[i][0]*4;
        for(int j=1;j<=n;j++)
        {
            u=nxt[u];
            putchar(ch[u>>2]);
        }
        puts("");
    }
    return 0;
}

