#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
struct Node{
    int data;
    Node *left;
    Node *right;
    Node(int value): data(value), left(nullptr), right(nullptr) {}
};

Node* InsertElement(Node* root,int value){
    if(root ==  nullptr){
        return new Node(value);
    }
    if(value < root->data) root->left=InsertElement(root->left,value);
    else if(value > root->data) root->right=InsertElement(root->right,value);
    return root;
}

Node *SearchElement(Node *root, int value){
    if(root == nullptr || root->data == value){
        return root;
    }
    if(value < root->data) return SearchElement(root->left,value);
    return SearchElement(root->right,value);
}

void InorderTraversal(Node *root){
    if(root == nullptr) return;
    InorderTraversal(root->left);
    // viet ham can kiem tra
    InorderTraversal(root->right);
}

Node* FindReplaceElementRight(Node* target){
    target = target->right;
    while(target != nullptr && target->left !=nullptr){
        target=target->left;
    }
    return target;
}

Node* DeleteElement(Node *root, int value){
    if(root == nullptr) return root;
    if(value < root->data ) root->left=DeleteElement(root->left,value);
    else if(value > root->data ) root->right=DeleteElement(root->right,value);
    else{
            // no chlid
        if(root->right == nullptr && root->left == nullptr){
            delete root;
            return nullptr;
        }
        // 1 chlid
        else if(root->left == nullptr){
            Node *temp=root->right;
            delete root; // cut the link
            return temp;
        }
        else if(root->right == nullptr){
            Node *temp=root->left;
            delete root; // cut the link
            return temp;
        }
        // 2 children
        else{
            Node *replacetarget = FindReplaceElementRight(root);
            root->data=replacetarget->data;
            root->right=DeleteElement(root->right,root->data);
            return root;
        }

    }
    return root;
}

Node* FindMinimum(Node *root){
    if(root == nullptr) return root;
    while(root != nullptr && root->left != nullptr){
        root=root->left;
    }
    return root;
}

Node *FindMaximum(Node *root){
    if(root == nullptr) return root;
    while(root != nullptr && root->right != nullptr){
        root=root->right;
    }
    return root;
}

int FindMaximumPath(Node* root){ // count nodes
    if(root ==  nullptr) return 0;
    return 1+max(FindMaximumPath(root->left),FindMaximumPath(root->right));
}

 // Overlap
Node* FindLeafDeepest(Node *root){
    if (root == nullptr || (root->left == nullptr && root->right == nullptr)){
        return root;
    }
    if(FindMaximumPath(root->left) > FindMaximumPath(root->right)) return FindLeafDeepest(root->left);
    return FindLeafDeepest(root->right);

}
// optimized solution
void FindLeaf(Node *root,int currentdeepth, int &maxdeepth,Node* &deepestleaf){
    if(root == nullptr) return;
    // found a leaf
    if(root->left == nullptr && root->right == nullptr){
        if(currentdeepth > maxdeepth){
            maxdeepth=currentdeepth;
            deepestleaf=root;
        }
    }
    FindLeaf(root->left,currentdeepth+1,maxdeepth,deepestleaf);
    FindLeaf(root->right,currentdeepth+1,maxdeepth,deepestleaf);
}

Node *FindLeafDeepest2(Node * root){
    int maxdeepth=-1;
    Node *Leaftemp=nullptr;
    FindLeaf(root,0,maxdeepth,Leaftemp);
    return Leaftemp;
}





int main(){
    Node* root = nullptr;
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
    root = InsertElement(root, 55);
    root = InsertElement(root, 65);
    root = InsertElement(root, 75);
    root = InsertElement(root, 85);
    root = InsertElement(root, 90);
    root = InsertElement(root, 95);
    root = InsertElement(root, 15);
    root = InsertElement(root, 5);
    root = InsertElement(root, 100);
    cout << root->data << endl;
    cout << FindMaximum(root)->data << ' ' << FindMaximumPath(root) << endl;
    cout << FindLeafDeepest(root)->data << ' ' << FindLeafDeepest2(root)->data << endl;

}

