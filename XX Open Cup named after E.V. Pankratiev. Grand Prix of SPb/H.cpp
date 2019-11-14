#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
string str;
bool has[2][17];
void print_pattern(bool eat=false)
{
    for(int i=1;i<=4;i++) if(has[0][i]) printf("*"); else printf(".");
    printf("|");
    for(int i=5;i<=8;i++) if(has[0][i]) printf("*"); else printf(".");
    if(eat) printf(" eat "); else printf(" buy ");
    for(int i=1;i<=4;i++) if(has[1][i]) printf("*"); else printf(".");
    printf("|");
    for(int i=5;i<=8;i++) if(has[1][i]) printf("*"); else printf(".");
    printf("\n");
	for(int i=9;i<=12;i++) if(has[0][i]) printf("*"); else printf(".");
    printf("|");
    for(int i=13;i<=16;i++) if(has[0][i]) printf("*"); else printf(".");
    printf("     ");
    for(int i=9;i<=12;i++) if(has[1][i]) printf("*"); else printf(".");
    printf("|");
    for(int i=13;i<=16;i++) if(has[1][i]) printf("*"); else printf(".");
    printf("\n");
    printf("---\n");
}
void set_val(int id,int st,int ed)
{
    memset(has[id],false,sizeof(has[id]));
    if(st==-1) return;
    if(st<=ed)
    {
        for(int i=st;i<=ed;i++) has[id][i]=true;
    }
    else
    {
        for(int i=st;i<=16;i++) has[id][i]=true;
        for(int i=1;i<=ed;i++) has[id][i]=true;
    }
}
void print_eat(int st,int ed)
{
    set_val(0,st,ed);
    if(st==ed) {st=ed=-1;}
    else
    {
        st++; if(st==17) st=1;
    }
    set_val(1,st,ed);
    print_pattern(true);
}
int calc_len(int st,int ed)
{
    int len;
    if(st<=ed) len=ed-st+1;
    else len=ed+(16-st+1);
    return len;
}
void print_buy(int st,int ed)
{
    set_val(0,st,ed);
    if(st==-1)
    {
        st=1; ed=10;
        set_val(1,st,ed);
    }
    else
    {
        if(calc_len(st,ed)>5) return;
        ed+=10; if(ed>=16) ed-=16;
        set_val(1,st,ed);
    }
    print_pattern(false);
}
int main()
{
    cin>>str;
    print_buy(-1,-1);
    for(int i=1;i<=16;i++)
        for(int j=1;j<=16;j++)
        {
            if(calc_len(i,j)==16) continue;
            print_eat(i,j);
            print_buy(i,j);
        }
    return 0;
}
