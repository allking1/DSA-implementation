#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;
/* cây phân đoạn làm việc tốt với các bài toán truy vấn trên đoạn, cập nhật phần tử, đoạn, tối ưu hóa quy hoạch động,...
dưới đây sẽ là code đối với bài toàn tìm tổng đoạn [l,r] và cập nhật vị trí u thành value v */
int a[1000], segment[4*1000+1]; // kết cấu cây được biểu diễn dưới mảng, số node không quá 4*n ( định lí thợ ? ).

void buildSegmentTree(int s,int l,int r){ // ta build cây từ vị trí 1, đoạn từ 0->n-1
    if(l==r) segment[s] = a[l]; // node lá
    else{
        int mid = (l+r)/2;
        buildSegmentTree(2*s,l,mid);
        buildSegmentTree(2*s+1,mid+1,r); // (tương tự heap, con trái là 2*s,con phải là 2*s+1)
        segment[s]=segment[2*s]+segment[2*s+1]; // cập nhật phần tử
    }
}

void update(int s,int l,int r,int pos,int value){
// ta update tại a[pos], s sẽ là chỉ số trong mảng segment ứng với node lá a[pos], hàm sẽ đi tìm và cập nhật
    if(l == r) segment[s]=value;
    else{
        int mid = (l+r)/2;
        if(pos <= mid) update(2*s,l,mid,pos,value);
        else update(2*s+1,mid+1,r,pos,value); // giống tìm kiếm nhị phân, ta đang đi tìm các thành phần liên thông với a[pos]
        segment[s]=segment[2*s]+segment[2*s+1];
    }
}

int sumLR(int s,int tl,int tr,int l,int r){
// s là chỉ số của segment, tl tr là chỉ số đoạn mà segment[s] quản lí, l, r là đoạn cần tìm. ta sẽ co đoạn đến khi l=tl,r=tr
    if(l > r) return 0;
    if(l==tl && r==tr) return segment[s];
    int tmid = (tl+tr)/2;
    if(r <= tmid) return sumLR(2*s,tl,tmid,l,r);
    if(l>=tmid+1) return sumLR(2*s+1,tmid+1,tr,l,r);
    return sumLR(2*s,tl,tmid,l,r)+sumLR(2*s+1,tmid+1,tr,l,r);
    /* return sumLR(2 * s, tl, mid, l, min(r, mid)) +
           sumLR(2 * s + 1, mid + 1, tr, max(l, mid + 1), r);
           đây thực ra là chia 3 trường hợp như trên
    */
}


int main(){
}
