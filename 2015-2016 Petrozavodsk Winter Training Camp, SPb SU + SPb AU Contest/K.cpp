#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+ 100;
struct Suffix_Automaton{
    //basic
    int nxt[maxn*2][26],fa[maxn*2],l[maxn*2];
    int last,cnt;
    Suffix_Automaton(){ clear(); }
    void clear(){
        last =cnt=1;
        fa[1]=l[1]=0;
        memset(nxt[1],0,sizeof nxt[1]);
    }
    void init(char *s){
        while (*s){
            add(*s-'a');s++;
        }
    }
    void add(int c){
        int p = last;
        int np = ++cnt;
        memset(nxt[cnt],0,sizeof nxt[cnt]);
        l[np] = l[p]+1;last = np;
        while (p&&!nxt[p][c])nxt[p][c] = np,p = fa[p];
        if (!p)fa[np]=1;
        else{
            int q = nxt[p][c];
            if (l[q]==l[p]+1)fa[np] =q;
            else{
                int nq = ++ cnt;
                l[nq] = l[p]+1;
                memcpy(nxt[nq],nxt[q],sizeof (nxt[q]));
                fa[nq] =fa[q];fa[np] = fa[q] =nq;
                while (nxt[p][c]==q)nxt[p][c] =nq,p = fa[p];
            }
        }
    }
    pair<int,int> gao(char *s,int ns){
        pair<int,int> ans = make_pair(-1,-1);
        int true_ans = -0x3f3f3f3f;
        int temp = 1;
        int len = 0;
        for (int i=0;i<ns;i++){
            int ch = s[i] - 'a';
            while (temp != 1 && !nxt[temp][ch])temp = fa[temp],len = l[temp];
            if (nxt[temp][ch]){
                temp = nxt[temp][ch];
                len ++;
            }
            if (len){
                int st = i - len + 1;
                int ed = i;
                int temp_ans = ed - st + 1 - max(st,ns - ed - 1);
                if (temp_ans > true_ans){
                    true_ans = temp_ans;
                    ans = make_pair(st,ed);
                }else if (temp_ans == true_ans){
                    ans = min(ans,make_pair(st,ed));
                }
            }
        }
        return ans;

    }
}sam;
char s[maxn],t[maxn];
int main(){
    scanf("%s%s",s,t);
    int ns = strlen(s);
    int nt = strlen(t);
    sam.init(t);
    auto pr = sam.gao(s,ns);
    cout<<pr.first<<" "<<pr.second<<endl;
    return 0;
}
