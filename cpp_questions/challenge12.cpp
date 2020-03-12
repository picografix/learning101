#include<iostream>
#include<string>
using namespace std;
int main(){
    string s,t;
    cin>>s>>t;
    cout<<s.size()<<" "<<t.size()<<endl;
    cout<<s+t<<endl;
    char t1=s[0];
    s[0]=t[0];
    t[0]= t1;
    cout<<s+" "+t;
}