#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

// 後綴樹節點類
class SuffixTreeNode {
public:
    unordered_map<char, SuffixTreeNode*> children; // 存儲子節點
    vector<int> indexes; // 存儲該節點對應的後綴起始索引(用來計算重複的數量)

    // 插入一個後綴到樹中 
    void insertSuffix(const string &suffix, int index) {
        SuffixTreeNode *current = this;
        for (char c : suffix) {
            if (current->children.find(c) == current->children.end()) {   //children.find(c)會回傳c(key)對應的value
                current->children[c] = new SuffixTreeNode();
            }
            current = current->children[c];
            current->indexes.push_back(index);
        }
    }
};

// 後綴樹類                                                                                                                                                             
class SuffixTree {
private:
    SuffixTreeNode *root;
    string text;

public:
    // 構造函數，建立後綴樹
    SuffixTree(const string &text) : text(text) {
        root = new SuffixTreeNode();
        for (int i = 0; i < text.size(); i++) {
            root->insertSuffix(text.substr(i), i);       //substr(i)回傳第i位到最後的字串(一個後綴)
        }
    }

    // 檢查子字串是否存在
    bool exist(const string &substring) {
        SuffixTreeNode *current = root;
        for (char c : substring) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        return true;
    }

    // 計算子字串出現的次數
    int count(const string &substring) {
        SuffixTreeNode *current = root;
        for (char c : substring) {
            if (current->children.find(c) == current->children.end()) {
                return 0;
            }
            current = current->children[c];
        }
        return current->indexes.size();
    }

    // 析構函數，釋放記憶體
    ~SuffixTree() {
        deleteTree(root);
    }

private:
    // 遞歸釋放記憶體
    void deleteTree(SuffixTreeNode *node) {
        for (auto &child : node->children) {
            deleteTree(child.second);    //child.second返回當前child的value
        }
        delete node;
    }
};

int main() {
    string text = "";
    while (true) {
        string temp;
        getline(cin, temp);
        if (temp == "")
            break;
        text += temp;
    }
    SuffixTree tree(text);

    string query;
    while (true) {
        getline(cin, query);
        if (query == "")
            break;
        cout << "Existence of '" << query << "': " << (tree.exist(query) ? "Yes" : "No") << endl;
        cout << "Count of '" << query << "': " << tree.count(query) << endl;
    }
    return 0;
}