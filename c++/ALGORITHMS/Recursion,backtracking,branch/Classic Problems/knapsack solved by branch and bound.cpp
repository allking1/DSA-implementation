#include <bits/stdc++.h>
using namespace std;
#define ll long long
double k =0,value=0,weight=0,res=0; // goi cac bien theo doi value,weight dang xet
int n; double s,w[102],v[102];
int dem=0;


void knapsack_backtrack(int i){
	
	for(int j=0;j<=1;j++){ // kha nang khi xet vat thu i la chon hoac khong chon
		if(j==0){ // khong chon vat i
		
			if(i==n){
				res=max(res,value); // dieu kien dung in ra cau hinh 
			}
			else if(value + (s-weight)*k > res){ 
			// nhanh can, neu can tren > res la gtln hien tai moi xet tiep
				knapsack_backtrack(i+1); 
			}
			// khong can go bo danh dau vi ta khong chon vat i
		}
		else{ // ta chon vat i, tuc la j==1
			if(weight + w[i] <= s){ // dieu kien vat i duoc chon la du khoi luong chua vat i
				weight+=w[i]; // cap nhat cac danh dau
				value +=v[i];
				if(i==n) res=max(res,value);
				else if(value + (s-weight)*k > res){ // nhanh can
					knapsack_backtrack(i+1); // goi vat tiep theo
				}
				weight-=w[i]; // go bo danh dau
				value-=v[i]; // go bo danh dau
					
				
				}
			}
		}
	}



int main(){

	cin >> n >> s;
	for(int i=1;i<=n;i++){
		cin >> w[i] >> v[i];
		k=max(k,v[i]/w[i]);
	} // tim don gia cao nhat de danh gia can tren
	knapsack_backtrack(1);
	cout << (ll)res;
	

	
}

