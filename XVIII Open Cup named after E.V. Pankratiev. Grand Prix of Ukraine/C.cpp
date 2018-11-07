//
// Created by calabash on 11/7/18.
//
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e4+100;
char s[maxn];
int n;
ll ans = 0;
char pattern[maxn];
void work(int len){
   // printf("%s %d\n",pattern,len);
    int idx = 0;
    int LEN = 0;
    for (int i=0;i<n;i++){
        if (s[i] == pattern[idx]){
            idx ++;
            if (idx == len){
                LEN++;
                idx = 0;
            }
        }
    }
    //pattern[len] = '\0';
    //printf("%lld\n",1ll *LEN*LEN*len);

    ans = max(ans,1ll * LEN * LEN * len);
}
int main(){
    scanf("%d",&n);
    scanf("%s",s);
    for (int i=0;i<3;i++){
        pattern[0] = 'a'+i;
        work(1);
        for (int j=0;j<3;j++){
            pattern[1] = 'a'+j;
            work(2);
            for (int k=0;k<3;k++){
                pattern[2] = 'a' + k;
                work(3);
                for (int o1 =0;o1 <3;o1 ++){
                    pattern[3] = 'a' + o1;
                    work(4);
                    for (int o2 =0;o2 <3;o2 ++){
                        pattern[4] = 'a' + o2;
                        work(5);
                        for (int o3 =0;o3 <3;o3 ++){
                            pattern[5] = 'a' + o3;
                            work(6);
                            for (int o4 =0;o4 <3;o4 ++){
                                pattern[6] = 'a' + o4;
                                work(7);
                                for (int o5 =0;o5 <3;o5 ++){
                                    pattern[7] = 'a' + o5;
                                    work(8);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}


/*
 11
 abcabacbcac



 10
 aaabbbccca
 */
