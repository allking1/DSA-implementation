#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define ll long long
#define db double
int max(int x,int y){
    return(x+y+abs(x-y))/2;
}

int main(){
    int n;
    scanf("%d",&n);
    int a[n+1],l[n+1],b[n+1],lmax=-10,ltemp,idx,idxmax;
    // ta can mang l la do dai day con dai nhat ket thuc o chi so thu i;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        l[i]=1;
        ltemp=0;
        idx=0;
        for(int j=1;j<=i-1;j++){
            if(a[i]>a[j]){
                if(l[j]>ltemp){
                    ltemp=l[j];
                    idx=j;
                }
            }
        }
        l[i]=ltemp +1;
        b[i]=idx; // b la mang luu chi so cua phan tu o truoc, b[i] la chi so j sao cho l[i]=l[j]+1;
        if(lmax<l[i]){
            lmax=l[i]; // tim ra day con dai nhat
            idxmax=i; // tim ra chi so ket thuc cua day con dai nhat
        }
    }
    //printf("%d\n",lmax);
    //for(int i=1;i<=n;i++){
    //    printf("%d ",b[i]);
   // }
    
    //printf("\n");
    //printf("%d",idxmax);
    int res[lmax]; // mang tim ra day con dai nhat
    res[0]=a[idxmax]; //
    for(int i=1;i<lmax;i++){
        idxmax=b[idxmax]; // lay chi so cua thang o truoc ma noi tiep voi a[idxmax]
        res[i]=a[idxmax]; // tim ra phan tu o truoc
    }
    //printf("\n");
    for(int i=lmax-1;i>=0;i--) printf("%d ",res[i]);
}

