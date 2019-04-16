#include<bits/stdc++.h>
#define MAXN 130
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,ans;
int d[MAXN],pre[MAXN];
bool reach[MAXN];
vector<int> steps,fans;
string str=
"000000\n100000\n110000\n111000\n111100\n101100\n001100\n001110\n001010\n101010\n101011\n101001\n001001\n011001\n011101\n011111\n111111\n110111\n110101\n100101\n000101\n000111\n000011\n010011\n010010\n010110\n010100\n";
void dfs(int v,bool saveans=false)
{
    if(saveans)
    {
        if(ans==(int)steps.size()) fans=steps;
    }
    else ans=max(ans,(int)steps.size());
    vector<int> reached; reached.clear();
    for(int i=0;i<n;i++)
    {
        int newmask=v^(1<<i);
        if(reach[newmask]) continue;
        reach[newmask]=true;
        reached.push_back(newmask);
    }
    for(auto u:reached)
    {
        steps.push_back(u);
        dfs(u,saveans);
        steps.pop_back();
    }
    for(auto u:reached) reach[u]=false;
}
int main()
{
    scanf("%d",&n);
	if(n==6)
	{
		printf("27\n");
		cout<<str<<endl;
		return 0;
	}
    reach[0]=true;
    steps.push_back(0);
    dfs(0);
    memset(reach,false,sizeof(reach));
    reach[0]=true;
    dfs(0,true);
    printf("%d\n",ans);
    for(auto v:fans)
    {
        for(int i=n-1;i>=0;i--) printf("%d",(v>>i)&1);
        puts("");
    }
    return 0;
}
