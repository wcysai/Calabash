#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int N,A,B,X[MAXN];
int main()
{
    scanf("%d%d%d",&N,&A,&B);
    for(int i=0;i<N;i++) scanf("%d",&X[i]);
    if(A==B)
    {
        int x=0;
        for(int i=0;i<N;i++) if((X[i]/A)&1) x=1-x;
        if(x) puts("Zenyk"); else puts("Marichka");
    }
    else if(A>B)
    {
        int x=0,cnt=0;
        for(int i=0;i<N;i++)
        {
            int m=X[i]%(A+B);
            if(m>=B&&m<A) {puts("Marichka"); return 0;}
            else if(m>=2*B) cnt++;
            else if(m>=A&&m>=B) x=1-x;
        }
        if(cnt>1) puts("Marichka");
        else if(cnt==1&&(x&1)) puts("Marichka");
        else if(cnt==1) puts("Zenyk");
        else if(x&1) puts("Zenyk");
        else puts("Marichka");
    }
    else
    {
        int x=0;
        for(int i=0;i<N;i++)
        {
            int m=X[i]%(A+B);
            if(m>=A&&m<B) {puts("Zenyk"); return 0;}
            else if(m>=2*A) {puts("Zenyk"); return 0;}
            else if(m>=A&&m>=B) x=1-x;
        }
        if(x&1) puts("Zenyk");
        else puts("Marichka");
    }
    return 0;
}
