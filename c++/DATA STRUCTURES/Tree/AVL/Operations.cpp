#include <iostream>
#include <algorithm>
using namespace std;

struct avlnode {
    int data;
    int height;
    avlnode* left;
    avlnode* right;
    avlnode(int value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

// Tính chiều cao của nút
int height(avlnode* x) {
    return x ? x->height : 0;
}

// Tính chỉ số cân bằng của nút
int balance(avlnode* x) {
    return x ? height(x->left) - height(x->right) : 0;
}

// Xoay phải
avlnode* RightRotation(avlnode* y) {
    avlnode* x = y->left;
    avlnode* T2 = x->right;

    // Thực hiện xoay
    x->right = y;
    y->left = T2;

    // Cập nhật chiều cao
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Xoay trái
avlnode* LeftRotation(avlnode* x) {
    avlnode* y = x->right;
    avlnode* T2 = y->left;

    // Thực hiện xoay
    y->left = x;
    x->right = T2;

    // Cập nhật chiều cao
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Xoay trái-phải
avlnode* LeftRightRotation(avlnode* x) {
    x->left = LeftRotation(x->left);
    return RightRotation(x);
}

// Xoay phải-trái
avlnode* RightLeftRotation(avlnode* x) {
    x->right = RightRotation(x->right);
    return LeftRotation(x);
}

// Cân bằng cây sau khi chèn hoặc xóa
avlnode* getbalance(avlnode* root) {
    root->height = max(height(root->left), height(root->right)) + 1;

    int bl = balance(root); int bll = balance(root->left); int blr = balance(root->right);

    if (bl > 1 && bll >= 0) { // LL -> xoay phải
        return RightRotation(root);
    }
    else if (bl > 1 && bll < 0) { // LR -> xoay trái-phải
        return LeftRightRotation(root);
    }
    else if (bl < -1 && blr <= 0) { // RR -> xoay trái
        return LeftRotation(root);
    }
    else if (bl < -1 && blr > 0) { // RL -> xoay phải-trái
        return RightLeftRotation(root);
    }

    return root;
}

// Thêm phần tử vào cây
avlnode* InsertElement(avlnode* root, int value) {
    if (root == nullptr) {
        return new avlnode(value);
    }

    if (value < root->data) {
        root->left = InsertElement(root->left, value);
    }
    else if (value > root->data) {
        root->right = InsertElement(root->right, value);
    }
    else return root; // Nếu phần tử đã tồn tại

    return getbalance(root); // Cân bằng cây sau khi chèn
}

// Tìm phần tử thay thế cho nút bị xóa
avlnode* FindReplaceElementRight(avlnode* target) {
    target = target->right;
    while (target && target->left) {
        target = target->left;
    }
    return target;
}

// Xóa phần tử trong cây
avlnode* RemoveElement(avlnode* root, int value) {
    if (root == nullptr) return root;

    if (value < root->data) {
        root->left = RemoveElement(root->left, value);
    } else if (value > root->data) {
        root->right = RemoveElement(root->right, value);
    } else {
        if(root->left==nullptr && root->right==nullptr){
            delete root;
            return nullptr;
        }
        else if (root->left == nullptr) {
            avlnode* temp = root->right;
            delete root;
            return temp; // Cân bằng cây ngay sau khi thay thế nút
        } else if (root->right == nullptr) {
            avlnode* temp = root->left;
            delete root;
            return temp; // Cân bằng cây ngay sau khi thay thế nút
        } else {
            // Nút có hai con
            avlnode* temp = FindReplaceElementRight(root);
            root->data = temp->data;
            root->right = RemoveElement(root->right, temp->data); // Xóa phần tử thay thế trong cây con phải
        }
    }

    // Cân bằng lại cây sau khi xóa
    return getbalance(root);
}

// Hàm inorder để in cây
void inorder(avlnode* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

int main() {
    avlnode* root = nullptr;

    root = InsertElement(root, 50);
    root = InsertElement(root, 30);
    root = InsertElement(root, 70);
    root = InsertElement(root, 20);
    root = InsertElement(root, 40);
    root = InsertElement(root, 60);
    root = InsertElement(root, 80);
    root = InsertElement(root, 10);
    root = InsertElement(root, 25);
    root = InsertElement(root, 35);
    root = InsertElement(root, 45);

    root = RemoveElement(root,50);
    root = RemoveElement(root,60);
    root = RemoveElement(root,30);
    root = RemoveElement(root,70);



    cout << root->height;



    return 0;
}
