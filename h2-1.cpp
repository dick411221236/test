#include <iostream>
#include <cstring>

#define SIZE 100

using namespace std;

class Stack
{
public:
    Stack()
    {
        top = 0;   //top=資料數量
    }

    int push(int data)
    {
        if (top >= SIZE)
        {
            return -1;
        }
        this->data[top] = data;  //this-> 強調data[]在Stack物件內
      	top++;
        return 1;
    }

    int *pop()
    {
        if (top <= 0)
        {
            return NULL;
        }
      	top--;
        return &data[top];
    }

private:
    int data[SIZE];
    int top;
};

int main()
{
    int data, *temp;
    char command[50];
    Stack *stack = new Stack();
    while(1)
    {
        cin >> command;
        if(strcmp(command, "exit") == 0) //strcmp判斷command是否為固定指令
        {
            break;
        }
        else if(strcmp(command, "push") == 0)
        {
            cout << "Please input an integer data: ";
            cin >> data;
            if(stack->push(data) == 1)
            {
                cout << "Successfully pushed data " << data << " into stack.\n";
            }
            else
            {
                cout << "Failed to push data into stack.\n";
            }
        }
        else if(strcmp(command, "pop") == 0) 
        {
            temp = stack->pop();
            if(temp == NULL)
            {
                cout << "Failed to pop a data from stack.\n";
            }
            else
            {
                cout << "Popped data " << *temp << " from stack.\n";
            }
        }
    }

    delete stack;
    return 0;
}