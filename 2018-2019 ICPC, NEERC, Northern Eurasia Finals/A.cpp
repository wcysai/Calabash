#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
bool dp[6][6][256][256];
void upd(bool &a){a=true;}
vector<P> v1,v2;
int t;
int main()
{
    for(int i=0;i<=23;i++) {v1.push_back(P(25,i)); v1.push_back(P(i,25));}
    for(int i=24;i+2<=200;i++) {v1.push_back(P(i+2,i)); v1.push_back(P(i,i+2));}
    for(int i=0;i<=13;i++) {v2.push_back(P(15,i)); v2.push_back(P(i,15));}
    for(int i=14;i+2<=200;i++) {v2.push_back(P(i+2,i)); v2.push_back(P(i,i+2));}
    memset(dp,false,sizeof(dp));
    dp[0][0][0][0]=true;
    for(int k=0;k<=4;k++)
    {
        for(int win=max(k-3,0);win<=3;win++)
        {
            for(int i=0;i<=200;i++)
            {
                for(int j=0;j<=200;j++)
                {
                    if(!dp[k][win][i][j]) continue;
                    if(win==3||k-win==3) continue;
                    if(k<4)
                    {
                        for(auto p:v1)
                        {
                            if(i+p.F>200) continue;
                            if(j+p.S>200) continue;
                            if(p.F>p.S) upd(dp[k+1][win+1][i+p.F][j+p.S]); else upd(dp[k+1][win][i+p.F][j+p.S]);
                        }
                    }
                    else
                    {
                        for(auto p:v2)
                        {
                            if(i+p.F>200) continue;
                            if(j+p.S>200) continue;
                            if(p.F>p.S) upd(dp[k+1][win+1][i+p.F][j+p.S]); else upd(dp[k+1][win][i+p.F][j+p.S]);
                        }
                    }
                }
            }
        }
    }
    scanf("%d",&t);
    while(t--)
    {
    	int a,b;
        scanf("%d%d",&a,&b);
        int cur=-1,m=-1,rec=-INF;
        for(int matches=3;matches<=5;matches++)
            for(int win=matches-3;win<=3;win++)
            {
            	if(win<3&&matches-win<3) continue;
                if(dp[matches][win][a][b]&&(win-(matches-win))>rec) {rec=win-(matches-win);  m=matches; cur=win;}
            }
        if(rec==-INF) {puts("Impossible"); continue;}
        printf("%d:%d\n",cur,m-cur);
        vector<P> ans;ans.clear();
        while(m>0)
        {
            if(m==5)
            {
                for(auto p:v2)
                {
                    if(p.F>a) continue;
                    if(p.S>b) continue;
                    int num=(p.F>p.S?1:0);
                    if(num>cur) continue;
                    if(!dp[m-1][cur-num][a-p.F][b-p.S]) continue;
                    if(cur-num>=3||m-1-(cur-num)>=3) continue;
                    m--;cur-=num;a-=p.F;b-=p.S;
                    ans.push_back(p);
                    break;
                }
            }
            else
            {
                for(auto p:v1)
                {
                    if(p.F>a) continue;
                    if(p.S>b) continue;
                    int num=(p.F>p.S?1:0);
                    if(num>cur) continue;
                    if(!dp[m-1][cur-num][a-p.F][b-p.S]) continue;
                    if(cur-num>=3||m-1-(cur-num)>=3) continue;
                    m--;cur-=num;a-=p.F;b-=p.S;
                    ans.push_back(p);
                    break;
                }
            }
        }
        for(int i=(int)ans.size()-1;i>=0;i--) printf("%d:%d%c",ans[i].F,ans[i].S,i==0?'\n':' ');
    }
    return 0;
}
