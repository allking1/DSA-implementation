#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define ll long long
#define db double
int fr1[1000]={0}; 
int fr2[1000]={0};
int tr[1000]={0}; // truy vet
int dp[1000]={0};
int max(int x,int y){
    return(x+y+abs(x-y))/2;
}
int cmp(const void *a,const void *b){
    int *x=(int*)a;
    int *y=(int*)b;
    return (*x)-(*y);
}

int main(){
    int n;
    scanf("%d",&n);
    int a[n+1];
    ll tong=0;
    for(int i=1;i<=n;i++) {
        scanf("%d",&a[i]);
        fr1[a[i]]++;
        tong+=a[i];
    }

    if(tong%2==0){
        tong=tong/2;
        int s=tong;
        dp[0]=1;
        for(int i=1;i<=n;i++){
            for(int j=s;j>=a[i];j--){ 
			// duyet tu s-> a[i] tranh viec them a[i] vao tap con nhieu lan
                if(dp[j-a[i]]==1){
                    if(dp[j]==0){ // lay thang dau tien lam dp[j]=1 khong bi loan mang tr[j];
                        dp[j]=1;
                        tr[j]=j-a[i];
                    }

                }
            }
        }
        printf("%d\n",dp[s]);
        for(int i=1;i<=s;i++) printf("%d ",dp[i]);
        printf("\n");
        for(int i=1;i<=s;i++) printf("%d ",tr[i]);
        int res[1000];
        int u=0;
        int j=s;
        while (j>0){
            res[u++]=j-tr[j]; // luu lai mang ket qua truy vet
            j=tr[j];
        }
        printf("\n");
        for(int i=u-1;i>=0;i--) {
                printf("%d ",res[i]);
                fr2[res[i]]++;
        }
        printf("\n");
        // xu li tan suat xuat hien de in ra 2 mang khong giao nhau,
        for(int i=1;i<=n;i++){
            if(fr2[a[i]]==0) printf("%d ",a[i]);
            else{
                if(fr1[a[i]]>fr2[a[i]]){
                    printf("%d ",a[i]);
                    fr1[a[i]]--;
                }
            }
        }

    }


}
