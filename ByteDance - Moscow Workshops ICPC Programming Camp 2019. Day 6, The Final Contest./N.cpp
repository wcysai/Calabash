#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAXN 300005
#define INF 1000000001
#define MOD 998244353
#define F first
#define S second
int n,q;
int odd;
int f[MAXN],g[MAXN];
void adjust(int x)
{
    if(x&1) odd++; else odd--;
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=0;i<q;i++)
    {
        int t,u,v;
        scanf("%d%d%d",&t,&u,&v);
        if(t==1)
        {
            if(u>v)
            {
                f[u]++;
                g[v]++;
            } else
            {
                f[v]++;
                g[u]++;
            }
        } else {
            if (u > v) {
                f[u]--;
                g[v]--;
            } else {
                f[v]--;
                g[u]--;
            }
        }
        if(u>v) {adjust(f[u]); adjust(g[v]);}
        else {adjust(f[v]); adjust(g[u]);}
        if(odd )puts("0"); else puts("1");
    }
}
