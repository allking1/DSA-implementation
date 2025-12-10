#include <iostream>
#include <algorithm>
using namespace std;
/* heap có cấu trúc giống cây nhị phân hoàn chỉnh nhưng thường được lưu bằng mảng,
ánh xạ bằng cách parent có chỉ số i thì left là 2*i+1, right là 2*i+2 thỏa mãn
các con của nó luôn có giá trị bé hơn(max-heap) ngược lại là min-heap được ứng dụng trong heap-sort,
priority queue
*/
void heapify(int a[], int heapsize, int i) { // tìm ra max trong 3 phần tử
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < heapsize && a[l] > a[largest]) largest = l;
    if (r < heapsize && a[r] > a[largest]) largest = r;
    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, heapsize, largest); // fix từ chỉ số i đến leave
    }
}

void build_max_heap(int a[], int heapsize) {
    for (int i = heapsize / 2 - 1; i >= 0; i--)
        heapify(a, heapsize, i); // ta chỉ fix từ những chỉ số mà có nút con tức là không phải là lá
}

void heap_sort(int a[], int arrsize) {
    build_max_heap(a, arrsize);
    for (int i = arrsize - 1; i >= 1; i--) {
        swap(a[0], a[i]); // vì phần tử a[0] luôn lớn nhất nên ta đưa về cuối mảng sau đó làm dần về chỉ số 1
        heapify(a, i, 0);
    }
}

int main() {
    int a[10];
    cout << "Nhap 10 so nguyen: ";
    for (int i = 0; i < 10; i++) cin >> a[i];

    heap_sort(a, 10);

    cout << "Mang sau khi sap xep: ";
    for (int i = 0; i < 10; i++) cout << a[i] << " ";
    return 0;
}
