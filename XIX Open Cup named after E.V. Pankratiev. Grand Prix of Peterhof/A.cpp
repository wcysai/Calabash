#include <bits/stdc++.h>
using namespace std;
const int maxn = 10000 + 5;
char s[maxn];
int main(){
    scanf("%s",s);
    int len = strlen(s);
    for (int i = len-1;i>=0;i--){
        if (s[i] == 'b'){printf("b");}
        else{
            for (int o=0;o<5;o++){
                printf("%c",s[i]);
            }
        }
    }
    puts("");
    return 0;
}
