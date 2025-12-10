#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define ll long long
#define db double
int max(int x,int y){
    return (x+y+abs(x-y))/2;
}
int f[3001][3001]={0}; 
// f[i][j] la do dai xau con chung dai nhat tinh den phan tu thu i,j cua a,b
char res[3001]; // xau truy vet
int main(){
    char a[3001],b[3001];
    scanf("%s",a);
    scanf("%s",b);


    for(int i=1;i<=strlen(a);i++){
        for(int j=1;j<=strlen(b);j++){
            if(a[i-1]==b[j-1]) f[i][j]=f[i-1][j-1]+1;
			// neu 2 phan tu cuoi bang nhau thi them vao xau chung
            else{
                f[i][j]=max(f[i-1][j],f[i][j-1]);
            // neu khong thi bo a[i] hoac b[j]
            }
        }

    }

    // truy vet
    for(int x=strlen(a),y=strlen(b),u=0;y>=1 && x>=1;){ // duyet nguoc de tim xau chung
            if(a[x-1]==b[y-1]){
                res[u]=a[x-1]; // neu 2 phan tu = nhau thi ta lay
                u++;
                x--;
                y--;
            }
            else{
                if(f[x-1][y]>f[x][y-1]){ 
				// neu xau chung theo huong y dai hon thi ta giam x (bo a[x])
                    x--;
                }
                else y--; // nguoc lai
            }

    }
    for(int i=strlen(res)-1;i>=0;i--) printf("%c",res[i]);

}
