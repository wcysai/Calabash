#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef vector<int> vec;
int N;
bool cmp(vec x,vec y) {return x.size()<y.size();}
vector<vec> chains;
bool add;
int main()
{
    scanf("%d",&N);
    if(N&1) {add=true; N--;} else add=false;
    int l=1,r=N;
    vector<int> tmp,lhs,rhs;
    tmp.push_back(N); tmp.push_back(1);
    for(int i=0;i<N/2-1;i++)
    {
        r--; tmp.push_back(r);
        l++; tmp.push_back(l);
    }
    reverse(tmp.begin(),tmp.end());
    chains.push_back(tmp);
    for(int i=0;i<N/2-1;i++)
    {
        for(int j=0;j<=N-1;j++) 
        {
            tmp[j]++;
            if(tmp[j]==N+1) tmp[j]=1;
        }
        lhs.clear(); rhs.clear();
        int len=i+1;
        for(int j=len;j>=0;j--) lhs.push_back(tmp[j]);
        for(int j=len;j<=N-1;j++) rhs.push_back(tmp[j]);
        chains.push_back(lhs); chains.push_back(rhs);
    } 
    if(add) 
    {
        vector<int> empty; empty.push_back(N/2); chains.push_back(empty);
        N++;
    }
    sort(chains.begin(),chains.end(),cmp);
    if(add)
    {
        for(int i=0;i<N-1;i++) chains[i].push_back(N);
    }
    for(int i=0;i<N-1;i++)
    {
        for(auto x:chains[i]) printf("%d ",x);
        puts("");
    }
    return 0;
}