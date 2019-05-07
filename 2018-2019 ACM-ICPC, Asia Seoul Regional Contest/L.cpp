#include<bits/stdc++.h>
#define MAXN 2005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,w,h;
int q[MAXN];//working day for each person
int d[MAXN];//person working for each day
int rest[MAXN];
int work[MAXN];
priority_queue<P> pque;
vector<int> workdays[MAXN];
int main()
{
    scanf("%d%d%d%d",&n,&m,&w,&h);
    for(int i=1;i<=n;i++) scanf("%d",&q[i]);
    for(int i=1;i<=m;i++) scanf("%d",&d[i]);
    for(int i=1;i<=n;i++) pque.push(P(q[i],i));
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(work[j])
            {
                work[j]--;
                q[j]--; d[i]--;
                if(d[i]<0)
                {
                    assert(0);
                    exit(0);
                }
                if(!work[j]) rest[j]=h+1;
            }
        }
        for(int j=1;j<=d[i];j++)
        {
            if(!pque.size())
            {
                puts("-1");
                exit(0);
            }
            P p=pque.top(); pque.pop();
            if(p.F==0)
            {
                puts("-1");
                exit(0);
            }
            q[p.S]--; 
            workdays[p.S].push_back(i);
            if(w>1) work[p.S]=w-1; else rest[p.S]=h+1;
        }
        for(int j=1;j<=n;j++)
        {
            if(rest[j])
            {
                rest[j]--;
                if(!rest[j]) pque.push(P(q[j],j));
            }
        }
    }
    for(int i=1;i<=n;i++) if(q[i]!=0) {puts("-1"); exit(0);}
    puts("1");
    for(int i=1;i<=n;i++)
    {
        for(auto x:workdays[i]) printf("%d ",x);
        puts("");
    }
    return 0;
}
