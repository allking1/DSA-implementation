#include <bits/stdc++.h>
using namespace std;
#define ll long long
/* bai toan tim so ngay target it nhat de di chuyen x1->x2,y1->y2, moi ngay co huong gio tac dong
*/

long long let,rght,down,up;
bool check(ll x1,ll y1,ll x2,ll y2,ll n,string s,ll target){ // ham check
// ngay target se bi gio tac dong target/n chu ki va 1->target%n;
	for(ll i=1;i<=target%n;i++){
		
			
		
		if(s[i%n]=='L') x1--;
		else if(s[i%n]=='R') x1++;
		else if(s[i%n]=='U') y1++;
		else y1--;
	
	}
	x1=x1+(target/n)*(rght-let);
	y1=y1+(target/n)*(up-down);
	return (abs(x1-x2)+abs(y1-y2)<=target); /* 
	sau khi tac dong, moi ngay ta duoc di chuyen 1 don vi, neu <= thi true */
	
	
	

}


int main() {
	ll x1,y1,x2,y2,n;
	cin >> x1 >> y1 >> x2 >> y2 >> n;
	string s(n+1,'0'); // them 0 vao de de dang dung i%n;
	for(int i=1;i<=n;i++){
		cin >> s[i];
		if(s[i]=='L') let++;
		else if(s[i]=='R') rght++;
		else if(s[i]=='D') down++;
		else up++;
	}
	s[0]=s[n]; // i%n==0 thi chinh la ngay thu n
	if(x1==x2 && y1==y2) cout << "0";
	else{
		int ok=0;
		ll l=1;
		if(check(x1,y1,x2,y2,n,s,l)) cout << "1";
		else{
			ll r=2; 
			while(!check(x1,y1,x2,y2,n,s,r)){
				r=r*2;
				if(r>1e17){
					cout <<"-1"; // check nhieu qua ma khong thay dap an :)))
					ok=1;  // de khong check co the khai bao r=1e18; va them 1 bien ans=-1;
					break;
				}
			}
			if(ok==0){ // binary search
				while(l<r){
					ll mid=l+(r-l-1)/2; 
					if(check(x1,y1,x2,y2,n,s,mid)) r=mid; // ans=mid;
					else l=mid+1;
				
				}
				cout << r;
			}
			
		}
		
		
	}
	



    
}
    



