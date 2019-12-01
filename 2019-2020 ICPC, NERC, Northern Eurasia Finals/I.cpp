#include<bits/stdc++.h>
#define MAXN 205
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define terminate fakodsl
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n;
bool smaller[MAXN][MAXN];
bool vis[MAXN][MAXN];
string str;
int ord[12] = {0, 6, 5, 4, 3, 2, 1};
bool is_smaller(int u,int v)
{
    if(u>v) return !is_smaller(v,u);
    if(vis[u][v]) return smaller[u][v];
    printf("? %d %d\n",u,v);
    fflush(stdout);
    vis[u][v]=true;
    cin>>str;
    if(str[0]=='<') return smaller[u][v]=true; else return smaller[u][v]=false;
}
void terminate()
{
    printf("!\n");
    fflush(stdout);
}
vector<pair<int, int>> prs;
vector<int> v;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        prs.clear(); v.clear();
        scanf("%d",&n);
        memset(vis,false,sizeof(vis));
        for(int i=1;i<=n;i++)
        {
            if(is_smaller(i,i+n))
            {
                prs.emplace_back(i, i+n);
            }
            else
            {
                prs.emplace_back(i+n, i);
            }
        }
        sort(prs.begin(), prs.end(), [] (pair<int, int> a, pair<int, int> b) {
            return !is_smaller(a.first, b.first);
        });
        for(int i=1;i<n;i++) v.push_back(prs[i].first);
        for(int i=1;i<n;i++) v.push_back(prs[i].second);
        sort(v.begin(),v.end(),is_smaller); reverse(v.begin(), v.end());
        is_smaller(prs[0].first,v[n-2]);
        terminate();
    }
    return 0;
}
