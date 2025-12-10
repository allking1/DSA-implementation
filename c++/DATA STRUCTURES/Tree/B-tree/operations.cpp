#include <iostream>
#include <vector>
using namespace std;
const int t = 3; // min_degree; với t = 2, max keys = 2*t - 1 = 3
struct BTreeNode {
    vector<int> keys;          // lưu các khóa (đã cấp phát kích thước cố định)
    vector<BTreeNode*> children; // lưu con trỏ đến các con (kích thước cố định: 2*t)
    int key_count;             // số lượng khóa hiện có (chỉ số hợp lệ: 0..key_count-1)
    bool leaf;                 // kiểm tra node lá hay không

    BTreeNode(bool is_leaf) : key_count(0), leaf(is_leaf) {
        // Cấp phát mảng cố định cho keys và children
        keys.resize(2*t - 1);
        children.resize(2*t, nullptr);
    }
};
    BTreeNode* realroot = nullptr;
// Tìm kiếm khóa k trong cây B-Tree, đồng thời cập nhật parent và index (vị trí của k hoặc vị trí con cần tiếp tục)
BTreeNode* searchElement(BTreeNode* root, BTreeNode* &parent, int &index, int k) {
    if(root == nullptr) {
        cout << "Not found" << endl;
        return nullptr;
    }
    int i = 0;
    while(i < root->key_count && k > root->keys[i]) {
        i++;
    }

    if(i < root->key_count && k == root->keys[i]) {
        return root;
    }
    if(root->leaf) {
        cout << "Not found" << endl;
        return nullptr;
    }
    parent = root;
    index = i;
    return searchElement(root->children[i], parent, index, k);
}

// Hàm tách con (Split child): tách con thứ index của parent
void Split_child(BTreeNode* parent, int index) {
    BTreeNode* child = parent->children[index];
    BTreeNode* newnode = new BTreeNode(child->leaf);

    // Copy các khóa từ vị trí t đến (2*t - 1) của child sang newnode
    for(int i = 0; i < t - 1; i++){
        newnode->keys[i] = child->keys[i + t];
    }
    newnode->key_count = t - 1;
    if(!child->leaf) {
        // Copy con trỏ: từ vị trí t đến 2*t
        for(int i = 0; i < t; i++){
            newnode->children[i] = child->children[i + t];
        }
    }
    child->key_count = t - 1;

    // Dịch chuyển các khóa và children của parent sang phải để tạo chỗ cho khóa mới
    for(int j = parent->key_count; j > index; j--) {
        parent->keys[j] = parent->keys[j - 1];
    }
    parent->keys[index] = child->keys[t - 1];

    for(int j = parent->key_count + 1; j > index + 1; j--) {
        parent->children[j] = parent->children[j - 1];
    }
    parent->children[index + 1] = newnode;
    parent->key_count++;
}

// Hàm chèn vào node không đầy
void Insert_non_full(BTreeNode* root, int k) {
    if(root->leaf) {
        int i = root->key_count - 1;
        // Dịch chuyển các khóa lớn hơn k sang phải
        while(i >= 0 && k < root->keys[i]) {
            root->keys[i + 1] = root->keys[i];
            i--;
        }
        root->keys[i + 1] = k;
        root->key_count++;
    } else {
        int j = 0;
        while(j < root->key_count && k > root->keys[j]) {
            j++;
        }
        if(root->children[j]->key_count == 2*t - 1) {
            Split_child(root, j);
            if(k > root->keys[j])
                j++;
        }
        Insert_non_full(root->children[j], k);
    }
}

// Hàm chèn khóa k vào B-Tree
void insert_element(BTreeNode* &root, int k) {
    if(root == nullptr) {
        root = new BTreeNode(true);
        root->keys[0] = k;
        root->key_count = 1;
        return;
    }
    if(root->key_count == 2*t - 1) { // Nếu root đầy, tạo root mới
        BTreeNode* newroot = new BTreeNode(false);
        newroot->children[0] = root;
        Split_child(newroot, 0);
        root = newroot;
    }
    Insert_non_full(root, k);
}

// --- Các hàm hỗ trợ cho xóa khóa từ node lá ---
//
// Hàm fixLeft: Mượn khóa từ anh em bên phải của node x
void fixLeft(BTreeNode* x, BTreeNode* y, BTreeNode* parent, int index, int k) {
    // Xóa khóa k khỏi x: dịch chuyển các phần tử sang trái
    for (int i = 0; i < x->key_count; i++) {
        if (x->keys[i] == k) {
            for (int j = i; j < x->key_count - 1; j++) {
                x->keys[j] = x->keys[j + 1];
            }
            x->key_count--;
            break;
        }
    }
    // Thêm khóa từ parent vào cuối x
    x->keys[x->key_count] = parent->keys[index];
    x->key_count++;
    // Cập nhật khóa của parent bằng khóa đầu tiên của node y (sibling bên phải)
    parent->keys[index] = y->keys[0];
    // Dịch chuyển các khóa của y sang trái để xóa khóa đầu
    for (int i = 0; i < y->key_count - 1; i++) {
        y->keys[i] = y->keys[i + 1];
    }
    y->key_count--;
}

// Hàm fixRight: Mượn khóa từ anh em bên trái của node x
void fixRight(BTreeNode* x, BTreeNode* y, BTreeNode* parent, int index, int k) {
    // Xóa khóa k khỏi x: dịch chuyển các phần tử sang trái nếu cần
    for (int i = 0; i < x->key_count; i++) {
        if (x->keys[i] == k) {
            for (int j = i; j < x->key_count - 1; j++) {
                x->keys[j] = x->keys[j + 1];
            }
            x->key_count--;
            break;
        }
    }
    // Dịch chuyển các khóa của x sang phải để tạo chỗ ở đầu
    for (int i = x->key_count; i > 0; i--) {
        x->keys[i] = x->keys[i - 1];
    }
    // Chèn khóa từ parent (ở vị trí index-1) vào đầu x
    x->keys[0] = parent->keys[index - 1];
    x->key_count++;
    // Cập nhật khóa của parent bằng khóa cuối của y
    parent->keys[index - 1] = y->keys[y->key_count - 1];
    // Xóa khóa cuối của y
    y->key_count--;
}
void doLeft(BTreeNode* x, BTreeNode* y, BTreeNode* parent,int index){
    int keystemp=y->keys[0]; BTreeNode* childrentemp=y->children[0];
    for(int i=0;i<y->key_count-1;i++) y->keys[i]=y->keys[i+1];
    for(int i=0;i<y->key_count;i++) y->children[i]=y->children[i+1];
    y->key_count--; int temp = parent->keys[index];
    parent->keys[index]=keystemp;
    x->keys[x->key_count]=temp;
    x->children[x->key_count+1]=childrentemp;
    x->key_count++;
    return;

}
void doRight(BTreeNode* x, BTreeNode* y, BTreeNode* parent,int index){
    int keystemp = y->keys[y->key_count-1]; BTreeNode* childrentemp=y->children[y->key_count];
    y->key_count--;
    int temp = parent->keys[index];
    parent->keys[index]=keystemp;
    for(int i=x->key_count-1;i>=0;i--) x->keys[i+1]=x->keys[i];
    for(int i=x->key_count;i>=0;i--) x->children[i+1]=x->children[i];
    x->keys[0]=temp;
    x->children[0]=childrentemp;
    x->key_count++;
    return;
}
void mergeTwoNode(BTreeNode* x,BTreeNode* y,BTreeNode* parent,int index){
    int target = parent->keys[index];
    for(int i=index;i<parent->key_count-1;i++) parent->keys[i]=parent->keys[i+1];
    for(int i=index+1;i<parent->key_count;i++) parent->children[i]=parent->children[i+1];
    parent->key_count--;
    x->keys[x->key_count++] = target;
    int len=x->key_count;
    for(int i=0;i<y->key_count;i++){
        x->keys[x->key_count++]=y->keys[i];
    }
    for(int i=0;i<=y->key_count;i++){
        x->children[len+i]=y->children[i];
    }
    delete y;
    if(parent == realroot && parent->key_count == 0){
            delete parent;
        realroot=x;
    }
    return;

}
void fixup(BTreeNode* x){
    if(x == realroot) return;
    BTreeNode* parent = nullptr;
    int index = 0;
    x=searchElement(realroot,parent,index,x->keys[0]);
    if(index < parent->key_count && parent->children[index+1]->key_count > t-1){
        doLeft(x,parent->children[index+1],parent,index);
        return;
    }
    else if(index > 0 && parent->children[index-1]->key_count > t-1){
        doRight(x,parent->children[index-1],parent,index-1);
        return;
    }
    else{
        if(index < parent->key_count) {
            mergeTwoNode(x,parent->children[index+1],parent,index);

        }
        else{
            mergeTwoNode(parent->children[index-1],x,parent,index-1);
        }
        if(parent->key_count > 0 && parent->key_count < t-1) fixup(parent);
    }
    return;

}

// Hàm mergeNode: Hợp nhất node x và node y (node y là anh em bên phải của x)
void mergeNode(BTreeNode* x, BTreeNode* y, BTreeNode* parent, int index, int k) {
    // Hợp nhất tất cả khóa của y vào cuối x
    for (int i = 0; i < y->key_count; i++) {
        x->keys[x->key_count + i] = y->keys[i];
    }
    x->key_count += y->key_count;
    // Giải phóng node y
    delete y;
    // Dịch chuyển con của parent: loại bỏ vị trí của node y
    for (int i = index + 1; i < parent->key_count; i++) {
        parent->children[i] = parent->children[i + 1];
    }
    // Lấy khóa trung gian từ parent (vị trí index)
    int target = parent->keys[index];
    // Dịch chuyển các khóa của parent sang trái để xóa khóa trung gian
    for (int i = index; i < parent->key_count - 1; i++) {
        parent->keys[i] = parent->keys[i + 1];
    }
    parent->key_count--;
    // Xóa khóa k khỏi x
    for (int i = 0; i < x->key_count; i++) {
        if (x->keys[i] == k) {
            for (int j = i; j < x->key_count - 1; j++) {
                x->keys[j] = x->keys[j + 1];
            }
            x->key_count--;
            break;
        }
    }
    // Chèn khóa target vào x sao cho giữ thứ tự tăng dần
    int j = 0;
    while (j < x->key_count && target > x->keys[j]) {
        j++;
    }
    // Dịch chuyển các khóa của x sang phải từ vị trí j
    for (int i = x->key_count; i > j; i--) {
        x->keys[i] = x->keys[i - 1];
    }
    x->keys[j] = target;
    x->key_count++;
    if(parent == realroot && parent->key_count == 0){
        delete parent;
        realroot=x;
        return;
    }
    if(parent->key_count < t-1) fixup(parent);
}

// Hàm xóa khóa k khỏi cây B-Tree (chỉ xử lý trường hợp node lá)
void deletion(BTreeNode* &root, int k) {
    BTreeNode* parent = nullptr;
    int index = -1;
    BTreeNode* x = searchElement(root, parent, index, k);
    if (x == nullptr)
        return;  // Không tìm thấy khóa

    // Chỉ xử lý khi node chứa khóa là node lá
    if (x->leaf) {
        // Trường hợp x là root
        if (x == root) {
            if (root->key_count == 1) {
                delete root;
                root = nullptr;
            } else {
                for (int i = 0; i < root->key_count; i++) {
                    if (root->keys[i] == k) {
                        for (int j = i; j < root->key_count - 1; j++) {
                            root->keys[j] = root->keys[j + 1];
                        }
                        root->key_count--;
                        break;
                    }
                }
            }
            return;
        } else {
            // Nếu node có số khóa lớn hơn tối thiểu (t - 1), chỉ cần xóa trực tiếp
            if (x->key_count > t - 1) {
                for (int i = 0; i < x->key_count; i++) {
                    if (x->keys[i] == k) {
                        for (int j = i; j < x->key_count - 1; j++) {
                            x->keys[j] = x->keys[j + 1];
                        }
                        x->key_count--;
                        return;
                    }
                }
            }
            // Nếu node có số khóa bằng t - 1, cần mượn từ anh em hoặc hợp nhất
            else {
                if (index < parent->key_count && parent->children[index + 1]->key_count > t - 1) {
                    fixLeft(x, parent->children[index + 1], parent, index, k);
                    return;
                } else if (index > 0 && parent->children[index - 1]->key_count > t - 1) {
                    fixRight(x, parent->children[index - 1], parent, index, k);
                    return;
                } else {
                   if(index > 0){
                        mergeNode(parent->children[index - 1], x, parent, index - 1, k);

                    }
                    else{
                        mergeNode(x,parent->children[index+1],parent,index,k);
                    }


                }
            }
        }
    }

    // Nếu node không phải lá: chưa xử lý trong phiên bản này.
    return;
}

// Hàm duyệt in-order đơn giản để hiển thị các khóa trong node (duyệt trên mỗi node)
void printNode(BTreeNode* root) {
    if (root != nullptr) {
        int i;
        for (i = 0; i < root->key_count; i++) {
            if (!root->leaf)
                printNode(root->children[i]);
            cout << root->keys[i] << " ";
        }
        if (!root->leaf)
            printNode(root->children[i]);
    }
}

int main(){

    insert_element(realroot,1);
    insert_element(realroot,2);
    insert_element(realroot,3);
    insert_element(realroot,4);
    insert_element(realroot,5);
    insert_element(realroot,6);
    insert_element(realroot,7);
    insert_element(realroot,8);
    insert_element(realroot,9);
    insert_element(realroot,10);
    insert_element(realroot,11);
    insert_element(realroot,12);
    insert_element(realroot,13);
    insert_element(realroot,14);
    insert_element(realroot,15);
    insert_element(realroot,16);
    insert_element(realroot,17);
    insert_element(realroot,18);
    insert_element(realroot,19);
    insert_element(realroot,20);
    insert_element(realroot,21);
    insert_element(realroot,22);


deletion(realroot,5);
cout << realroot->children[0]->keys[1] << endl;
deletion(realroot,10);
cout << realroot->key_count<< endl;
printNode(realroot);
return 0;
}
