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
int T,n,x;
multiset<int> ms;
vector<int> ans,save;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        ms.clear();ans.clear();
        scanf("%d",&n);
        for(int i=1;i<(1<<n);i++)
        {
            scanf("%d",&x);
            ms.insert(x);
        }
        bool f=true;
        for(int i=1;i<=n;i++)
        {
            if(!f) break;
            int now=*ms.begin();
            save.clear();
            ans.push_back(now);ms.erase(ms.begin());
            while(ms.size())
            {
                int v=*ms.begin();
                save.push_back(v);
                if(!ms.count(v+now)) {f=false; break;}
                ms.erase(ms.find(v+now));
                ms.erase(ms.begin());
            }
            for(auto v:save) ms.insert(v);
        }
        if(!f)  {puts("NO"); continue;}
        for(auto v:ans) printf("%d ",v);
        puts("");
    }
    return 0;
}

