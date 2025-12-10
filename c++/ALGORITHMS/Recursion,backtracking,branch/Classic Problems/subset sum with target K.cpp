#include <bits/stdc++.h>
using namespace std;
int a[100],used[1000]={0},tong=0;vector<int> v(1,0);int n,k;int check=0;
/* tim tap con co tong bang k ( cac phan tu khac nhau doi mot va > 0 ) */
void backtrack(int i){
	if(i==n+1) return;
	if(tong==k){
		for(int j=1;j<v.size();j++){
			cout << v[j] << " ";
		

		}
		cout << endl;
		check=1;
		return;
	}
	for(int x:a){
		if(used[x]==0 && x > v[i-1]){ // ta luon de v[0]=0 de co the xet duoc phan tu dau tien
			v.push_back(x); // danh dau
			tong+=x;
			used[x]=1;
			backtrack(i+1);
			tong-=x;
			used[x]=0;
			v.pop_back(); // go het tat ca
		}
	}
	return;
}


int main(){
	cin >> n >> k;
	for(int i=0;i<n;i++){
		cin >> a[i];
	}
	sort(a,a+n);
	backtrack(1);
	if(check==0) cout << "no solution";

	
	
}

