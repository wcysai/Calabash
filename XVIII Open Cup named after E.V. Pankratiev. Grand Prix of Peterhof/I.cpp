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
set<char> s;
char ch[4]={'N','W','E','S'};
int main()
{
    cin>>str;
    for(int i=0;i<(int)str.size();i++) s.insert(str[i]);
    if(s.size()<2)
    {
        puts("X");
        return 0;
    }
    if(s.size()==2&&s.count('E')&&s.count('W')) {puts("X"); return 0;}
    if(s.size()==2&&s.count('N')&&s.count('S')) {puts("X"); return 0;}
    vector<char> v; v.clear();
    for(int i=0;i<4;i++) if(!s.count(ch[i])) v.push_back(ch[i]);
    for(int i=0;i<(int)v.size();i++) 
        for(int j=0;j<50;j++)
            printf("%c",v[i]);
    printf("\n");
    return 0;
}
