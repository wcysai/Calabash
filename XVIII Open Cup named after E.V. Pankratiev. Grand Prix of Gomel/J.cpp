#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t;
char ch[3];
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        int cnt=0;
        for(int i=0;i<6;i++) scanf("%s",ch);
        for(int i=0;i<6;i++)
        {
            scanf("%s",ch);
            if(ch[0]=='R'&&ch[1]=='J') cnt++;
            if(ch[0]=='B'&&ch[1]=='J') cnt++;
        }
        for(int i=0;i<42;i++) scanf("%s",ch);
        scanf("%s",ch);
        if(cnt==2) puts("Johann"); else puts("Sebastian");
    }
    return 0;
}
/*
2
TC QD 2S TH 4S 3C
AS RJ AC 7D 6C BJ
3D 4C 8C AD TD TS 7H JS KD 4H QC 6H 9D 7C 9H JC AH 5H 6S QH KS 5S 5D 3H JD JH 8H QS 2H 4D 5C 9S KH 6D 9C 8D 8S KC 7S 3S 2D 2C
S
TC 8S JS JD 5C 9C
QS 8C 3H 4D 4H 2D
3D 4C 8C AD TD TS 7H JS KD 4H QC 6H 9D 7C 9H JC AH 5H 6S QH KS 5S 5D 3H JD JH 8H QS 2H 4D 5C 9S KH 6D 9C 8D 8S KC 7S 3S 2D 2C
S
*/
