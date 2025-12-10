#include<iostream>
#include<vector>
using namespace std;
// tối ưu bằng size,
int parent[1000],num[1000];
int n;
void make_set(){
    for(int i=1;i<=n;i++){
        parent[i]=i;
        num[i]=1; // union by size
    }
}
int find(int a){
    if(a == parent[a]) return a;
    return (parent[a]=find(parent[a])); // phép return (a=b) vừa gán a = b vừa trả về b gọi là path compression
}

void Union(int a,int b){
    a=find(a);b=find(b);
    if(a!=b){
        if(num[a] < num [b]) swap(a,b); // lấy tập có ít phần tử hơn ghép vào
        parent[b]=a;
        num[a]+=num[b];
    }
}















int main(){
    return 0;
}
