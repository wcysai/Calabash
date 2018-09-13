#include <bits/stdc++.h>
using namespace std;
vector<int> sheet = {1,2,3,5,7,11,13,17,23,31,37,53,71,73,113,131,137,173,311,317};
char N[105];
int main(){
    int T;
    scanf("%d",&T);
    int Case=1;
    while (T--){
        scanf("%s",N);
        printf("Case #%d: ",Case++);
        if (strlen(N) > 3){
            puts("317");
        }else{
            int n = atoi(N);
            int ans =1;
            for (int i=0;i<sheet.size();i++){
                if (sheet[i] <= n){
                    ans = sheet[i];
                }
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}
