#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int a,b;
int go(int x)
{
    if(x==0) a++; else b++;
    if(x==0) printf("+\n"); else printf("-\n");
    fflush(stdout);
    int ret;
    scanf("%d",&ret);
    return 1-ret;
}
void win(int x)
{
    printf("! ");
    if(x==0) puts("good");
    else if(x==1) puts("bad");
    else puts("ugly");
    fflush(stdout);
    exit(0);
}
void get()
{
    go(0); int x=go(1);
    int y=go(1);
    if(x==0) win(2); else if(y==0) win(0); else win(1);
}
int main()
{
    a=0;b=0;
    ll cur=1; 
    int type=1;
    while(true)
    {
        for(int i=0;i<cur;i++) if(go(type)==0) get();
        cur=cur*3; type^=1;
    }
    return 0;
}
