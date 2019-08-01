#include<bits/stdc++.h>
#define MAXN 10005
#define MAXM 15
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
int n,m,len,tot;
int cnt[MAXM];
int st[MAXM];
int num[MAXN],color[MAXN];
string sub[MAXM][MAXM];
string str;
bool flag;
vector<int> G[MAXN];
void add_edge(int from,int to)
{
    G[from].push_back(to);
}
deque<int> order;
void dfs_visit(int v)
{
	color[v]=1;
	for(int i=0;i<G[v].size();i++)
	{
		int to=G[v][i];
		if(color[to]==0) dfs_visit(to);
		else if(color[to]==1) flag=false;
	}
	color[v]=2;
	order.push_front(v);
}
bool toposort()
{
	flag=true;
	memset(color,0,sizeof(color));
	for(int i=1;i<=n;i++)
		if(color[i]==0)
			dfs_visit(i);
    return flag;
}
int main()
{
    scanf("%d%d ",&n,&m);
    for(int i=0;i<m*(m-1)/2;i++)
    {
        getline(cin,str);
        int x=str[0]-'a',y=str[1]-'a';
        if(x>y) swap(x,y);
        getline(cin,sub[x][y]);
    }
    memset(cnt,-1,sizeof(cnt));
    bool f=true;
    for(int i=0;i<m;i++)
    {
        for(int j=i+1;j<m;j++)
        {
            int cnt0=0,cnt1=0;
            for(int k=0;k<(int)sub[i][j].size();k++) if(sub[i][j][k]-'a'==i) cnt0++; else cnt1++;
            if(cnt[i]!=-1&&cnt[i]!=cnt0) f=false;
            if(cnt[j]!=-1&&cnt[j]!=cnt1) f=false;
            cnt[i]=cnt0; cnt[j]=cnt1;
        }
    }
    int sum=0;
    for(int i=0;i<m;i++) sum+=cnt[i];
    if(sum!=n) f=false;
    if(!f) {puts("-1"); return 0;}
    st[0]=1;
    for(int i=1;i<=cnt[0];i++) num[i]=0;
    for(int i=1;i<m;i++)
    {
        st[i]=st[i-1]+cnt[i-1];
        for(int j=st[i];j<=st[i]+cnt[i]-1;j++) num[j]=i;
    }
    for(int i=0;i<m;i++)
        for(int j=i+1;j<m;j++)
        {
            int last=-1,cnt0=0,cnt1=0,cur;
            for(int k=0;k<(int)sub[i][j].size();k++)
            {
                if(sub[i][j][k]-'a'==i)
                {
                    cur=st[i]+cnt0;
                    cnt0++;
                }
                else
                {
                    cur=st[j]+cnt1;
                    cnt1++;
                }
                if(last!=-1) add_edge(last,cur);
                last=cur;
            }
        }
    if(!toposort()) {puts("-1"); return 0;}
    for(int i=0;i<(int)order.size();i++) printf("%c",'a'+num[order[i]]);
    puts("");
    return 0;
}
