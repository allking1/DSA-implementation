#include <iostream>
#include <algorithm>
using namespace std;

#define QUEUE_SIZE 100

// Hàm kiểm tra rỗng
bool isEmpty(int size) {
    return size <= 0;
}

// Hàm kiểm tra đầy
bool isFull(int size) {
    return size >= QUEUE_SIZE;
}

// Heapify xuống từ chỉ số i
void heapify_down(int a[], int heapsize, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < heapsize && a[l] > a[largest]) largest = l;
    if (r < heapsize && a[r] > a[largest]) largest = r;

    if (largest != i) {
        swap(a[i], a[largest]);
        heapify_down(a, heapsize, largest);
    }
}

// Heapify lên từ chỉ số i
void heapify_up(int a[], int i) {
    int parent = (i - 1) / 2;
    if (parent >= 0 && a[parent] < a[i]) {
        swap(a[parent], a[i]);
        heapify_up(a, parent);
    }
}

// Thêm phần tử vào hàng đợi ưu tiên
void add(int a[], int &size, int element) {
    if (isFull(size)) {
        cout << "Queue overflow! Cannot insert " << element << endl;
        return;
    }
    a[size++] = element;
    heapify_up(a, size - 1);
    /* thêm vào vị trí cuối, truy ngược về parent nếu có xung đột thì đổi chỗ để giữ nguyên
    cấu trúc heap.
    */
}

// Xóa phần tử có ưu tiên cao nhất (max)
void pop(int a[], int &size) {
    if (isEmpty(size)) {
        cout << "Queue underflow! Nothing to pop.\n";
        return;
    }
    a[0] = a[size - 1];
    size--;
    heapify_down(a, size, 0);
    /* thay phần tử đầu bằng phần tử cuối để giữ cấu trúc cây cân bằng, sau đó tại fix ngay tại vị trí 0.
    Từ đây ta có thể xóa phần tử ở 1 vị trí bất kì vì chỉ cần xem tại vị trí đó là 1 cây con, cấu trúc cây
    cân bằng vẫn sẽ không ảnh hưởng.
    */
}

// Lấy phần tử ưu tiên cao nhất
int top_element(int a[], int size) {
    if (isEmpty(size)) {
        cout << "Queue is empty!\n";
        return -1;
    }
    return a[0];
}

// In toàn bộ hàng đợi
void print_queue(int a[], int size) {
    cout << "Priority Queue: ";
    for (int i = 0; i < size; i++) cout << a[i] << " ";
    cout << endl;
}

// Hàm main
int main() {
    int a[QUEUE_SIZE];
    int size = 0;

    add(a, size, 2);
    add(a, size, 21);
    add(a, size, 25);
    add(a, size, 28);
    add(a, size, 223);
    add(a, size, 2321);
    add(a, size, 211);
    add(a, size, 222);

    print_queue(a, size);
    cout << "Top: " << top_element(a, size) << endl;

    pop(a, size);
    cout << "Top after pop: " << top_element(a, size) << endl;
    cout << "Size: " << size << endl;

    return 0;
}
