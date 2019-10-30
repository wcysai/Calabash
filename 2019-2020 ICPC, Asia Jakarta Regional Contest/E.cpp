#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int N,L,R,K,A[MAXN];
int l[MAXN],r[MAXN];
int main()
{
    scanf("%d%d%d%d",&N,&L,&R,&K);
    for(int i=1;i<=N;i++) scanf("%d",&A[i]);
    l[N]=L; r[N]=R;
    for(int i=N-1;i>=1;i--)
    {
        if(A[i]==A[i+1])
        {
            l[i]=l[i+1];
            r[i]=r[i+1];
        }
        else if(A[i]>A[i+1])
        {
            l[i]=l[i+1]+1;
            r[i]=min(R,r[i+1]+K);
        }
        else 
        {
            l[i]=max(L,l[i+1]-K);
            r[i]=r[i+1]-1;
        }
        if(l[i]>r[i])
        {
            puts("-1");
            return 0;
        }
    }
    int cur=l[1];
    printf("%d",cur);
    for(int i=2;i<=N;i++)
    {
        if(A[i]==A[i-1]) printf(" %d",cur);
        else if(A[i]>A[i-1])
        {
            int xl=cur+1,xr=cur+K;
            xl=max(xl,l[i]); xr=min(xr,r[i]);
            cur=xl;
            printf(" %d",xl);
        }
        else
        {
            int xr=cur-1,xl=cur-K;
            xl=max(xl,l[i]); xr=min(xr,r[i]);
            cur=xl;
            printf(" %d",xl);
        }
    }
    puts("");
    return 0;
}
