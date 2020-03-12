#include <iostream>
#include <map>
using namespace std;

map <string, string> use;

void createMap(int &p, string pretag) {
    if(!p) return;
    
    string line, tag, attr, value;
    getline(cin, line);
    
    int i=1;
    if(line[i]=='/') {           
        while(line[i]!='>') i++;
        if(pretag.size()>(i-2))        
            tag = pretag.substr(0,pretag.size()-i+1);
        else
            tag = "";
    }
    else {                       
        while(line[i]!=' ' && line[i]!='>') i++;
        tag = line.substr(1,i-1);   
        if(pretag!="") tag = pretag + "." + tag;
        
        int j;
        while(line[i]!='>') { 
            j = ++i;
            while(line[i]!=' ') i++;
            attr = line.substr(j,i-j);   
            
            while(line[i]!='\"') i++;
            j = ++i;
            while(line[i]!='\"') i++;
            value = line.substr(j,i-j);    
            i+= 1;
            
            use[tag + "~" + attr] = value;
        }
    }
    createMap(--p, tag);
}

int main() {
    int p, q;
    cin >> p >> q;
    cin.ignore();
    createMap(p,"");
    
    string attr, value;
    while(q--) {
        getline(cin,attr);
        value = use[attr];
        if(value=="") value = "Not Found!";
        cout << value << endl;
    }
    return 0;
}