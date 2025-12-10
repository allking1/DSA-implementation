#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define ll long long
#define db double

char a[1000];
f[1001][1001];
int main(){
   scanf("%s",a);
   int n=strlen(a);
   for(int k=1;k<=n;k++){
    for(int i=0;i<n;i++){
        int j=i+k-1;
        if(j<n){
            if(j==i) f[i][j]=1;
            else if(k==2){
                if(a[i]!=a[j]) f[i][j]=0;
                else f[i][j]=1;


            }
            else{
                if(a[i]!=a[j]) f[i][j]=0;
                else {
                    if(f[i+1][j-1]==0) f[i][j]=0;
                    else if(f[i+1][j-1]==1) f[i][j]=1;
                }
            }
        }
    }
   }
   int max=-2;
   for(int i=0;i<n;i++){
    for(int j=i;j<n;j++){
        if(f[i][j]==1){
            if(j-i+1 > max) max=j-i+1;
        }
    }
   }
   for(int i=0;i<n;i++){
    for(int j=i;j<n;j++){
        if(f[i][j]==1 && j-i+1==max){
            for(int u=i;u<=j;u++){
                printf("%c",a[u]);

            }
            printf("\n");
        }
    }
   }

