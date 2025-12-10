#include <bits/stdc++.h>
using namespace std;
int a[100][100];char x[200];int n;int dem=0;int visted[100][100]={0};int check=0;
void SolveMaze(int i,int j,int t){
	dem++;
	if(i==n-1 && j==n-1){
		cout << x << endl;
		check=1;
		return;
	}
	visted[i][j]=1; 
	/* 
	bai toan nay ta co the danh dau vi tri dang dung hoac danh dau vi tri tiep theo 
	neu ta chon danh dau o vi tri tiep theo thi phai danh dau o 4 cai if va go danh dau o 4 cai if 
	*/
	if(i<n-1 && a[i+1][j]==1 && visted[i+1][j]==0){
		x[t]='D'; // ta co the dung string x va dung push_back , pop_back
		SolveMaze(i+1,j,t+1);
		// x.pop_back(); neu dung string x;
	}
	if(j<n-1 && a[i][j+1]==1 && visted[i][j+1]==0){
		x[t]='R';
		SolveMaze(i,j+1,t+1);
	}
	if(i>=1 && a[i-1][j]==1 && visted[i-1][j]==0){
		x[t]='U';
		SolveMaze(i-1,j,t+1);
	}
	if(j>=1 && a[i][j-1]==1 && visted[i][j-1]==0){
		x[t]='L';
		SolveMaze(i,j-1,t+1);
	}
	visted[i][j]=0; // go bo vi tri danh dau 
	
	return;
}

int main(){
	cin >> n;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cin >> a[i][j];
		}
	}
	SolveMaze(0,0,0);
	if(check==0) cout << "No path";

	
	
}

