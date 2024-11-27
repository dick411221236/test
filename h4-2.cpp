//用鏈結串列
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define SIZE 10
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class Grid   //每個Grid代表一個格子
{
public:
    Grid() { Grid(0); }
    Grid(int s)
    {
        state = s;
        dir[UP] = NULL;
        dir[DOWN] = NULL;
        dir[LEFT] = NULL;
        dir[RIGHT] = NULL;
    }
    Grid* getDir(int d) { return dir[d]; }
    int getState() { return state; }
    void setDir(int d, Grid* g) { dir[d] = g; }
    void setState(int s) { state = s; }

private:
    Grid* dir[4];
    int state;
};

struct List
{
public:
    List() { top = 0; }
    
    void addElement(Grid* g)
    {
        if (top < SIZE * SIZE)
        {
            data[top++] = g;
        }
    }
    
    Grid* removeElement()
    {
        if (top > 0)
        {
            return data[--top];
        }
        return NULL;
    }
    
    void printPath()
    {
        for (int j = 1; j < top; j++)
        {
            if (data[j] == data[j - 1]->getDir(UP)) { cout << "UP\n"; }
            else if (data[j] == data[j - 1]->getDir(DOWN)) { cout << "DOWN\n"; }
            else if (data[j] == data[j - 1]->getDir(LEFT)) { cout << "LEFT\n"; }
            else if (data[j] == data[j - 1]->getDir(RIGHT)) { cout << "RIGHT\n"; }
        }
    }

private:
    Grid* data[SIZE * SIZE];
    int top;  //下一個的位置
};

class Maze
{
public:
    Maze() { initMaze(SIZE); }

    ~Maze() { delete[] maze; }

    void initMaze(int s){
        maze = new Grid[s * s]; // 動態分配迷宮，每個maze[i]都是一個Grid(不是Grid*)
    
        //初始狀態位置全為0
        for (int i = 0; i < s * s; i++)  
            maze[i].setState(0);

        // 隨機生成 20% 的牆壁
        srand(time(0));
        int wallCount = (s * s) * 0.2;
        while (wallCount)
        {
            int r = rand() % s;
            int c = rand() % s;

            // 確保起點 (0,0) 和終點 (s-1, s-1) 不是牆
            if ((r == 0 && c == 0) || (r == s - 1 && c == s - 1))
                continue;

            // 確認這個位置還不是牆
            if (maze[r * s + c].getState() == 0){
                maze[r * s + c].setState(1); // 設置為牆
                wallCount--;
            }
        }
            // 設置相鄰格子的指針
            for (int i = 0; i < s; i++)
            {
                for (int j = 0; j < s; j++)
                {
                    int idx = i * s + j;
                    if (i > 0) maze[idx].setDir(UP, &maze[(i - 1) * s + j]);     // 向上
                    if (i < s - 1) maze[idx].setDir(DOWN, &maze[(i + 1) * s + j]); // 向下
                    if (j > 0) maze[idx].setDir(LEFT, &maze[i * s + (j - 1)]);    // 向左
                    if (j < s - 1) maze[idx].setDir(RIGHT, &maze[i * s + (j + 1)]); // 向右
                }
            }
    }

    bool dfs(int x, int y, List* path, bool visited[SIZE][SIZE])
    {
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || visited[x][y] || maze[x * SIZE + y].getState() == 1)
        {
            return false;
        }

        path->addElement(&maze[x * SIZE + y]); // 加入當前點到路徑
        visited[x][y] = true;

        if (x == SIZE - 1 && y == SIZE - 1)
        {
            return true; // 終點
        }

        // 搜索四個方向
        if (dfs(x - 1, y, path, visited) || // 向上
            dfs(x + 1, y, path, visited) || // 向下
            dfs(x, y - 1, path, visited) || // 向左
            dfs(x, y + 1, path, visited))   // 向右
        {
            return true;
        }

        // 若該路徑無法到達終點，則回退
        path->removeElement();
        return false;
    }

    List* getPath()
    {
        List* path = new List();
        bool visited[SIZE][SIZE] = { false }; // 紀錄是否走過該點

        if (dfs(0, 0, path, visited))
        {
            return path; // 找到路徑，返回路徑列表
        }

        delete path;  // 沒有路徑，釋放記憶體
        return nullptr; // 回傳空指標表示無路徑
    }

    void printMaze()
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                cout << maze[i * SIZE + j].getState();
            }
            cout << endl;
        }
    }

private:
    Grid* maze;
};

int main()
{
    Maze* maze = new Maze();  // 動態分配 Maze
    maze->printMaze();

    List* path = maze->getPath();  // 動態分配 List
    if (path != nullptr)
    {
        cout << "\nPath found:\n";
        path->printPath();
        delete path;  // 釋放 List 記憶體
    }
    else
    {
        cout << "No path found!\n";
    }

    delete maze;  // 釋放 Maze 記憶體

    return 0;
}