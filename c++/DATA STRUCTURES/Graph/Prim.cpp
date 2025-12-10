#include<iostream>
#include<vector>
#include<queue>
#include<tuple>
using namespace std;

int n, m;
vector<vector<pair<int, int>>> adj(1000);
bool visited[1000];

void Prim(int start) {
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq; // dùng turple để truy vết dễ
    visited[start] = true;

    // đẩy tất cả cạnh từ đỉnh start
    for (auto [w, v] : adj[start]) {
        pq.push({w, start, v}); // (weight, from, to)
    }

    int total = 0;
    vector<tuple<int, int, int>> mst_edges;

    while (!pq.empty()) {
        auto [w, u, v] = pq.top(); pq.pop();
        if (visited[v]) continue;
        visited[v] = true;
        total += w;
        mst_edges.push_back({u, v, w});

        for (auto [next_w, to] : adj[v]) {
            if (!visited[to]) pq.push({next_w, v, to});
        }
    }

    cout << "Total weight: " << total << "\nEdges:\n";
    for (auto [u, v, w] : mst_edges) {
        cout << u << " - " << v << " (w = " << w << ")\n";
    }
}
int main(){
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int x, y, w;
        cin >> x >> y >> w;
        adj[x].push_back({w, y});
        adj[y].push_back({w, x}); // đồ thị vô hướng
    }
    Prim(1); // bắt đầu từ đỉnh 1
}
