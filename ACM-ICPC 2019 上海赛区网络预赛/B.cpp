#include<bits/stdc++.h>
#define MAXN 305
#define MAXM 150005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,N,M;
vector<int> v;
int main()
{
    scanf("%d",&T);
    for(int tot=1;tot<=T;tot++)
    {
        scanf("%d%d",&N,&M);
        v.clear();
        for(int i=0;i<M;i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            v.push_back(x-1); v.push_back(y);
        }
        sort(v.begin(),v.end(),greater<int>());
        int state=0,ans=0;
        for(int i=0;i<(int)v.size();i++)
        {
            if(!state) ans+=v[i];
            else ans-=v[i];
            state=!state;
        }
        printf("Case #%d: %d\n",tot,ans);
    }
    return 0;
}
