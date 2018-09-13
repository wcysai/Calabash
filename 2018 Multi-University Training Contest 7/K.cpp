/*************************************************************************
    > File Name: K.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-08-13 14:51:03
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
int T,n,k;
vector<P> a[6];
int b[MAXN][6];
int v[6],cnt[MAXN],now[6];
queue<int> que;
const int MAXBUF = 10000;
char buf[MAXBUF], *ps = buf, *pe = buf+1;
inline void rnext()
{
    if(++ps == pe)
        pe = (ps = buf)+fread(buf,sizeof(char),sizeof(buf)/sizeof(char),stdin);
}

template <class T>
inline bool in(T &ans)
{
    ans = 0;
    T f = 1;
    if(ps == pe) return false;//EOF
    do{
        rnext();
        if('-' == *ps) f = -1;
    }while(!isdigit(*ps) && ps != pe);
    if(ps == pe) return false;//EOF
    do
    {
        ans = (ans<<1)+(ans<<3)+*ps-48;
        rnext();
    }while(isdigit(*ps) && ps != pe);
    ans *= f;
    return true;
}
int main()
{
    in(T);
    while(T--)
    {
        int ans=0;
        in(n);in(k);
        for(int i=1;i<=k;i++) in(v[i]);
        for(int i=1;i<=k;i++) a[i].clear();
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=k;j++)
            {
                int x;
                in(x);
                a[j].push_back(P(x,i));
            }
            for(int j=1;j<=k;j++) in(b[i][j]);
        }
        for(int i=1;i<=k;i++) sort(a[i].begin(),a[i].end());
        memset(now,0,sizeof(now));
        while(que.size()) que.pop();
        bool f=false;
        do
        {
            for(int i=1;i<=k;i++)
            {
                while(now[i]<n&&a[i][now[i]].F<=v[i])
                {
                    cnt[a[i][now[i]].S]++;
                    if(cnt[a[i][now[i]].S]==k) que.push(a[i][now[i]].S);
                    now[i]++;
                }
            }
            f=false;
            while(que.size())
            {
                f=true;
                int p=que.front();que.pop();
                ans++;
                for(int i=1;i<=k;i++) v[i]+=b[p][i];
            }
        }while(f);
        printf("%d\n",ans);
        for(int i=1;i<=k;i++) printf("%d%c",v[i],i==k?'\n':' ');
    }
    return 0;
}
