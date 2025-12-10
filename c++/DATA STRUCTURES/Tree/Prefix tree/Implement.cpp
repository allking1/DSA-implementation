#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

struct Trie {
    Trie* children[26]; // Mỗi node có tối đa 26 nhánh tương ứng a–z
    bool isEnd;         // Đánh dấu node kết thúc của 1 từ

    Trie() {
        isEnd = false;
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
    }
};

// Thêm một từ vào cây Trie
void insert(Trie* root, const string& s) {
    for (char c : s) {
        int idx = c - 'a';
        if (!root->children[idx]) {
            root->children[idx] = new Trie();
        }
        root = root->children[idx];
    }
    root->isEnd = true; // Đánh dấu kết thúc từ
}

// Tìm kiếm một từ trong Trie
void search(Trie* root, const string& s) {
    for (char c : s) {
        int idx = c - 'a';
        if (!root->children[idx]) {
            cout << "doesn't exist\n";
            return;
        }
        root = root->children[idx];
    }
    if (root->isEnd)
        cout << "Existed\n";
    else
        cout << "doesn't exist\n";
}

// Kiểm tra xem node hiện tại có phải là lá (không có nhánh con)
bool isLeaf(Trie* node) {
    for (int i = 0; i < 26; i++)
        if (node->children[i])
            return false;
    return true;
}

// Xóa một từ ra khỏi cây Trie
void deleteWord(Trie* root, const string& s) {
    int n = s.size();
    vector<Trie*> path; // Lưu đường đi từ root đến từng node của từ
    Trie* current = root;

    // Lưu từng node trong đường đi
    for (char c : s) {
        int idx = c - 'a';
        if (!current->children[idx]) return; // Không tồn tại từ
        path.push_back(current->children[idx]);
        current = current->children[idx];
    }

    int u = n;
    // Duyệt từ node cuối lên để xóa nếu là lá và không phải điểm kết thúc của từ khác
    while (u > 0 && isLeaf(path[u - 1]) && !path[u - 1]->isEnd) {
        delete path[u - 1];
        if (u == 1) {
            root->children[s[0] - 'a'] = nullptr;
        } else {
            path[u - 2]->children[s[u - 1] - 'a'] = nullptr;
        }
        u--;
    }

    // Nếu từ cần xóa là prefix của từ khác -> chỉ cần xóa cờ isEnd
    if (u == n) path[u - 1]->isEnd = false;
}

// Giải phóng toàn bộ bộ nhớ Trie
void freeTrie(Trie* node) {
    for (int i = 0; i < 26; ++i) {
        if (node->children[i])
            freeTrie(node->children[i]);
    }
    delete node;
}

Trie* deletebyrecursion(Trie* root, const string &s, int depth = 0) {
    // Bảo vệ root null
    if (root == nullptr) return nullptr;

    // Khi đã duyệt hết chuỗi
    if (depth == s.length()) {
        if (root->isEnd) root->isEnd = false;

        // Nếu là lá thì xóa node
        if (isLeaf(root)) {
            delete root;
            return nullptr;
        }

        return root; // return sớm
    }

    int index = s[depth] - 'a';
    root->children[index] = deletebyrecursion(root->children[index], s, depth + 1);

    // Sau khi xử lý node con, xét xem node hiện tại còn cần giữ không
    if (isLeaf(root) && root->isEnd == false) {
        delete root;
        return nullptr;
    }

    return root;
}

int main() {
    Trie* root = new Trie();

    insert(root, "toansamba");
    insert(root, "toandeptrai");
    insert(root, "abc");
    insert(root, "abcd");
    insert(root,"a");

    root = deletebyrecursion(root, "abcd");
    root = deletebyrecursion(root,"abc");
    root = deletebyrecursion(root,"a");



    search(root, "abc");    // Có
    search(root, "abcd");   // Không
    search(root,"a");

    freeTrie(root);         // Dọn sạch bộ nhớ
    return 0;
}
