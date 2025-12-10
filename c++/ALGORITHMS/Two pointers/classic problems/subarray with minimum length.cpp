#include <bits/stdc++.h>
using namespace std;
#define ll long long
/*bai toan tim day con ngan nhat co tong >= p, day cho truoc co chu ki lap lai, tim chi so bat dau
va do dai day*/
// giong voi sliding window ,cac bai co chu ky nen tinh xem no lap lai may chu ki de ko TLE
int main(){
	int n;ll p;vector<ll> v(1002);
	cin >> n >> p;
	ll cycle=0;
	for(int i=1;i<=n;i++){
		cin >> v[i];
		cycle+=v[i]; // tong trong 1 chu ki
	}
	v[0]=v[n];

	ll start=1,ans,l=1,r=0;
	ll mood=0;
    if(mood < p){
			ll k=(p-mood)/cycle; // so chu ki lap lai
			mood+=k*cycle; // tang them k chu ki
			r+=k*n; // dich chuyen can right them k chu ki
			while(mood < p){
				++r;
				mood+=v[r%n];
			}
		}
	ans=r-l+1;
	while(l<=n){ // co dinh can left, can right di chuyen
		mood-=v[l++]; // lan luot xet cac subarray co chi so bat dau tu 1->n
		if(mood < p){
			ll k=(p-mood)/cycle; // tuong tu tren
			mood+=k*cycle;
			r+=k*n;
			while(mood < p){
				++r;
				mood+=v[r%n];
			}
		}
		if(r-l+1<ans){
			ans=r-l+1;
			start=l;
		}


	}
	cout << start << " " << ans;		
}
/* comments : in common we use fixed right bound and left bound moves but in this case left bound fixed 
is easier */
// code fixed right bound no using cycle (TLE)
/*
int n;ll p;vector<ll> v(2002);
	cin >> n >> p;
	for(int i=1;i<=n;i++){
		cin >> v[i];
		v[i+n]=v[i];
	}
	v[0]=v[n];
	ll start=1,ans,l=2,r=1;
	ll mood=0;
	while(mood < p){
		--l;
		mood+=v[n+l%n];
	}
	ans=r-l+1;
	start=l;
	while(r<n){
		++r;
		mood+=v[r];
		while(mood >= p){
			if(ans > r-l+1){
				ans=r-l+1;
				start=l;
			}
			mood-=v[n+l%n];
			l++;
		}
	}
	if(start <= 0){
		start=n+start%n;
	}
	cout << start << " " << ans;

*/
