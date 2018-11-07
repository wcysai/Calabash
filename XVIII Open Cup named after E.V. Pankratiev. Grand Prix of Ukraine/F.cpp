//
// Created by calabash on 11/7/18.
//
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+100;
int n;
struct Manacher{
    char ch[maxn*2];
    int N;
    int lc[maxn*2];
    void init(char *s){
        ch[n*2+1] = '#';
        ch[0] = 'z'+1;
        for (int i=n;i>=1;i--){
            ch[i*2] = s[i];
            ch[i*2-1] = '#';
        }
        N = n*2+1;
        manacher();
    }
    void manacher(){
        lc[1]=1;  int k=1;
        for (int i=2;i<=N;i++){
            int p = k+lc[k]-1;
            if (i<=p){
                lc[i]=min(lc[2*k-i],p-i+1);
            }else{  lc[i]=1;  }
            while (ch[i+lc[i]]==ch[i-lc[i]])lc[i]++;
            if (i+lc[i]>k+lc[k])k=i;
        }
    }
    void debug(){
        for (int i=1;i<=N;i++){
            printf("lc[%d]=%d\n",i,lc[i]);
        }
    }
    int query(){
        if (lc[(N+1)/2] != (N+1)/2)return 1;
        for (int i=(N+1)/2-3;i>=1;i--){
            int l = i;
            int r = (N+1)/2;
            int len = r-l+1;
            if (len &1){
                int mid = l+r >>1;
                if (lc[mid]>= (len+1)/2)continue;
                int ll = l-1;
                int rr = (N+1)/2-1;
                int llen = rr - ll +1;
                int mmid = ll + rr >>1;
                if (lc[mmid]>=(llen+1)/2)continue;
                return 2;
            }else{
                int rr = (N+1)/2-1;
                int llen = rr-l+1;
                int mid = rr + l >>1;
                if (lc[mid] >= (llen+1)/2)continue;
                int rrr = r+1;
                int lllen = rrr - l +1;
                int mmid = l + rrr >>1;
                if (lc[mmid]>=(lllen+1)/2)continue;
                return 2;
            }
        }
        return -1;
    }
}manacher;
char s[maxn];
int main(){
    scanf("%d",&n);
    scanf("%s",s+1);
    manacher.init(s);
    //manacher.debug();
    cout<<manacher.query()<<endl;
    return 0;
}
/*
5
aabaa
lc[1]=1
lc[2]=2
lc[3]=3
lc[4]=2
lc[5]=1
lc[6]=6
lc[7]=1
lc[8]=2
lc[9]=3
lc[10]=2
lc[11]=1
1
 */
