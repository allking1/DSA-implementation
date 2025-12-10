#include <bits/stdc++.h>
using namespace std;
#define ll long long 
/* bai toan cho day a, n le, thuc hien k thao tac sao cho so trung vi lon nhat , cac thao tac 
la tang so bat ki trong a len 1 don vi */
// day a da duoc sap xep
bool check(ll a[],ll k, ll n, ll target){ // ham de search hay con goi la P(target)
	ll cnt=0;
	for(int i=n/2+1;i<n;i++){ /* 
	khi tang so a[n/2] trong day da sap xep chi quan tam den so phia sau 
	vi so phia truoc da nho hon san
	*/
	
		if(a[i]<target) cnt+=target-a[i];
		//can tang it nhat target-a[i] voi moi i de thoa man median
		if(a[i]>=target) break;// neu xuat hien so thoa man thi cac so dang sau khong can tang
	}
	cnt+=target-a[n/2];// chi phi tang so trung vi
	/* neu cho for chay tu n/2 thi se break som neu gap truong hop median khong tang duoc
	vi the ta de o ngoai for de co the break som trong nhieu truong hop khong can duyet den cuoi*/
	return cnt<=k;
}

int main() {
	
    ll k,n; cin >> n >> k;
    ll a[n];
    for(int i=0;i<n;i++){
    	
      cin >> a[i];

     
 
}
    sort(a,a+n);
    if(n==1) cout << a[0]+k;
    else{
    	ll l=a[n/2],r=(ll)2*1e9; // can left: true, right: false
		// co the dung r=1;while check(a,k,n,r) r=r*2;
    	while(l<r){ // binary search
    		ll mid=l+(r-l+1)/2;
    		if(check(a,k,n,mid)) l=mid;
    		else r=mid-1;
		}
		cout << l;
	}

}

