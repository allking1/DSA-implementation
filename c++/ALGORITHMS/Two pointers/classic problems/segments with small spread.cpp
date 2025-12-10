#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
	int n; ll k; vector<ll> v(100020);
	cin >> n >> k;
	for(int i=0;i<n;i++) cin >> v[i];
	ll res=0; multiset<ll> ms; // dung multiset de luu min,max tren l->r
    ll l=0;
	for(ll r=0;r<n;r++){
		ms.insert(v[r]);
		while(*ms.rbegin()-*ms.begin()>k){
			ms.erase(ms.find(v[l++])); 
			//chi xoa 1 phan tu neu ms.erase(v[l]) se dan den xoa het cac ptu=v[l]
		}
		res+=r-l+1;
	}
	cout << res;		
}

