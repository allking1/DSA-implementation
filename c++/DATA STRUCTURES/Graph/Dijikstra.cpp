#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int INF = 1e9;
int a[1000][1000],n; // ma trận trọng số
vector<int> d(1000,INF); // khoảng cách
bool marked[1000]={false}; // đánh dấu đã gán nhãn cố định
int previous[1000];
vector<int> path;


void Dijkstra(int source,int t){
    d[source]=0;
    previous[source]=source;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
    q.push({d[source],source});
    while(!q.empty()){

        pair<int,int> top = q.top();q.pop();
        int u = top.second;
        int dist = top.first;
        marked[u]=true;
        if(dist > d[u]) continue;
        // chứng tỏ u đã được gán nhãn cố định tức là đã tìm đc min dist từ s tới u
        // nếu không thì cập nhật
        for(int i = 1; i <= n; i++) {
            if (!marked[i]) {
                if (d[i] > d[u] + a[u][i]) {
                    d[i] = d[u] + a[u][i];
                    previous[i] = u;
                    q.push({d[i], i});
        }
    }
}

    }
    cout << d[t] << endl;
    while(t!=source){
        path.push_back(t);
        t=previous[t];
    }
    path.push_back(source);
    reverse(path.begin(),path.end());
    for (auto x : path) cout << x << " ";
}




int main(){
    cin >> n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) cin >> a[i][j];
    }
    Dijkstra(1,3);
}
