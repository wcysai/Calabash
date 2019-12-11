#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,tot,type,last;
set<P> s[MAXN];
vector<int> pos[MAXN];
vector<int> val[MAXN];
int add[MAXN],need[MAXN];
vector<int> ans;
void add_member(int id)
{
    if(need[id]<=0) return;
    int k=(int)pos[id].size();
    val[id].clear();
    int threshold=(need[id]+k-1)/k;
    for(int j=0;j<k;j++)
    {
        int x=pos[id][j];
        s[x].insert(P(threshold+add[x],id));
        val[id][j]=add[x];
    }
}
void update(int id)
{
    int added=0;
    int k=(int)pos[id].size();
    int threshold=(need[id]+k-1)/k;
    for(int i=0;i<k;i++)
    {
        int x=pos[id][i];
        added+=add[x]-val[id][i];
        s[x].erase(s[x].find(P(threshold+val[id][i],id)));
    }
    need[id]-=added;
    if(need[id]<=0) ans.push_back(id);
    else add_member(id);
}
void add_val(int x,int y)
{
    add[x]+=y;
    while(s[x].size()&&s[x].begin()->F<=add[x]) update(s[x].begin()->S);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        scanf("%d",&type);
        if(type==1)
        {
            int y,k;
            scanf("%d%d",&y,&k); y^=last;
            need[++tot]=y;
            for(int j=0;j<k;j++)
            {
                int x;
                scanf("%d",&x); x^=last;
                pos[tot].push_back(x);
            }
            val[tot].resize(pos[tot].size());
            add_member(tot);
        }
        else
        {
            int x,y;
            scanf("%d%d",&x,&y); x^=last; y^=last;
            add_val(x,y);
            last=(int)ans.size();
            printf("%d",last);
            sort(ans.begin(),ans.end());
            for(auto x:ans) printf(" %d",x);
            puts("");
            ans.clear();
        }
    }
    return 0;
}