#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
mt19937 wcy(time(NULL));
int main()
{
    freopen("in.txt","w",stdout);
    int N=1000000,t=1000000;
    printf("%d %d\n",N,t);
    for(int i=0;i<N;i++)
    {
        int x=wcy()%(INF+1);
        printf("%d%c",x,i==N-1?'\n':' ');
    }
}
