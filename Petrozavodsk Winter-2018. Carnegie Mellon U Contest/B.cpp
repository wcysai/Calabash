#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
int N,Q,P;
int d;
set<int> pos;
int main()
{
    scanf("%d%d%d",&N,&Q,&P);
    for(int i=0;i<N;i++)
    {
        int x;
        scanf("%d",&x);
        pos.insert(x);
    }
    for(int i=0;i<Q;i++)
    {
        int type;
        scanf("%d",&type);
        if(type==1)
        {
            int x;scanf("%d",&x);
            pos.insert(x+d);
        }
        else
        {
            pos.erase(pos.begin());
            pos.insert(P+d);d++;
        }
    }
    for(auto it:pos) printf("%d ",it-d);
    return 0;
}
