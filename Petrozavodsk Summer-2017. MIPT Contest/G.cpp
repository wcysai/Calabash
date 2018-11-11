/*************************************************************************
    > File Name: G.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-11-11 15:31:32
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
int n,tot;
int deg[MAXN],cycle[MAXN];
void euler(int v)
{
    for(;deg[v]<2;)
    {
        deg[v]++;
        if(deg[v]==1) euler(2*v%(n/2));
        else euler((2*v+1)%(n/2));
    }
    cycle[tot++]=v;
}
int main()
{
    scanf("%d",&n);
    if(n==2) {puts("10"); return 0;}
    euler(0);
    reverse(cycle,cycle+tot);
    --tot;
    for(int i=1;i<=tot;i++)
    {
        if((2*cycle[i])%(n/2)==cycle[(i+1)%n]) printf("0");
        else printf("1");
    }
    puts("");
    return 0;
}

