#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;;
ll K;
vector<P> v;
int main()
{
    scanf("%lld",&K);
    for(int i=1;;i++)
    {
        if(!K) break;
        int rem=K%(i+1);
        if(rem) v.push_back(make_pair(i,rem));
        K-=rem;
    }
    for(auto p:v) printf("%d %d\n",p.F,p.S);
    return 0;
}
