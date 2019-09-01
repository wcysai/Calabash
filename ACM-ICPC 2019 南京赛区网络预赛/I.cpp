#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int N,y;
vector<int> t;
vector<int> can[MAXN];
int main()
{
    while(scanf("%d%d",&N,&y)==2)
    {
        t.clear();
        for(int i=0;i<N;i++)
        {
            int x;
            scanf("%d",&x);
            t.push_back(x);
        }
        sort(t.begin(),t.end());
        for(int i=1;i<=y;i++)
        {
            int cnt=y/i;
            int mx=0;
            for(int j=N-1;j>=max(0,N-cnt);j--) mx=max(mx,t[j]+(N-j)*i);
            if(N-cnt>0) mx=max(mx,t[N-cnt-1]+y);
            printf("%d%c",mx,i==y?'\n':' ');
        }
    }
    return 0;
}
