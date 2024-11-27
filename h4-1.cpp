//動態分配一個二維陣列的迷宮，再用dfs找走出迷宮的路
#include<iostream>
#include<cstdlib>
#include<ctime>

#define SIZE 10

using namespace std;

class Node  // (r, c)
{
public:
    Node()
    {
        row = 0;
        col = 0;
    }
    Node(int r, int c)
    {
        row = r;
        col = c;
    }
    int getRow() { return row; }
    int getCol() { return col; }
    void setRow(int r)
    {
        if (r >= 0 && r < SIZE)
            row = r;
    }
    void setCol(int c)
    {
        if (c >= 0 && c < SIZE)
            col = c;
    }
private:
    int col, row;
};

class List
{
public:
    List()
    {
        top = 0;
    }
    /*
    function addElement
    Insert an element from list
    */
    void addElement(int r, int c)
    {
        if (top < SIZE * SIZE)
        {
            data[top++] = Node(r, c);
        }
    }
    /*
    function removeElement
    remove an element from list and return a pointer point to the element.
    If list is empty, return NULL.
    */
    Node* removeElement()
    {
        if (top > 0)
            return &data[--top];    //回傳被刪掉的元素的位置
        return NULL;
    }
    void printList()
    {
        int j;
        for (j = 0; j < top; j++)
        {
            cout << "(" << data[j].getRow() << ", " << data[j].getCol() << ")" << endl;
        }
    }
private:
    Node data[SIZE * SIZE];    //data 儲存點(r,c)
    int top;    //下一個可插入的位置引索
};

class Maze
{
public:
    Maze()
    {
        initMaze(SIZE);
    }

    ~Maze() {
        // 釋放 maze 二維陣列
        for (int i = 0; i < SIZE; i++) {
            delete[] maze[i];  //釋放行指標指向的陣列
        }
        delete[] maze;   //釋放存放行指標的陣列
    }

    /*
    function initMaze
    Allocate a 2-D array with s * s sizes as the map of maze.
    Inside the maze where 0 represent empty space and 1 represent wall.
    [0][0] is start point and [s - 1][s - 1] is finish point.
    Randomly generate 20% wall in the maze.
    Make sure [0][0] and [s - 1][s - 1] are 0
    */
    void initMaze(int s)
    {
        // 動態配置迷宮
        maze = new int* [s];
        for (int i = 0; i < s; i++)
            maze[i] = new int[s];

        // 初始化迷宮為空白 (0 表示空間)
        for (int i = 0; i < s; i++)
        {
            for (int j = 0; j < s; j++)
            {
                maze[i][j] = 0;
            }
        }

        // 隨機生成 20% 的牆壁 (1 表示牆壁)
        srand(time(0));
        int wallCount = (s * s) * 0.2;
        while (wallCount > 0)
        {
            int r = rand() % s;
            int c = rand() % s;
            if ((r == 0 && c == 0) || (r == s - 1 && c == s - 1)) // 起點和終點不能是牆
                continue;
            if (maze[r][c] == 0) // 確保位置沒有牆
            {
                maze[r][c] = 1;
                wallCount--;
            }
        }
    }

    /*
    function getPath
    This function will find a path between start point and finish point.
    Return a list containing the path information inside.
    If there is no path between two points, then the list will be empty.
    */
    List* getPath()
    {
        List* path = new List();
        bool visited[SIZE][SIZE] = { false };   //初始化布林陣列(全設為false)

        if (dfs(0, 0, path, visited))
            return path;

        return nullptr; // 若找不到路徑，回傳nullptr
    }

    /*
    function dfs
    深度優先搜尋用來尋找從起點到終點的路徑
    */
    bool dfs(int r, int c, List* path, bool visited[SIZE][SIZE])
    {
        // 如果超出邊界或碰到牆壁或已經走過此位置，則返回 false
        if (r < 0 || c < 0 || r >= SIZE || c >= SIZE || maze[r][c] == 1 || visited[r][c])
            return false;

        // 將當前節點標記為已訪問
        visited[r][c] = true;

        // 將當前位置加入路徑
        path->addElement(r, c);

        // 如果到達終點，則找到路徑
        if (r == SIZE - 1 && c == SIZE - 1)
            return true;

        // 遞迴搜尋四個方向：上、下、左、右
        if (dfs(r - 1, c, path, visited) || dfs(r + 1, c, path, visited) ||
            dfs(r, c - 1, path, visited) || dfs(r, c + 1, path, visited))
            return true;

        // 如果此路徑無效，則從路徑中移除當前節點
        path->removeElement();

        return false;
    }

    void printMaze()
    {
        int j, k;
        for (j = 0; j < SIZE; j++)
        {
            for (k = 0; k < SIZE; k++)
            {
                if (maze[j][k] == 0)
                    cout << " ";
                else if (maze[j][k] == 1)
                    cout << "*";
            }
            cout << "\n";
        }
    }

private:
    int** maze;
};

int main()
{
    Maze* maze = new Maze();
    maze->printMaze();

    List* path = maze->getPath();
    if (path != nullptr)
    {
        cout << "\nPath from start to end:\n";
        path->printList();
        delete path; // 釋放動態分配的 List
    }
    else
    {
        cout << "No path found!\n";
    }

    delete maze;  // 釋放 Maze 物件

    return 0;
}