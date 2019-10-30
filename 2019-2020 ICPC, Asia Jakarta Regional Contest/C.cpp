#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int N,Q;
int R[MAXN],C[MAXN];
int RL[MAXN],RR[MAXN],CL[MAXN],CR[MAXN];
int main()
{
    scanf("%d%d",&N,&Q);
    for(int i=1;i<=N;i++) scanf("%d",&R[i]);
    for(int i=1;i<=N;i++) scanf("%d",&C[i]);
    RL[1]=1; CL[1]=1; RR[N]=N; CR[N]=N;
    for(int i=2;i<=N;i++) if((R[i]&1)==(R[i-1]&1)) RL[i]=RL[i-1]; else RL[i]=i;
    for(int i=2;i<=N;i++) if((C[i]&1)==(C[i-1]&1)) CL[i]=CL[i-1]; else CL[i]=i;
    for(int i=N-1;i>=1;i--) if((R[i]&1)==(R[i+1]&1)) RR[i]=RR[i+1]; else RR[i]=i;
    for(int i=N-1;i>=1;i--) if((C[i]&1)==(C[i+1]&1)) CR[i]=CR[i+1]; else CR[i]=i;
    for(int i=0;i<Q;i++)
    {
        int a,b,c,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        if(c>=RL[a]&&c<=RR[a]&&d>=CL[b]&&d<=CR[b]) puts("YES"); else puts("NO");
    }
    return 0;
}
