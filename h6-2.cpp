#include <iostream>
#include <string>  //stoi()
#include <stack>
#include <cctype>  //isspace()、isdigit()
#include <stdexcept>

using namespace std;

class ExpressionTree {
private:
    struct Node {
        string value;
        Node* left;
        Node* right;

        Node(const string& val) : value(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // 建構表達樹
    Node* constructTree(const string& expression) {
        stack<Node*> nodes;
        stack<char> ops;
        string token;
        for (int i = 0; i < expression.length(); i++) {
            char c = expression[i];
            if (isspace(c))   //isspace()判斷c是否為" "
                continue;
            if (isdigit(c) || (c == '-' && (!isCharOperator(expression, i)))) {  //這邊在判斷是否是負數，isdigit()判斷是否為數字
                token += c;
                while (i + 1 < expression.length() && isdigit(expression[i + 1])) {
                    token += expression[++i];
                }
                nodes.push(new Node(token));
                token.clear();
            } else if (c == '(') {
                ops.push(c);
            } else if (c == ')') {
                while (!ops.empty() && ops.top() != '(') {   //避免只有)，或者是()內為空情形
                    nodes.push(buildNode(ops.top(), nodes));
                    ops.pop();
                }
                ops.pop();  // 移除 '('
            } else if (isOperator(c)) {
                while (!ops.empty() && precedence(ops.top()) >= precedence(c)) {   //precedence(ops.top()) >= precedence(c)，判斷先乘除後加減
                    nodes.push(buildNode(ops.top(), nodes));
                    ops.pop();
                }
                ops.push(c);
            }
        }
        while (!ops.empty()) {    //最後再把剩下的合併
            nodes.push(buildNode(ops.top(), nodes));
            ops.pop();
        }
        return nodes.top();
    }

    bool isCharOperator(const string &expression, size_t index) { //回傳當下的"-"是否為減號
        while (index > 0) {
            index--;
            if (isspace(expression[index])) 
                continue; // 忽略空白字元
            return isdigit(expression[index]) || expression[index] == ')';
        }
        return false;  //index是開頭，或是index前並沒有數字(因此當前"-"不是減號)
    }

    Node* buildNode(char op, stack<Node*>& nodes) {  //將ops內的top的左右分別指向nodes內最後存入的元素，再將那2個node，pop()出nodes
        Node* right = nodes.top(); 
        nodes.pop();
        Node* left = nodes.top();
        nodes.pop();
        Node* newNode = new Node(string(1, op));
        newNode->left = left;
        newNode->right = right;
        return newNode;
    }

    int precedence(char op) {    //先乘除後加減
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/' || op == '%') return 2;
        return 0;
    }

    bool isOperator(char c) {   //判斷是否為運算符號
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
    }

    void printInFix(Node* node) {
        if (!node) return;
        if (node->left && node->right) 
            cout << "(";
        printInFix(node->left);
        cout << node->value << " ";
        printInFix(node->right);
        if (node->left && node->right)
            cout << ")";
    }

    void printPreFix(Node* node) {
        if (!node) return;
        cout << node->value << " ";
        printPreFix(node->left);
        printPreFix(node->right);
    }

    void printPostFix(Node* node) {
        if (!node) return;
        printPostFix(node->left);
        printPostFix(node->right);
        cout << node->value << " ";
    }

    int evaluate(Node* node) {
        if (!node->left && !node->right) 
            return stoi(node->value);        //stoi()將字串轉成數字
        int leftValue = evaluate(node->left);
        int rightValue = evaluate(node->right);
        if (node->value == "+") return leftValue + rightValue;
        if (node->value == "-") return leftValue - rightValue;
        if (node->value == "*") return leftValue * rightValue;
        if (node->value == "/") return leftValue / rightValue;
        if (node->value == "%") return leftValue % rightValue;
        throw invalid_argument("Invalid operator");
    }
public:
    ExpressionTree(const string& expression) {
        root = constructTree(expression);
    }

    ~ExpressionTree() { deleteTree(root); }

    void deleteTree(Node* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    void printInFixOrder() {
        printInFix(root);
        cout << endl;
    }

    void printPreFixOrder() {
        printPreFix(root);
        cout << endl;
    }

    void printPostFixOrder() {
        printPostFix(root);
        cout << endl;
    }

    int eval() {
        return evaluate(root);
    }
};

int main() {
    string infix = "( -12 + 3 ) * 4 % 5";
    getline(cin, infix);
    ExpressionTree exprTree(infix);

    cout << "Inorder: ";
    exprTree.printInFixOrder();
    cout << "Preorder: ";
    exprTree.printPreFixOrder();
    cout << "Postorder: ";
    exprTree.printPostFixOrder();
    cout << "Evaluated result: " << exprTree.eval() << endl;

    return 0;
}