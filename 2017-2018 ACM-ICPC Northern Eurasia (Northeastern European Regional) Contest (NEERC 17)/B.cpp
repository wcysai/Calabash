//
// Created by calabash_boy on 18-6-8.
//
#include<bits/stdc++.h>
using namespace std;
int a,b,c,w,h;
bool check(int xx,int yy){
    if(xx<=w&&yy<=h)return true;
    if(xx<=h&&yy<=w)return true;
    return false;
}
bool check(int a,int b,int c){
    if(check(2*b+2*c,a+2*b)||check(a+b+2*c,a+2*b)||check(a+b+c,a+2*b+c)||check(3*a+b+c,b+c)){
        return true;
    }else{
        return false;
    }
}
int main(){
    cin>>a>>b>>c>>w>>h;
    if(check(a,b,c)||check(a,c,b)||check(b,a,c)||check(b,c,a)||check(c,a,b)||check(c,b,a)){
        cout<<"Yes"<<endl;
    }else{
        cout<<"No"<<endl;
    }
    return 0;
}
