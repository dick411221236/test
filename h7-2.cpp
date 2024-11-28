//trie
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TrieNode {
public:
    vector<pair<char, TrieNode*>> children; // 子節點集合（保持插入順序）
    string storedString;                    // 節點儲存的壓縮字串
    bool isEndOfWord;                       // 是否為一個單字的結尾

    TrieNode() : storedString(""), isEndOfWord(false) {}
};

class Trie {
private:
    TrieNode* root;

    void deleteTrie(TrieNode* node) {
        // 釋放所有子節點
        for (auto& child : node->children) {
            deleteTrie(child.second);
        }
        // 釋放當前節點
        delete node;
    }

    // 輔助函數，用來遞迴列印 Trie 的內容
    void preorderHelper(TrieNode* node, string prefix, int level) {
        if (!node->storedString.empty()) { 
            cout << string(level * 2, ' ') << node->storedString << endl;
        }
        for (auto& child : node->children) {   //往子節點遞迴
            preorderHelper(child.second, "", level + 1);
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        deleteTrie(root);
    }

    // 插入字串到壓縮 Trie 中
    void insert(string value) {
        TrieNode* current = root;

        while (!value.empty()) {
            bool found = false;
            for (auto& child : current->children) {      //做重疊部分

                string& childString = child.second->storedString;

                int i = 0;
                while (i < childString.length() && i < value.length() && childString[i] == value[i]) {    //計算重疊多長
                    i++;
                }

                if (i > 0) { // 存在重疊部分
                    found = true;

                    if (i < childString.length()) {   // 如果重疊部分不是整個字串，拆分節點
                        TrieNode* splitNode = new TrieNode();
                        splitNode->storedString = childString.substr(i);
                        splitNode->children = move(child.second->children);
                        splitNode->isEndOfWord = child.second->isEndOfWord;

                        child.second->storedString = childString.substr(0, i);
                        child.second->children.clear();
                        child.second->children.emplace_back(splitNode->storedString[0], splitNode);
                        child.second->isEndOfWord = false;
                    }

                    current = child.second;  //因為有重疊，所以往前遞移
                    value = value.substr(i); //取沒有重疊的部分繼續去創子節點
                    break;   //跳出for迴圈
                }
            }

            if (!found) {   //沒重疊就直接創新節點，接在當前節點後面
                TrieNode* newNode = new TrieNode();
                newNode->storedString = value;
                newNode->isEndOfWord = true;
                current->children.emplace_back(value[0], newNode);
                return;
            }
        }
    }

    // 搜尋字串是否存在於壓縮 Trie 中
    bool search(string key) {
        TrieNode* current = root;

        while (!key.empty()) {
            bool found = false;
            for (auto& child : current->children) {
                string& childString = child.second->storedString;

                if (key.substr(0, childString.length()) == childString) {  //一位一位去判斷是否相同
                    current = child.second;
                    key = key.substr(childString.length());
                    found = true;
                    break;
                }
            }

            if (!found) return false; // 若找不到匹配節點
        }

        return current->isEndOfWord;
    }

    // 以前序遍歷方式印出 Trie
    void preorder() {
        cout << "[]" << endl;
        preorderHelper(root, "", 0);
    }
};

int main() {
    Trie* trie = new Trie();
    string command, key, value;

    while (1) {
        cin >> command;
        if (command == "insert") {
            cin >> value;
            trie->insert(value);
        } else if (command == "search") {
            cin >> key;
            if (trie->search(key))
                cout << "exist" << endl;
            else
                cout << "not exist" << endl;
        } else if (command == "print") {
            trie->preorder();
        } else if (command == "exit") {
            break;
        }
    }

    // 在程式結束時釋放 Trie 佔用的記憶體
    delete trie;

    return 0;
}