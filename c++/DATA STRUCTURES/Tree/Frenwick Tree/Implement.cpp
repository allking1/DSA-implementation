#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
/* khi ta muốn đưa bài toán từ tuyến tính về log, sử dụng frenwick tree giúp kiểm soát tốt hơn khi cập nhật phần tử (Ologn)
áp dụng vào các bài toán trên đoạn [L,R], đếm các phần tử ở trước < a[i],... */

/* có nhiều cách định nghĩa bit[i] tùy bài toán, dưới đây code bit[i] theo thông thường dùng để tính tổng đoạn, cập nhật đoạn */
int a[1000],bit[1000], n;

void update(int pos,int value){
    while(pos <= n){ // hiểu đơn giản, lấy bit đầu tiên khác 0(phải sang) cộng dần lên bằng bao nhiêu thì sẽ có mặt trong bit đó.
        bit[pos]+=value;
        pos += pos & (-pos);

    }
}

int sum(int x){
    int res = 0;
    while(x>0){
        res += bit[x];
        x -= x &(-x);
    }
    return res;
}

int main(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i],update(i,a[i]);
    cout << sum(5);

}
