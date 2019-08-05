#include<bits/stdc++.h>
#define MAXN 100005
#define INF 8000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,N,K;
vector<pair<string,string> > v;
vector<pair<string,string> > tmp;
int perm[10];
int ans[30];
int main()
{
    for(int i=1;i<=8;i++) perm[i]=i;
    do
    {
        string s,t;
        for(int i=1;i<=8;i++) s+=(char)'0'+perm[i];
        t+=(char)perm[1]-'0';
        for(int i=2;i<=8;i++) t+=(char)'0'+perm[i]-perm[i-1];
        v.push_back(make_pair(t,s));
    }while(next_permutation(perm+1,perm+9));
    sort(v.begin(),v.end());
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&N,&K);
        if(N<=8)
        {
            tmp.clear();
            for(int i=1;i<=N;i++) perm[i]=i;
            do
            {
                string s,t;
                for(int i=1;i<=N;i++) s+=(char)'0'+perm[i];
                for(int i=2;i<=N;i++) t+=(char)'0'+perm[i]-perm[i-1];
                tmp.push_back(make_pair(t,s));
            }while(next_permutation(perm+1,perm+N+1));
            sort(tmp.begin(),tmp.end());
            string str=tmp[K-1].S;
            for(int i=0;i<N;i++) printf("%d%c",str[i]-'0',i==N-1?'\n':' ');
        }
        else
        {
            ans[1]=N;
            for(int i=2;i<=N-8;i++) ans[i]=i-1;
            string str=v[K-1].S;
            for(int i=N-8+1;i<=N;i++)
            {
                int id=i-(N-8+1);
                ans[i]=str[id]-'0'+(N-9);
            }
            for(int i=1;i<=N;i++) printf("%d%c",ans[i],i==N?'\n':' ');
        }
    }
}
