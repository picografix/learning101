#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

int main() {
    string str;
    cin >> str;
    vector<string> integers ;
    stringstream so(str);
    string temp;
    while (getline(so, temp, ',')) { 
        integers.push_back(temp);
    }
    for(int i = 0; i < integers.size(); i++) {
        cout << integers[i] << "\n";
    }
    
    return 0;
}