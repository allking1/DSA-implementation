#include<iostream>
#include<stack>
#include<queue>
#include<vector>
#include <algorithm>
using namespace std;
/* bài toán sắp xết tô pô phải trên đồ thị có hướng và không có chu trình,
sắp xếp các đỉnh sao cho nếu có đường đi từ u đến v thì u phải đứng trước v.
ứng dụng : sắp xếp lịch làm việc, thứ tự các học phần (học phần tiên quyết,...) */
// Kahn Algorithm
vector<int> ke[10001];
int in_degree[10001]={0};
vector<int> a;
void topoSort(int n,int m){
    queue<int> q;
    for(int i=1;i<=n;i++){
        if(in_degree[i] == 0) q.push(i);
    }
    while(!q.empty()){
        int e = q.front();q.pop();
        a.push_back(e);
        for(auto x : ke[e]){
            in_degree[x]--;
            if(in_degree[x]==0) q.push(x);
        }
    }

    for(auto x : a){
        cout << x << " ";
    }
}



int main(){
    int n,m;
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int x,y;
        cin >> x >> y;
        ke[x].push_back(y);
        in_degree[y]++;
    }
    topoSort(n,m);
}
