#include <bits/stdc++.h>
using namespace std;

int v[100], n, k, tong = 0;
bool check = false; 

void backtrack(int i) {
    if (n==1){
    	cout << k; return; // tranh truong hop n=1 khong backtrack duoc;
	}
	if(i==n){
		for(int j=1;j<n;j++){
			cout << v[j] << " ";
			
		}
		cout << k-tong << endl; // ta chi chon n-1 so , so thu n chi co 1 cach chon
		return;
	}
	for(int j=1;j<=k;j++){
		if(tong+j<=k-(n-i)){ // kiem tra dieu kien tong + so thu i co vuot qua khong
			
		
		v[i]=j;
		tong+=j;
		backtrack(i+1); // quay lui
		tong-=j; // go bo danh dau
	}
	}
	return;
}

int main() {
    cin >> n >> k;
    backtrack(1);

}

