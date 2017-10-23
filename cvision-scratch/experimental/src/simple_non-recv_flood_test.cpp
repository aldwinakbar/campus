// A C++ program to implement flood fill algorithm
#include<iostream>
#include <vector> 
#include <queue>          // std::queue
#include <opencv2/opencv.hpp>
using namespace std;
 
// Dimentions of paint screen
#define M 8
#define N 8
 
// A recursive function to replace previous color 'prevC' at  '(x, y)' 
// and all surrounding pixels of (x, y) with new color 'newC' and
void floodFillUtil(int screen[][N], int x, int y, int prevC, int newC)
{
    // Base cases
    if (x < 0 || x >= M || y < 0 || y >= N)
        return;
    if (screen[x][y] != prevC)
        return;
 
    // Replace the color at (x, y)
    screen[x][y] = newC;
 
    // Recur for north, east, south and west
    floodFillUtil(screen, x+1, y, prevC, newC);
    floodFillUtil(screen, x-1, y, prevC, newC);
    floodFillUtil(screen, x, y+1, prevC, newC);
    floodFillUtil(screen, x, y-1, prevC, newC);
}
 
// It mainly finds the previous color on (x, y) and
// calls floodFillUtil()
void floodFill(int screen[][N], int x, int y, int newC)
{
    int prevC = screen[x][y];
    floodFillUtil(screen, x, y, prevC, newC);
}

void NRFloodFill(vector<vector<int>> &screen, int x, int y, int target){

    queue<cv::Point> ff_operation;

    ff_operation.push(cv::Point(x,y));
    int old = screen[x][y];

    while (!ff_operation.empty()){
        cv::Point temp = ff_operation.front();
        ff_operation.pop();

        if (temp.x < 0 || temp.x >= M || temp.y < 0 || temp.y >= N) continue;
        if(screen[temp.x][temp.y] != old) continue;

        screen[temp.x][temp.y] = target;
       
        ff_operation.push(cv::Point(temp.x+1,temp.y));
        ff_operation.push(cv::Point(temp.x-1,temp.y));
        ff_operation.push(cv::Point(temp.x,temp.y+1));
        ff_operation.push(cv::Point(temp.x,temp.y-1));
    }
}

// Driver program to test above function
int main()
{
    int screen[M][N] = {{1, 1, 1, 1, 1, 1, 1, 1},
                      {1, 1, 1, 1, 1, 1, 0, 0},
                      {1, 0, 0, 1, 1, 0, 1, 1},
                      {1, 2, 2, 2, 2, 0, 1, 0},
                      {1, 1, 1, 2, 2, 0, 1, 0},
                      {1, 1, 1, 2, 2, 2, 2, 0},
                      {1, 1, 1, 1, 1, 2, 1, 1},
                      {1, 1, 1, 1, 1, 1, 1, 1},
                     };
    int x = 4, y = 4, newC = 3;
    floodFill(screen, x, y, newC);
 
    cout << "Updated screen after call to floodFill: \n";
    for (int i=0; i<M; i++)
    {
        for (int j=0; j<N; j++)
           cout << screen[i][j] << " ";
        cout << endl;
    }

    vector<vector<int>> screen_vec {{2, 1, 1, 1, 2, 2, 2, 2},
                                    {2, 1, 1, 1, 2, 1, 0, 0},
                                    {2, 0, 0, 1, 2, 0, 1, 1},
                                    {2, 2, 2, 2, 2, 0, 1, 0},
                                    {1, 1, 1, 2, 2, 0, 1, 0},
                                    {1, 1, 2, 2, 2, 2, 2, 2},
                                    {1, 2, 2, 1, 1, 2, 1, 2},
                                    {2, 2, 1, 1, 2, 2, 1, 2},};

    NRFloodFill(screen_vec,4,4,3);

    cout << "\n\nUpdated screen after call to floodFill: \n";
    for (int i=0; i<M; i++)
    {
        for (int j=0; j<N; j++)
           cout << screen_vec[i][j] << " ";
        cout << endl;
    }
}