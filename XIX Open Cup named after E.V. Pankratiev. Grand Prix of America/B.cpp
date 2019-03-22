#pragma GCC optimize(3)
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/priority_queue.hpp>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int,int> P;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
typedef __gnu_pbds::priority_queue<int,greater<int>,pairing_heap_tag> pq;
int n,m;
char s[MAXN][MAXN],t[MAXN][MAXN];
bool frow[MAXN],fcol[MAXN];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
    for(int i=1;i<=n;i++) scanf("%s",t[i]+1);
    bool f=true;
    memset(frow,false,sizeof(frow));
    memset(fcol,false,sizeof(fcol));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            if(s[i][j]!=t[i][j])
            {
                f=false;
                break;
            }
        }
    if(f)
    {
        puts("1");
        return 0;
    }
    for(int i=1;i<=n;i++)
    {
        int cnt=0;
        for(int j=1;j<=m;j++) if(t[i][j]=='X') cnt++;
        if(cnt>=2) frow[i]=true; 
    }
    for(int i=1;i<=m;i++)
    {
        int cnt=0;
        for(int j=1;j<=n;j++) if(t[j][i]=='X') cnt++;
        if(cnt>=2) fcol[i]=true;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(s[i][j]=='X'&&t[i][j]=='X')
            {
                if(frow[i]) fcol[j]=true;
                if(fcol[j]) frow[i]=true;
            }
        }
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            if(s[i][j]=='O'&&t[i][j]=='X')
            {
                if(frow[i]||fcol[j])
                {
                    puts("0");
                    return 0;
                }
            }
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            if(s[i][j]=='X'&&t[i][j]=='O')
            {
                if(frow[i]&&fcol[j])
                {
                    puts("0");
                    return 0;
                }
            }
        }
    bool f1=false,f2=false;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            if(frow[i]||fcol[j]) continue;
            if(s[i][j]=='O') f1=true;
            if(t[i][j]=='X') f2=true;
        }
    if(f1&&f2) puts("1"); else puts("0");
    return 0;
}

