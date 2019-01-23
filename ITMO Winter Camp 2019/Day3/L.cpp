#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 10007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
map<vector<int>,int> mp;
vector<int> states[MAXN];
int R,C;
vector<int> a;
int dfs(int now,int last)
{
    if(now==C+1) 
    {
        mp[a]=++tot;
        states[tot]=a;
    }
    for()
}
int main()
{
    return 0;
}

