#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define ll long long
#define db double
int dp[1000][1000];
int max(int x,int y){
	if(x>=y) return x;
	return y;
}
int main(){
	int n,s;
	scanf("%d %d",&n,&s);
	int w[n+1],v[n+1];
	for(int i=1;i<=n;i++) scanf("%d",&w[i]);
	for(int i=1;i<=n;i++) scanf("%d",&v[i]);
	// dap an la dp[n][s]; ( lay n vat dau tien khong qua s thi co max la dp)
	for(int i=1;i<=n;i++){
		for(int j=1;j<=s;j++){
			dp[i][j]=dp[i-1][j];
			if(j>=w[i]){
				dp[i][j]=max(dp[i][j],dp[i-1][j-w[i]]+v[i]);
			}
		}
	}
	printf("%d\n",dp[n][s]);
	// truy vet
	int tr[1000];
	int cnt=0; // so luong phan tu );
	int i=n,j=s;
	while(i){
		if(dp[i][j]!=dp[i-1][j]) { // chung to da lay vat i vao trong tui
			tr[cnt++]=i;
			j=j-w[i]; // giam khoi luong xuong de truy vet tiep
		}
		i--; // neu dp[i]=dp[i-1] thi la cu giam i khong van de gi,
	}
	for(int i=cnt-1;i>=0;i--) printf("%d ",tr[i]);
}
