#include <bits/stdc++.h>
using namespace std;
#define ll long long
// bai toan dem so cap i<j sao cho s[i]=a, s[j]=b, segment co so cap <= c dai nhat la bao nhieu 
int main(){
	int n; ll c; string s;
	cin >> n >> c >> s;
    ll ans=0,cnta=0,cntb=0; // dem 'a','b' trong segment hien tai
	ll l=0; ll res=0;
	for(ll r=0;r<n;r++){
		if(s[r]=='a') cnta++; // them a thi ko tang them cap , vi i < j
		else if(s[r]=='b') {
			cntb++;
			res=res+cnta; // neu them b thi moi 'a' ghep voi 'b' them cnta cap
		}
		while(res > c){
			if(s[l]=='a'){
				cnta--;
				res-=cntb; // neu xoa a thi moi 'b' se mat di 1 cap, tong la cntb cap
			}
			else if(s[l]=='b') cntb--; // xoa b thi so cap ko doi
			l++;
			
		}
		ans=max(ans,r-l+1);
		
	}
	cout << ans;	
}

