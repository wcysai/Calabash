//
// Created by calabash_boy on 18-6-8.
//
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e3+100;
int a[maxn],n;
int zeronumber;
map<int,int> now;
vector<int> ans;
int main(){
    cin>>n;
    for (int i=0;i<n;i++){
        cin>>a[i];
    }
    for (int i=0;i<n;i++){
        if(a[i]>0){
            now[a[i]]++;
        }else if (a[i]<0){
            if(now[-a[i]]==0&&zeronumber==0){
                cout<<"No"<<endl;
                return 0;
            }else{
                if(now[-a[i]]>0){
                    now[-a[i]]--;
                }else{
                    zeronumber--;
                    ans.push_back(-a[i]);
                }
            }
        }else{
            zeronumber++;
        }
    }
    cout<<"Yes"<<endl;
    for (int i=0;i<n;i++){
        ans.push_back(1);
    }
    for (int i=0,j=0;i<n;i++){
        if (a[i]==0){
            cout<<ans[j++]<<" ";
        }
    }
    return 0;
}
