#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define dec asdkoasdoa
#define div doskdoa
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int lb,rb,len;
int cnt[10];
int mult;
int add;
int dec;
int div;
int operand;//0: = 1:< 2:> 3:!= 4:<= 5:>=
char str[3];
mt19937 wcy(time(NULL));
string op[6]=
{
    "=",
    "<",
    ">",
    "!=",
    "<=",
    ">=",
};
string pool[6][6]=
{
    "=","<",">","!=","<=",">=",
    "4","+","-","(","(",")",
    "0","/","/","/","8","+",
    "2","3","4","5","-",")",
    "+","-","*","/","1","9",
    "6","7","+","-","(",")",
};
char ask(int x)
{
    printf("%d\n",x); fflush(stdout);
    scanf("%s",str);
    len++;
    return str[0];
}
void get_relation()
{
    printf("1\n"); fflush(stdout);
    scanf("%s",str);
    if(str[0]=='=') operand=0,len++;
    else if(str[0]=='!') operand=3,len+=2;
    else if(strlen(str)==2) operand=(str[0]=='<'?4:5),len+=2;
    else operand=(str[0]=='<'?1:2),len++; 
}
void analyze(char ch)
{
    if(ch=='(') lb++;
    else if(ch==')') rb++;
    else if(ch>='0'&&ch<='9') cnt[ch-'0']++;
    else if(ch=='+') add++;
    else if(ch=='-') dec++;
    else if(ch=='*') mult++;
    else if(ch=='/') div++;
} 
void get_type(int x)
{
    char ch=ask(x);
    analyze(ch);
}
int get_nonzero()
{
    for(int i=1;i<=9;i++) if(cnt[i]) {cnt[i]--; return i;}
    assert(0);//should not reach here
}
int get_any()
{
    for(int i=0;i<=9;i++) if(cnt[i]) {cnt[i]--; return i;}
    assert(0);//should not reach here
}
string get_allnum()
{
    string str="";
    int x=get_nonzero();
    str+=(char)('0'+x);
    for(int i=0;i<=9;i++)
        for(int j=0;j<cnt[i];j++)
            str+=(char)('0'+i);
    return str;
}
string construct_any()
{
    string str="";
    int x=get_nonzero();
    str+=(char)('0'+x);
    while(div)
    {
        int x=get_nonzero();
        str+='/';
        str+=(char)('0'+x);
        div--;
    }
    while(mult)
    {
        int x=get_any();
        str+='*';
        str+=(char)('0'+x);
        mult--;
    }
    while(add)
    {
        int x=get_any();
        str+='+';
        str+=(char)('0'+x);
        add--;
    }
    assert(dec>0);
    while(dec>1) 
    {
        int x=get_any();
        str+='-';
        str+=(char)('0'+x);
        dec--;
    }
    str+='-';
    str+=get_allnum();
    assert(lb==rb);
    while(lb) {lb--; rb--; str='('+str+')';}
    return str;
}
string construct_eq()
{
    cnt[0]-=2;
    lb--; rb--; mult--;
    string str=construct_any();
    str='('+str+')'+'*'+'0';
    return str;
}
string construct_neq()
{
    cnt[0]--; cnt[2]--;
    lb--; rb--; mult--;
    string str=construct_any();
    str='('+str+')'+'*'+'0';
    return str;
}
string construct_ans()
{
    if(operand==0||operand==4||operand==5) 
    {
        string str=construct_eq();
        str=str+op[operand]+'0';
        return str;
    }
    else
    {
        string str=construct_neq();
        if(operand==2) str='2'+op[operand]+str;
        else str=str+op[operand]+'2';
        return str;
    }
}
int main()
{
    get_relation();
    int tot=301;
    for(int i=0;i<300;i++) get_type(4);
    while(lb<rb) {get_type(2); tot++; assert(tot<=1000);}
    while(cnt[0]<2) {get_type(3); tot++; assert(tot<=1000);}
    while(!mult) {get_type(5); tot++; assert(tot<=1000);}
    string s=construct_ans();
    assert((int)s.size()==len);
    cout<<"0 "<<s<<endl;
    return 0;
}
