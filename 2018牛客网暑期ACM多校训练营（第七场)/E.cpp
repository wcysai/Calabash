/*************************************************************************
    > File Name: E.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com
    > Created Time: 2018-08-09 12:11:50
 ************************************************************************/
 
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int k;
vector<P> E;
int comb[505],comb2[505];
int vis[1000005];
int main()
{
    comb[3]=1;
    for(int i=4;i<=300;i++) comb[i]=1LL*i*comb[i-1]/(i-3);
    comb2[4]=1;
    for(int i=5;i<=300;i++) comb2[i]=1LL*i*comb2[i-1]/(i-4);
    //printf("%d\n",comb[300]);
    scanf("%d",&k);
    E.clear();
    for(int sz=75;sz>=4;sz--)
    {
        if(k<comb2[sz]) continue;
        if((75-sz+1)*comb2[sz]<k) continue;
        int kk=k-comb2[sz];
        for(int i=0;i<=kk;i++) vis[i]=0;
        queue<P> que;
        while(que.size()) que.pop();
        que.push(P(kk,75));
        vis[kk]=75;
        while(que.size())
        {
            if(vis[0]) break;
            P p=que.front();que.pop();
            for(int j=3;j<sz;j++)
            {
                int nxt=p.F-comb[j];
                if(nxt<0||vis[nxt]||p.S==sz+1) continue;
                vis[nxt]=p.S-1;
                que.push(P(nxt,p.S-1));
            }
        }
        if(!vis[0]) continue;
        for(int i=2;i<=sz;i++)
            for(int j=1;j<i;j++)
                E.push_back(P(i,j));
        for(int i=75;i>sz;i--)
        {
            E.push_back(P(i,1));
            E.push_back(P(i,2));
        }
        int now=0,cur=vis[0];
        while(now!=kk)
        {
            for(int j=3;j<sz;j++)
            {
                if(now+comb[j]>kk) break;
                if(vis[now+comb[j]]==cur+1)
                {
                    for(int p=3;p<=j;p++) E.push_back(P(cur+1,p));
                    now+=comb[j];cur++;
                    break;
                }
            }
        }
        printf("75 %d\n",(int)E.size());
        for(int j=0;j<(int)E.size();j++) printf("%d %d\n",E[j].F,E[j].S);
        return 0;
    }
    return 0;
}
