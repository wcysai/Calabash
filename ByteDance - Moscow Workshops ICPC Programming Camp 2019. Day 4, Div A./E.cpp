#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define MAXN 100005
#define INF 1000000001
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T;
map<string,int> mp;
int tot;
string str[32][3];
set<string> s;
set<string> m3,m4,m5,m6;
vector<string> group[8];
map<string,int> grnum;
map<string,int> score,goal;
vector<P> ppair;
int ans;
map<pair<string,string>,int> ppp;
bool use[32],grp[32];
int contestcnt[4];
void fuck()
{
    printf("There are no possible championships for list #%d!\n",tot);
}
void print(int x)
{
    if(x==1) printf("There is 1 possible championship for list #%d.\n",tot);
    else printf("There are %d possible championships for list #%d.\n",x,tot);
}
bool cmp(string x,string y)
{
    if(score[x]!=score[y]) return score[x]>score[y];
    if(goal[x]!=goal[y]) return goal[x]>goal[y];
    return x<y;
}
void check()
{
    score.clear();goal.clear();
    memset(grp,false,sizeof(grp));
    memset(contestcnt,0,sizeof(contestcnt));
    for(int i=0;i<31;i++)
    {
        int u=str[i][1][0]-'0',v=str[i][1][2]-'0';
        if(!use[i]) continue;
        if(grnum[str[i][0]]!=grnum[str[i][2]]) continue;
        contestcnt[grnum[str[i][0]]]++;
        grp[i]=true;
        if(u==v) {score[str[i][0]]++; score[str[i][2]]++;}
        else if(u>v) score[str[i][0]]+=3;
        else score[str[i][2]]+=3;
        goal[str[i][0]]+=u-v;
        goal[str[i][2]]+=v-u;
    }
    for(int i=0;i<4;i++) if(contestcnt[i]!=6) return;
    for(int i=0;i<4;i++) sort(group[i].begin(),group[i].end(),cmp);
    for(int i=0;i<4;i++)
    {
        if(m3.count(group[i][0])||m3.count(group[i][1])||!m3.count(group[i][2])||!m3.count(group[i][3])) return;
    }
    set<string> cur;cur.clear();
    for(auto p:mp) if(!m3.count(p.F)) cur.insert(p.F);
    for(int i=0;i<31;i++)
    {
        if(grp[i]) continue;
        bool f=false;
        if(m4.count(str[i][0])&&!m4.count(str[i][2])) f=true;
        if(m4.count(str[i][2])&&!m4.count(str[i][0])) f=true;
        if(!f) continue;
        if(!cur.count(str[i][0])||!cur.count(str[i][2])) return;
        int f1=0,f2=0;
        for(int j=0;j<4;j++) 
        {
            if(group[j][0]==str[i][0]) 
            {
                f1=1;
                break;
            }
            else if(group[j][1]==str[i][0])
            {
                f1=2;
                break;
            }
        }
        for(int j=0;j<4;j++) 
        {
            if(group[j][0]==str[i][2]) 
            {
                f2=1;
                break;
            }
            else if(group[j][1]==str[i][2])
            {
                f2=2;
                break;
            }
        }
        if(!f1||!f2) return;
        if(f1==f2) return;
        int u=str[i][1][0]-'0',v=str[i][1][2]-'0';
        if(u==v) return;
        if(u>v)
        {
            if(m4.count(str[i][0])) return;
            cur.erase(cur.find(str[i][2]));
        }
        else
        {
            if(m4.count(str[i][2])) return;
            cur.erase(cur.find(str[i][0]));
        }
    }
    if(cur.size()!=4) return;
    for(int i=0;i<31;i++)
    {
        if(grp[i]) continue;
        int u=str[i][1][0]-'0',v=str[i][1][2]-'0';
        bool f=false;
        if(m5.count(str[i][0])&&m6.count(str[i][2])) f=true;
        if(m5.count(str[i][2])&&m6.count(str[i][0])) f=true;
        if(!f) continue;
        if(!cur.count(str[i][0])||!cur.count(str[i][2])) return;
        if(u==v) return;
        if(u>v)
        {
            if(m5.count(str[i][0])) return;
            cur.erase(cur.find(str[i][2]));
        }
        else
        {
            if(m5.count(str[i][2])) return;
            cur.erase(cur.find(str[i][0]));
        }
    }
    if(cur.size()!=2) return;
    for(int i=0;i<31;i++)
    {
        if(grp[i]) continue;
        bool f=false;
        if(m6.count(str[i][0])&&m6.count(str[i][2])) f=true;
        if(!f) continue;
        if(!cur.count(str[i][0])||!cur.count(str[i][2])) return;
        int u=str[i][1][0]-'0',v=str[i][1][2]-'0';
        if(u==v) return;
        if(u>v) cur.erase(cur.find(str[i][2])); else cur.erase(cur.find(str[i][0]));
    }
    if(cur.size()!=1) return;
    ans++;
}
int main()
{
    scanf("%d",&T);
    for(tot=1;tot<=T;tot++)
    {
        s.clear();mp.clear();m3.clear();m4.clear();m5.clear();m6.clear();grnum.clear();
        ans=0;
        bool f=true;
        for(int j=0;j<4;j++) group[j].clear();
        for(int i=0;i<31;i++)
        {
            cin>>str[i][0];
            cin>>str[i][1];
            cin>>str[i][2];
            if(str[i][0]>str[i][2])
            {
                swap(str[i][0],str[i][2]); 
                swap(str[i][1][0],str[i][1][2]);
            }
            if(str[i][0]==str[i][2]) {f=false; break;}
            mp[str[i][0]]++;mp[str[i][2]]++;
            s.insert(str[i][0]);s.insert(str[i][2]);
        }
        if(s.size()!=16) {fuck(); continue;}
        for(auto p:mp)
        {
            if(p.S<3||p.S>6)
            {
                f=false;
                break;
            }
            if(p.S==3) m3.insert(p.F);
            else if(p.S==4) m4.insert(p.F);
            else if(p.S==5) m5.insert(p.F);
            else m6.insert(p.F);
        }
        if(m3.size()!=8) f=false;
        else if(m4.size()!=4) f=false;
        else if(m5.size()!=2) f=false;
        else if(m6.size()!=2) f=false;
        if(!f) {fuck(); continue;}
        int gnum=0;
        for(int i=0;i<31;i++)
        {
            if(m3.count(str[i][0])&&m3.count(str[i][2]))
            {
                grnum[str[i][0]]=grnum[str[i][2]]=gnum;
                group[gnum].push_back(str[i][0]);
                group[gnum++].push_back(str[i][2]);
            }
        }
        if(gnum!=4) {fuck(); continue;}
        for(int i=0;i<31;i++)
        {
            if(m3.count(str[i][0])||m3.count(str[i][2]))
            {
                if(grnum.find(str[i][0])==grnum.end())
                {
                    grnum[str[i][0]]=grnum[str[i][2]];
                    group[grnum[str[i][0]]].push_back(str[i][0]);
                }
                if(grnum.find(str[i][2])==grnum.end())
                {
                    grnum[str[i][2]]=grnum[str[i][0]];
                    group[grnum[str[i][2]]].push_back(str[i][2]);
                }
            }
        }
        for(int i=0;i<4;i++)
        {
            sort(group[i].begin(),group[i].end());
            group[i].erase(unique(group[i].begin(),group[i].end()),group[i].end());
        }
        ppp.clear();ppair.clear();
        for(int i=0;i<31;i++)
        {
            pair<string,string> pp=make_pair(str[i][0],str[i][2]);
            if(pp.F>pp.S) swap(pp.F,pp.S);
            if(ppp.find(pp)==ppp.end()) ppp[pp]=i;
            else if(ppp[pp]==-1) {f=false; break;}
            else {ppair.push_back(make_pair(ppp[pp],i)); ppp[pp]=-1;}
        }
        int n=(int)ppair.size();
        for(int i=0;i<(1<<n);i++)
        {
            memset(use, true, sizeof(use));
            bool flag=true;
            for (int j = 0; j < n; j++)
            {
                int u=ppair[j].F,v=ppair[j].S;
                if(str[u][1]==str[v][1])
                {
                    if(i&(1<<j)) use[ppair[j].F]=false;
                    else flag=false;
                }
                else
                {
                    if (i & (1 << j)) use[ppair[j].F] = false; else use[ppair[j].S] = false;
                }
            }
            if(flag) check();
        }
        if(!f||!ans) fuck(); else print(ans);
    }
    return 0;
}
