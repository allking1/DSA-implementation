#include<iostream>
#include<stack>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;
// Bước 1 : DFS đến từng đỉnh lưu lại thứ tự sắp xếp trong stack ( giống với topo nhưng đây là có chu trình )
// Bước 2 : lật ngược cung -> transpose graph
// Bước 3 : pop từng đỉnh trong stack ra gọi DFS trên transpose graph -> đếm được SCC.
int n, m;
vector<vector<int>> ke(1000);
vector<vector<int>> ke_reverse(1000);
bool visited[1000];
stack<int> topo;

void topoSort(int u){
    visited[u] = true;
    for(auto x : ke[u]){
        if(!visited[x]) topoSort(x);
    }
    topo.push(u);
}

void countSCC(int u){
    visited[u] = true;
    for(auto x : ke_reverse[u]){
        if(!visited[x]) countSCC(x);
    }
}

int main(){
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        ke[x].push_back(y);
        ke_reverse[y].push_back(x); // lật cạnh
    }

    // Bước 1: DFS để lấy topo order
    memset(visited, false, sizeof(visited));
    for(int i = 1; i <= n; i++){
        if(!visited[i]) topoSort(i);
    }

    // Bước 2: DFS theo thứ tự topo trên đồ thị đảo để đếm SCC
    memset(visited, false, sizeof(visited));
    int cnt = 0;
    while(!topo.empty()){
        int u = topo.top(); topo.pop();
        if(!visited[u]){
            countSCC(u);
            cnt++;
        }
    }

    cout << cnt << endl;
}
