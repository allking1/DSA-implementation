#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long

void BubbleSort(int a[],int n){
// y tuong dich ptu lon nhat ve cuoi, ptu lon thu hai ve n-2,.. tuong tu
    for(int i=0;i<n-1;i++){
        bool swapped = false;
        for(int j=0;j<n-i-1;j++){
            if(a[j]>a[j+1]) {
                swap(a[j],a[j+1]);
                swapped = true;
            }
        }
        if(!swapped) return;// neu khong co swap thi sap xep xong
    }
    return;
}

void InsertionSort(int a[],int n){
/*y tuong xay dung tu 1 mang da duoc sap xep, khi them 1 phan tu vao cuoi
    thi tim vi tri chen no vao va dich vi tri cac phan tu > hon no */
    for(int i=1;i<n;i++){
// tim vi tri cua a[i] trong mang 0->i-1
// a[0] da duoc sap xep nen ta xet tu 1->n-1
        int key=a[i];
        int j=i-1;
        while(j>=0 && a[j] > key){ // tim vi tri cua key trong mang 0->i-1
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=key;
    }
    return;
}

void SelectionSort(int a[], int n) {
    // y tuong tim min dua ve a[0], cac ptu tiep theo tuong tu
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[minIndex]) {
                minIndex = j;
            }
        }
        swap(a[i], a[minIndex]); // chi can hoan doi 1 lan, tiet kiem
}
    return;
}

void QuickSort(int a[],int l,int r){ // Hoare Partition
    if(l>=r) return;
    int pivot=a[(l+r)/2];
    int i=l,j=r;
    while(i<j){
        while(a[i] < pivot) i++;
        while(a[j] > pivot) j--;
        if(i<=j){
            swap(a[i],a[j]);
            i++;j--;
        }
    }
    QuickSort(a,l,j);
    QuickSort(a,i,r);
    return;
}


void merge(int a[], int l, int m, int r) {
    int k = r - l + 1;
    vector<int> c(k);

    int i = l, j = m + 1, t = 0;

    while (i <= m && j <= r) {
        if (a[i] <= a[j]) c[t++] = a[i++];
        else c[t++] = a[j++];
    }

    while (i <= m) c[t++] = a[i++];
    while (j <= r) c[t++] = a[j++];

    for (int i = 0; i < k; i++) a[l + i] = c[i];
}

void MergeSort(int a[], int l, int r) {
    if (l >= r) return;

    int m = (l + r) / 2;
    MergeSort(a, l, m);
    MergeSort(a, m + 1, r);
    merge(a, l, m, r);
}

void CountingSort(int a[], int n) {
    // dem tan suat xuat hien , sau do duyet theo thu tu tang dan index cua mang count[]
    int minarray = *min_element(a, a + n);
    int maxarray = *max_element(a, a + n);

    int range = maxarray - minarray + 1;
    vector<int> countfre(range, 0);

    for (int i = 0; i < n; i++) {
        countfre[a[i] - minarray]++; // xu li cac so am
    }

    int index = 0;
    for (int i = 0; i < range; i++) {
        while (countfre[i]--) {
            a[index++] = i + minarray;
        }
    }
}

void countingSort(int a[], int n, int exp) {
    vector<int> output(n);
    vector<int> count(10, 0); // Đếm số lần xuất hiện của chữ số (0-9)

    // Đếm tần suất chữ số tại vị trí `exp`
    for (int i = 0; i < n; i++) {
        int digit = (a[i] / exp) % 10;
        count[digit]++;
    }

    // Cộng dồn để xác định vị trí chính xác của từng chữ số
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Xây dựng mảng kết quả theo thứ tự ổn định
    for (int i = n - 1; i >= 0; i--) { // Duyệt ngược để đảm bảo tính ổn định
        int digit = (a[i] / exp) % 10;
        output[count[digit] - 1] = a[i];
        count[digit]--;
    }

    // Copy mảng kết quả về mảng gốc
    for (int i = 0; i < n; i++) {
        a[i] = output[i];
    }
}

void radixSort(int a[], int n) {
    int maxVal = *max_element(a, a + n); // Tìm số lớn nhất

    // Chạy Counting Sort cho từng chữ số (hàng đơn vị, hàng chục, ...)
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSort(a, n, exp);
    }
}

int main() {
   int a[100];int n; cin >> n;
   for(int i=0;i<n;i++) cin >> a[i];
   radixSort(a,n);
   for(int i=0;i<n;i++) cout << a[i] << ' ';

}
