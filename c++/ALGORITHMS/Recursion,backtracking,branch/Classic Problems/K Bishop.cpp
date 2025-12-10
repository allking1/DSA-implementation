#include <bits/stdc++.h>
using namespace std;
#define ll long long
/* bai nay hay vi cach xay dung cau hinh, va quay lui trong 1 ma tran 
*/
int a[105][105]={0},k,n,diag1[105]={0},diag2[105]={0},dem=0;
void backtrack(int x,int y,int k){
	dem++;
	if(k==0){
		for(int i=0;i<n;i++){
		for(int j=0;j<n;j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	return;
	}
	if(x==n) return;
	if(k>0 && a[x][y]==0 && diag1[x+y]==0 && diag2[x-y+n-1]==0){ // neu dat quan tuong duoc
		a[x][y]=1;
		diag1[x+y]=1;diag2[x-y+n-1]=1; // danh dau
		if(y<n-1){
			backtrack(x,y+1,k-1); // ta di theo huong y truoc ( column )
			a[x][y]=0;
			diag1[x+y]=0;diag2[x-y+n-1]=0;
		}
		else if(y==n-1){ // neu y khong di duoc nua, reset y=0, x++, 
			backtrack(x+1,0,k-1);
			a[x][y]=0;
			diag1[x+y]=0;diag2[x-y+n-1]=0;
		}
		
		
	}
	if(y<n-1){ // tuong tu
			backtrack(x,y+1,k); // khong dat quan tuong,
		
		}
		else if(y==n-1){
			backtrack(x+1,0,k);
		
	
		}
	

	return;

}





int main(){
	cin >> n >> k;
	backtrack(0,0,k);
	cout << dem;
	
}
