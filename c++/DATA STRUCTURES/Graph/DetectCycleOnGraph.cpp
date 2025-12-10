#include<iostream>
#include<stack>
#include<queue>
#include<vector>
#include <algorithm>
using namespace std;
/* Để kiểm tra chu trình trên đồ thị ta cũng dùng DFS và BFS, đối với đồ thị vô hướng thì tìm cạnh ngược trên cây, vì khi duyệt các thành
phần liên thông của 1 đỉnh rõ ràng nếu có đỉnh nào đó đã được duyệt mà lại kề với đỉnh ở trên nó từ ông nội trở lên thì ngay lập tức
xuất hiện chu trình. Nhưng với đồ thị có hướng ta dùng mảng color hoặc recstack để kiểm tra xem các đỉnh đó có cùng nằm trong 1 thành phần
liên thông hay không (nằm trong stack đệ quy). Ở đây ta code DFS vì nó dễ truy vết với BFS thì tương tự ngoài ra ở đồ thị có hướng BFS để kiểm tra chu trình
hay còn gọi là thuật toán Kahn trong sắp xếp topo */
vector<vector<int>> ke(1001);
bool visited[1001]={false};
int parent[1001]={0};
enum Color {White,Gray,Black};
int n,m,st,en;
Color color[1001]={White};


void initUndirectedGraph(){
    int x,y;
    for(int i=0;i<m;i++){
        cin >> x >> y;
        ke[x].push_back(y);
        ke[y].push_back(x);
    }
    return;
}

void initDirectedGraph(){
    int x,y;
    for(int i=0;i<m;i++){
        cin >> x >> y;
        ke[x].push_back(y);

    }
    return;
}

bool DFS_undirected(int u){
    visited[u]=true;
    for(auto x : ke[u]){
        if(!visited[x]){
            parent[x]=u;
            if(DFS_undirected(x)) return true;
        }
        else if(x!=parent[u]){
            st=x; en=u;
            vector<int> path;
            path.push_back(st);
            while(en != st){
                path.push_back(en);
                en=parent[en];
            }
            path.push_back(st);
            reverse(path.begin(),path.end());
            for(auto t : path) cout << t << " ";
            cout << endl;
            return true;
        }


    }
    return false;
}

bool DFS_directed(int u){
    color[u]=Gray; // đánh dấu đang thăm trong stack đệ quy tức là cùng 1 thành phần liên thông
    for(auto x : ke[u]){
        if(color[x]==White){ // chưa thăm
            if(DFS_directed(x)) return true;
        }
        else if(color[x] == Gray) return true;
    // đã tìm thấy chu trình vì đỉnh kề với u đã được thăm trước đó kể cả nếu đó là đỉnh cha của u vẫn thỏa (khác với vô hướng)
    }
    color[u]=Black; // kết thúc thành phần liên thông hay stack đệ quy đó
    return false;
}



int main(){
    cin >> n >> m;
    initUndirectedGraph();
    for(int i=1;i<=n;i++){
        if(!visited[i])
        if(DFS_undirected(i)) {
                cout << "YES";
                break;
        }
    }
    cout << "NO";

}


