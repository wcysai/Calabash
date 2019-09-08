#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,k,a[MAXN],b[MAXN],cnt[MAXN];
vector<int> beauty[MAXN],smart[MAXN];
bool used[MAXN];
int main()
{
	memset(used,false,sizeof(used));
	memset(cnt,0,sizeof(cnt));
    scanf("%d%d%d",&n,&m,&k);
    for(int i=0;i<m;i++)
    {
		int x,y;
		scanf("%d%d",&x,&y);
    }
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&a[i]);
		beauty[a[i]].push_back(i);
		cnt[a[i]]++;
	}
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&b[i]);
		smart[b[i]].push_back(i);
	}
	queue<int> que;
	for(int i=1;i<=n;i++) if(beauty[i].size()==1) que.push(i);
	while(que.size())
	{
		int color1=que.front(); que.pop();
		if(cnt[color1]!=1) continue;
		int v;
		for(auto x:beauty[color1])
		{
			if(a[x]==color1)
			{
				v=x;
				break;
			}
		}
		int color2=b[v];
		vector<int> upd; upd.clear();
		for(auto to:smart[color2])
		{
			if(to==v) continue;
			upd.push_back(a[to]);
			cnt[a[to]]--;
			a[to]=a[v];
			cnt[a[to]]++;
		}
		for(auto c:upd)
		{
			if(used[c]) continue;
			if(cnt[c]==1)
			{
				que.push(c);
				used[c]=true;
			}
		}
	}
	puts("TAK");
	for(int i=1;i<=n;i++) printf("%d%c",a[i],i==n?'\n':' ');
    return 0;
}

