#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct Edge{
    int u,v,w;
    bool operator<(const Edge &other){ // kiểu struct ta có thể định nghĩa các operator để dùng với set,map,p queue,
        return w < other.w;

}
};
int n,m,parent[1000],sz[1000]; // union by size
vector<Edge> e;
vector<Edge> MST ;   // minimum spanning tree
// DSU
void make(){
    for(int i=1;i<=n;i++){
        parent[i]=i; sz[i]=1;
    }
}

int find_parent(int u){
    if(u != parent[u]) parent[u]=find_parent(parent[u]); // path compression
    return parent[u];
}

bool Union(int u,int v){
    u=find_parent(u);v=find_parent(v);
    if(u==v) return false;
    //vì đỉnh u và v đã nằm trong tập tức đã liên thông mà còn có cạnh u đến v thì tạo thành chu trình
    if(sz[u]<sz[v]) swap(u,v);
    parent[v]=u;
    sz[u]+=sz[v];
    return true;

}

void Kruskal(){
    make();
    sort(e.begin(),e.end());
    int total=0;
    for(int i=0;i<m;i++){
        if(MST.size() == n-1) break;
        if(Union(e[i].u,e[i].v)){
                MST.push_back(e[i]);
            total+=e[i].w;
        }
    }
    cout << total << endl;
}


int main(){
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int x,y,w; cin >> x >> y >> w;
        e.push_back({x,y,w});
    }
    Kruskal();
}
