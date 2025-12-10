#include <iostream>
#include <algorithm>
using namespace std;

enum Color { RED, BLACK };

struct RBNode {
    int data;
    Color color;
    RBNode* parent;
    RBNode* left;
    RBNode* right;
    RBNode(int data) : data(data), color(RED), parent(nullptr), left(nullptr), right(nullptr) {}
};

RBNode* NIL;  // Sentinel NIL

// Khởi tạo sentinel NIL
void initializeNIL() {
    NIL = new RBNode(0);
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = NIL;
}

// Tạo nút mới, các con trỏ được gán sentinel NIL
RBNode* createNode(int data) {
    RBNode* node = new RBNode(data);
    node->left = node->right = node->parent = NIL;
    return node;
}

// Left Rotation: xoay trái quanh x
void leftRotate(RBNode*& root, RBNode* x) {
    RBNode* y = x->right;           // y là con phải của x
    x->right = y->left;             // chuyển cây con trái của y thành cây con phải của x
    if (y->left != NIL)
        y->left->parent = x;
    y->parent = x->parent;          // liên kết y với cha của x
    if (x->parent == NIL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;                    // x trở thành con trái của y
    x->parent = y;
}

// Right Rotation: xoay phải quanh y
void rightRotate(RBNode*& root, RBNode* y) {
    RBNode* x = y->left;            // x là con trái của y
    y->left = x->right;             // chuyển cây con phải của x thành cây con trái của y
    if (x->right != NIL)
        x->right->parent = y;
    x->parent = y->parent;          // liên kết x với cha của y
    if (y->parent == NIL)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;                   // y trở thành con phải của x
    y->parent = x;
}

// RBInsertFixup: Sửa chữa cây sau chèn để khôi phục các thuộc tính RB Tree.
void RBInsertFixup(RBNode*& root, RBNode* z) {
    while (z->parent->color == RED) {
        RBNode* gp = z->parent->parent;
        if (z->parent == gp->left) {
            RBNode* y = gp->right; // Uncle
            if (y->color == RED) {
                // Case 1: Uncle đỏ → đổi màu
                z->parent->color = BLACK;
                y->color = BLACK;
                gp->color = RED;
                z = gp;
            } else {
                if (z == z->parent->right) {
                    // Case 2: z là con phải của cha, chuyển về trường hợp Case 3
                    z = z->parent;
                    leftRotate(root, z);
                }
                // Case 3: z là con trái của cha
                z->parent->color = BLACK;
                gp->color = RED;
                rightRotate(root, gp);
            }
        } else {
            // Trường hợp đối xứng
            RBNode* y = gp->left; // Uncle
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                gp->color = RED;
                z = gp;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                gp->color = RED;
                leftRotate(root, gp);
            }
        }
    }
    root->color = BLACK;
}

// RBInsert: Chèn nút mới vào cây
void RBInsert(RBNode*& root, int data) {
    RBNode* z = createNode(data);
    RBNode* y = NIL;
    RBNode* x = root;
    while (x != NIL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else if (z->data > x->data)
            x = x->right;
        else {
            // Nếu dữ liệu trùng, không chèn lại.
            delete z;
            return;
        }
    }
    z->parent = y;
    if (y == NIL)
        root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;
    z->color = RED;
    RBInsertFixup(root, z);
}

// treeMinimum: Tìm nút có giá trị nhỏ nhất trong cây con của x
RBNode* treeMinimum(RBNode* x) {
    while (x->left != NIL)
        x = x->left;
    return x;
}

// RBTransplant: Thay thế cây con bắt đầu từ u bằng cây con bắt đầu từ v
void RBTransplant(RBNode*& root, RBNode* u, RBNode* v) {
    if (u->parent == NIL)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

// RBDeleteFixup: Sửa chữa cây sau xóa, xử lý trường hợp "double black"
void RBDeleteFixup(RBNode*& root, RBNode* x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            RBNode* w = x->parent->right; // anh em của x
            if (w->color == RED) {
                // Case 1: w đỏ
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                // Case 2: w và cả hai con của w đều đen
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    // Case 3: w đen, w->left đỏ, w->right đen
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }
                // Case 4: w đen, w->right đỏ
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = root;
            }
        } else { // x là con phải
            RBNode* w = x->parent->left; // anh em của x
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(root, x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

// RBDelete: Xóa nút có giá trị data khỏi cây
void RBDelete(RBNode*& root, int data) {
    RBNode* z = root;
    while (z != NIL && z->data != data)
        z = (data < z->data) ? z->left : z->right;
    if (z == NIL) {
        cout << "Not found\n";
        return;
    }
    RBNode* y = z;
    Color y_original_color = y->color;
    RBNode* x;
    if (z->left == NIL) {
        x = z->right;
        RBTransplant(root, z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        RBTransplant(root, z, z->left);
    } else {
        y = treeMinimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            RBTransplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RBTransplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (y_original_color == BLACK)
        RBDeleteFixup(root, x);
}

// RBSearch: Tìm nút chứa data trong cây
RBNode* RBSearch(RBNode* root, int data) {
    if (root == NIL || root->data == data)
        return root;
    return (data < root->data) ? RBSearch(root->left, data) : RBSearch(root->right, data);
}

// Inorder traversal: in cây theo thứ tự trung vị
void inorder(RBNode* root) {
    if(root == NIL) return;
    inorder(root->left);
    cout << root->data << "(" << (root->color == RED ? "R" : "B") << ") ";
    inorder(root->right);
}

int main(){
    initializeNIL();
    RBNode* root = NIL;


    RBInsert(root, 20);
    RBInsert(root, 15);
    RBInsert(root, 25);
    RBInsert(root, 10);
    RBInsert(root, 5);
    RBInsert(root, 1);
    RBInsert(root, 30);

    RBDelete(root,15);
    RBDelete(root,10);
    RBDelete(root,20);
    inorder(root);
    cout << root->data;

    return 0;
}
