#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int a , b;
    cin >> a >> b;
    vector<int> arr[a];
    for(int i= 0 ; i < a ; i++)
    {
       int m;
       cin >> m;
       int t1;
       for(int j=0;j<m;j++)
       {
          cin >> t1;
          arr[i].push_back(t1);
       }
    }
    int r,s;
    for(int k=0;k<b;k++)
    {
      cin>>r>>s;
      cout <<arr[r][s]<< endl;
    }
    return 0;
}