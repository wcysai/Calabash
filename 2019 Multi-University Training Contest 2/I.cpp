// Created by calabash_boy on 18-6-4.
// BZOJ 3676
// calc max(len(t)*cnt(t)) t为s回文子串，cnt(t)=t出现次数
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ULL;
const int maxn = 3e5+100;
int n;


struct Palindromic_AutoMaton{
    //basic
    int temp_len = 0;
    int s[maxn],now;
    int ep[maxn];
    int nxt[maxn][26],fail[maxn],l[maxn],last,tot;
    // extension
    int num[maxn];/*节点代表的所有回文串出现次数*/
    void clear(){
        temp_len = 0;
        //1节点：奇数长度root 0节点：偶数长度root
        s[0]=l[1]=-1;
        fail[0] = tot = now =1;
        last = l[0]=0;
        memset(nxt[0],0,sizeof nxt[0]);
        memset(nxt[1],0,sizeof nxt[1]);
    }
    Palindromic_AutoMaton(){clear();}
    int newnode(int ll,int now_ep){
        tot++;
        ep[tot] = now_ep;
        memset(nxt[tot],0,sizeof nxt[tot]);
        fail[tot]=num[tot]=0;
        l[tot]=ll;
        return tot;
    }
    int get_fail(int x){
        while (s[now-l[x]-2]!=s[now-1])x = fail[x];
        return x;
    }
    void add(int ch){
        s[now++] = ch;
        int cur = get_fail(last);
        if(!nxt[cur][ch]){
            int tt = newnode(l[cur]+2,temp_len);
            fail[tt] = nxt[get_fail(fail[cur])][ch];
            nxt[cur][ch] = tt;
        }
        last = nxt[cur][ch];num[last]++;
    }
    void build(){
        //fail[i]<i，拓扑更新可以单调扫描。
        for (int i=tot;i>=2;i--){
            num[fail[i]]+=num[i];
        }
        num[0]=num[1]=0;
    }
    void init(char* ss){
        temp_len = 0;
        while (*ss){
            temp_len ++;
            add(*ss-'a');ss++;
        }
    }
    void init(string str){
        for (int i=0;i<str.size();i++){
            add(str[i]-'a');
        }
    }
    void answer();
}pam;
ll ans[maxn];
struct Manacher{
    int lc[maxn*2];
    char ch[maxn*2];
    int N;
    Manacher(){}
    Manacher(char *s){init(s);manacher();}
    /* s 1 bas */
    void init(char *s){
        int n = strlen(s+1);
        ch[n*2 +1] = '#';
        ch[0] = '@';
        ch[n*2 +2] = '\0';
        for (int i=n;i>=1;i--){
            ch[i*2] = s[i];ch[i*2 -1] = '#';
        }
        N = 2* n +1;
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
        puts(ch);
        for (int i=1;i<=N;i++){
            printf("lc[%d]=%d\n",i,lc[i]);
        }
    }
}manacher;
void Palindromic_AutoMaton::answer(){
    for (int i=0;i<=n;i++){
        ans[i] = 0;
    }
    for (int i=2;i<=tot;i++){
        int length = (l[i] + 1) / 2;
        int R = ep[i];
        int L = R - length + 1;
        int mid = L + R;
        int need = 2 * R - mid + 1;
        if (manacher.lc[mid] >= need){
            ans[l[i]] += num[i];
        }
    }
    for (int i=1;i<=n;i++){
        printf("%lld%c",ans[i],i == n?'\n':' ');
    }
}
char s[maxn];
char t[maxn];
int main(){

    while (scanf("%s",s+1) != EOF){
        pam.clear();
        n = strlen(s+1);
        for (int i=1;i<=n;i++){
            t[i] = s[i];
        }
        reverse(t+1,t + 1 + n);
        pam.init(s+1);
        manacher.init(s);
      //  manacher.debug();
        pam.build();
        pam.answer();
    }
    
    return 0;
}
