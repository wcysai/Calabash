#include <bits/stdc++.h>
#define rank rkrkrk
using namespace std;
const int maxn = 2e5+100;
vector<pair<int,int> > segs[26];
char s[maxn];
char ans[maxn];
int n,k;
int calc_need(int pos,int ch){
    int cnt = 0;
    for (pair<int,int> seg: segs[ch]){
        if (seg.second < pos)continue;
        if (seg.first != pos) cnt ++;
    }
    return cnt;
}
int get_all(int idx,int ch){
    int cnt = 0;
    for (pair<int,int> seg: segs[ch]){
        if (seg.second < idx)continue;
        cnt += seg.second - seg.first + 1;
    }
    return cnt;
}
namespace Suffix_Array{
    int cntA[maxn],cntB[maxn],tsa[maxn],A[maxn],B[maxn];
    int sa[maxn],rank[maxn];
    void get_sa(char * ch,int n){
        int N = max(n,(int)'z')+1;
        for (int i=0;i<N;i++)cntA[i] = 0;
        for (int i=1;i<=n;i++)cntA[ch[i]]++;
        for (int i=1;i<=N;i++)cntA[i] += cntA[i-1];
        for (int i=n;i;i--)sa[cntA[ch[i]]--] = i;
        rank[sa[1]] = 1;
        for (int i=2;i<=n;i++){
            rank[sa[i]] = rank[sa[i-1]];
            if (ch[sa[i]] != ch[sa[i-1]]) rank[sa[i]]++;
        }
        for (int l = 1;rank[sa[n]]<n;l<<=1){
            for (int i=0;i<N;i++)cntA[i] = 0;
            for (int i=0;i<N;i++)cntB[i] = 0;
            for (int i=1;i<=n;i++){
                cntA[A[i] = rank[i]] ++;
                cntB[B[i] = (i+l<=n)?rank[i+l]:0]++;
            }
            for (int i=1;i<N;i++)cntB[i] += cntB[i-1];
            for (int i=n;i;i--)tsa[cntB[B[i]]--] = i;
            for (int i=1;i<N;i++)cntA[i] += cntA[i-1];
            for (int i=n;i>=1;i--)sa[cntA[A[tsa[i]]]--] = tsa[i];
            rank[sa[1]] = 1;
            for (int i=2;i<=n;i++){
                rank[sa[i]] = rank[sa[i-1]];
                if (A[sa[i]]!= A[sa[i-1]] || B[sa[i]] != B[sa[i-1]]) rank[sa[i]] ++;
            }
        }

    }
};
int ans_len = 0;
inline void append_ans(int ch,int length){
    for (int i=0;i<length;i++,ans_len++){
        ans[ans_len] = 'a' + ch;
    }
}
typedef pair<int,int> SEG;
void work(int st_pos,int k,int ch){
    //cerr<<st_pos<<" "<<k<<" "<<(char)('a' + ch)<<endl;
    int R = -1;
    vector<pair<int,int> > S;
    for (pair<int,int> seg : segs[ch]){
        if (seg.second < st_pos)continue;
        if (seg.first == st_pos){
            append_ans(ch,seg.second - seg.first +1);
            R = max(R,seg.second+1);
            continue;
        }
        S.push_back(seg);
    }
    sort(S.begin(),S.end(),[](SEG x,SEG y){
        return x.second - x.first > y.second - y.first;
    });
    assert(S.size() >k);
    SEG key_seg = S[k-1];
    int key_len = key_seg.second - key_seg.first + 1;
    vector<SEG> key_segs(0);
    for (SEG seg : S){
        int seg_len = seg.second - seg.first + 1;
        if (seg_len > key_len){
            append_ans(ch,seg_len);
            k--;
            R = max(R,seg.second);
        }else if (seg_len == key_len){
            key_segs.push_back(seg);
        }
    }
    append_ans(ch,k * key_len);
    vector<int> suf_pos(0);
    sort(key_segs.begin(),key_segs.end(),[](SEG x,SEG y){
        return x.first < y.first;   
    });
    for (int i=k-1;i<key_segs.size();i++){
        suf_pos.push_back(max(R+1,key_segs[i].second+1));
    }
    if (key_segs[k-1].second<=R)suf_pos.push_back(R+1);
    Suffix_Array::get_sa(s,n+1);
    sort(suf_pos.begin(),suf_pos.end(),[](int x,int y){
        return Suffix_Array::rank[x] > Suffix_Array::rank[y];
    });
   // cerr<<"suffix "<<endl;
   // for (int x : suf_pos){
   //     cerr<<x<<" ";
   // }
   // cerr<<endl;
    int st_suf = suf_pos[0];
    for (int i = st_suf;i<=n;i++){
        ans[ans_len++] = s[i];
    }
}
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
//        cerr<<"hello"<<endl;
        memset(ans,0,sizeof ans);
        ans_len = 0;
        scanf("%d%s",&k,s+1);
        n = strlen(s+1);
        for (int i=0;i<26;i++){
            segs[i].clear();
        }
        int prech = '0';
        int pre_st = -1;
        for (int i=1;i<=n;i++){
            if (s[i] != prech){
                if (i != 1){
                    segs[prech-'a'].push_back(make_pair(pre_st,i-1));
                }
                prech = s[i];
                pre_st = i;
            }
        }
        segs[s[n]-'a'].push_back(make_pair(pre_st,n));
        //int ans_len = 0;
        int idx = 1;
        for (int i=25;i>=0;i--){
     //       cerr<<(char)(i+'a')<<" "<<ans<<endl;
            //puts("ans");
            if (segs[i].empty())continue;
            int need_k = calc_need(idx,i);
            if (need_k <=k){
                //int num = get_all(idx,i);
                append_ans(i,get_all(idx,i));
                idx = max(idx,segs[i].back().second + 1);
                k -= need_k;
            }else if (k && idx <= n){
                work(idx,k,i);
                break;
            }else{
       //         cerr<<idx<<endl;
                for (int j = idx;j <=n;j++){
                    ans[ans_len++] = s[j];
                }
                break;
            }
         //   cerr<<(char)(i+'a')<<"   "<<ans<<endl;
        }
        ans[ans_len] = '\0';
        puts(ans);
    }
    return 0;
}
