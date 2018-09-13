/*************************************************************************
    > File Name: I.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-08-08 12:14:55
 ************************************************************************/

#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 300005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,ans;
int deg[MAXN],to[MAXN],type[MAXN],save[MAXN];
bool used[MAXN];
int st[MAXN];
char s[20];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) deg[i]=0,save[i]=0;
        memset(used,false,sizeof(used));
        ans=0;
        vector<int> p; p.clear();
        for(int i=1;i<=n;i++)
        {
            int x;
            scanf("%d",&x);assert(x!=i);scanf("%s",s);to[i]=x;deg[x]++;
            if(s[0]=='v') type[i]=0; else type[i]=1;
        }
        int tot=0;
        for(int i=1;i<=n;i++) if(deg[i]==0) st[tot++]=i;
        while(tot)
        {
            int cur=st[tot-1];
            //printf("cur=%d\n",cur);
            used[cur]=true;
            if(type[cur]==0) save[to[cur]]+=save[cur]+1;
            tot--;
            deg[to[cur]]--;
            if(deg[to[cur]]==0) st[tot++]=to[cur]; 
        }
        for(int i=1;i<=n;i++)
        {
            if(used[i]) continue;
            int cur=i,res=0,cnt=0;
            while(!used[cur])
            {
                used[cur]=true;
                if(type[cur]==1)
                {
                    cnt++;
                    res+=save[to[cur]];
                }
                if(used[to[cur]]) break;
                cur=to[cur];
            }
            if(cnt==1) 
            {
                //printf("%d\n",res);
                ans+=1+res;
            }
        }
        printf("%d %d\n",0,ans);
    }
}
