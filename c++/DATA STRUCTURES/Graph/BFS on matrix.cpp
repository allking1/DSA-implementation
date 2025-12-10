#include <iostream>
#include <queue>
#include <utility>
using namespace std;

const int MAX = 1001;
int a[MAX][MAX], n;
bool visited[MAX][MAX];
pair<int,int> parent[MAX][MAX];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

pair<int,int> endPoint = {-1, -1};

bool isValid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n && !visited[x][y] && a[x][y] != 0;
}

void BFS(int i, int j) {
    visited[i][j] = true;
    queue<pair<int, int>> q;
    q.push({i, j});

    while (!q.empty()) {
        auto [u, v] = q.front(); q.pop();

        for (int dir = 0; dir < 4; dir++) {
            int ni = u + dx[dir];
            int nj = v + dy[dir];

            if (isValid(ni, nj)) {
                visited[ni][nj] = true;
                parent[ni][nj] = {u, v};
                q.push({ni, nj});

                if (a[ni][nj] == 2) {
                    endPoint = {ni, nj};  // lưu điểm đích
                    return; // dừng BFS khi tìm thấy đích
                }
            }
        }
    }
}

void printPath() {
    if (endPoint.first == -1) {
        cout << "No path found to destination." << endl;
        return;
    }

    vector<pair<int,int>> path;
    pair<int,int> curr = endPoint;

    while (!(curr.first == 0 && curr.second == 0)) {
        path.push_back(curr);
        curr = parent[curr.first][curr.second];
    }
    path.push_back({0, 0}); // thêm điểm bắt đầu

    // In ngược từ (0,0) đến đích
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << path[i].first << " " << path[i].second << endl;
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];

    if (a[0][0] == 0) {
        cout << "Starting point is blocked!" << endl;
        return 0;
    }

    BFS(0, 0);
    printPath();
    return 0;
}
