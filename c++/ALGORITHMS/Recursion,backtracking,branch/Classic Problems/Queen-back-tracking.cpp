#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n,x[100]={0}; // luu cac nghiem cua bai toan x[i]=j la (i,j) co 1 con hau 
int col[100]={0},md[100]={0},cd[100]={0}; 
// cac mang de danh dau cac cot, duong cheo chinh va phu da bi kiem soat chua

void inkq() {
	for (int i = 1;i <= n;i++) {
		cout << x[i] << " ";
	}
	cout << endl;
	return;
}
void Queen_back_tracking(int i) {
	for (int j = 1;j <= n;j++) { // duyet tat cac ca kha nang cua con hau thu i
		if(!col[j] && !md[i-j+n] && !cd[i+j-1]){ 
		// neu cot j, 2 duong cheo kiem soat cot j chua co hau
			x[i]=j; // danh dau da co 1 hau
			col[j]=1;md[i-j+n]=1;cd[i+j-1]=1; // da bi kiem soat
			if(i==n) { // dieu kien dung khi da tim duoc 1 cau hinh
				inkq();
			}
			else {
			Queen_back_tracking(i+1); // tiep tuc den con hau thu i
			}
			col[j]=0;md[i-j+n]=0;cd[i+j-1]=0; 
			// go bo danh dau, cac o va duong cheo het bi kiem soat
			
		}
	}
	return;
}


int main(){

	cin >> n;
	Queen_back_tracking(1);
}

