#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,l;
struct fish
{
    int x,y;
}a[MAXN];
struct man
{
    int x,id;
}b[MAXN];
bool cmp2(man p,man q)
{
    return p.x<q.x;
}
vector<int> v;
int sum[MAXN];
int ans[MAXN];
int main()
{
    scanf("%d%d%d",&n,&m,&l);
    for(int i=0;i<n;i++) scanf("%d%d", &a[i].x, &a[i].y);
    for(int i=0;i<m;i++)
    {
        scanf("%d",&b[i].x);b[i].id=i;v.push_back(b[i].x);
    }
    sort(v.begin(),v.end());
    sort(b,b+m,cmp2);
    for(int i=0;i<n;i++)
    {
        if(a[i].y>l) continue;
        int lb=a[i].x-(l-a[i].y),rb=a[i].x+(l-a[i].y);
        int lid=lower_bound(v.begin(),v.end(),lb)-v.begin();sum[lid]++;
        int rid=upper_bound(v.begin(),v.end(),rb)-v.begin();sum[rid]--;
    }
    for(int i=1;i<=m;i++) sum[i]+=sum[i-1];
    for(int i=0;i<m;i++)
        ans[b[i].id]=sum[i];
    for(int i=0;i<m;i++) printf("%d\n",ans[i]);
    return 0;
}
