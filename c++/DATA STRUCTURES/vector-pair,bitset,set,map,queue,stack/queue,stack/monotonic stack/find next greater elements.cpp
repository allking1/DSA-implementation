#include <iostream>
#include <vector>
#include <algorithm>
#include<cstring>
#include<stack>
using namespace std;

#define ll long long
void find_next_greater_element(vector<int> v,int n){
    stack<int> s;
    vector<int> ans(n);
    for(int i=n-1;i>=0;i--){
        while(!s.empty() && s.top() <= v[i]){
            s.pop();
        }
        if(s.empty()) ans[i]=-1;
        else ans[i]=s.top();
        s.push(v[i]);
    }
    for(auto x : ans){
        cout << x << ' ';
    }
    return;
}






int main(){
    int n;cin >> n;
    vector<int> v(n);
    for(int i=0;i<n;i++){
        cin >> v[i];
    }
    find_next_greater_element(v,n);
}
