#include <iostream>
#include <vector>
using namespace std;
 
void floodFill(vector<vector<int>> &screen, int x, int y, int prevC, int newC, int type){

    int M = screen[0].size();
    int N = screen.size();
    // Base cases
    if (x < 0 || x >= M || y < 0 || y >= N)
        return;
    if (screen[x][y] != prevC)
        return;
 
    // Replace the color at (x, y)
    screen[x][y] = newC;
    
    if(type == 1){
        // Recur for all direction
        floodFill(screen, x+1, y, prevC, newC, type);
        floodFill(screen, x-1, y, prevC, newC, type);
        floodFill(screen, x, y+1, prevC, newC, type);
        floodFill(screen, x, y-1, prevC, newC, type);

        floodFill(screen, x-1, y+1, prevC, newC, type);
        floodFill(screen, x+1, y+1, prevC, newC, type);
        floodFill(screen, x+1, y-1, prevC, newC, type);
        floodFill(screen, x-1, y-1, prevC, newC, type);
    }
    
    else{
        // Recur for north, east, south and west
        floodFill(screen, x+1, y, prevC, newC, type);
        floodFill(screen, x-1, y, prevC, newC, type);
        floodFill(screen, x, y+1, prevC, newC, type);
        floodFill(screen, x, y-1, prevC, newC, type);
    }
}
 
// It mainly finds the previous color on (x, y) and
// calls floodFillUtil()
void floodFill(vector<vector<int>> &screen, int x, int y, int newC, int type)
{
    int prevC = screen[x][y];
    floodFill(screen, x, y, prevC, newC, type);
}

bool check_xy(int x, int y, int limit){
    if (x < 0 || x >= limit || y < 0 || y >= limit) return false;
    return true;
}

void find_perimeter(vector<vector<int>> &screen,vector<vector<int>> &screen_r, int x, int y, int target){
    
    int M = screen[0].size();
    int N = screen.size();
    // Base cases
    if (x < 0 || x >= M || y < 0 || y >= N)
        return;
    if (screen[x][y] != target)
        return;
    if (screen[x][y] == target && screen_r[x][y])
        return;
    
    // Replace the color at (x, y)
    //screen[x][y] = target;
    screen_r[x][y] = 1;

    // Recur for north, east, south and west
    find_perimeter(screen,screen_r, x+1, y, target);
    find_perimeter(screen,screen_r, x-1, y, target);
    find_perimeter(screen,screen_r, x, y+1, target);
    find_perimeter(screen,screen_r, x, y-1, target);
}
// Driver program to test above function
int main()
{
    vector<vector<int>> screen {{1, 1, 1, 1, 1, 1, 1, 1},
                                {1, 1, 1, 1, 1, 1, 0, 0},
                                {1, 0, 0, 1, 1, 2, 1, 1},
                                {1, 2, 2, 2, 2, 0, 1, 0},
                                {1, 1, 1, 2, 2, 0, 1, 0},
                                {1, 1, 1, 2, 2, 2, 2, 0},
                                {1, 1, 1, 1, 1, 2, 1, 1},
                                {1, 1, 1, 1, 1, 1, 1, 1},};
    vector<vector<int>> other_screen(screen);
    vector<vector<int>> screen_r {{0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},};

    int M = screen[0].size();
    int N = screen.size();
    int x = 4, y = 4, newC = 3;

    cout << "Orginal screen before call to floodFill: \n";
    for (int i=0; i<M; i++)
    {
        for (int j=0; j<N; j++)
           cout << screen[i][j] << " ";
        cout << endl;
    }

    cout << endl;

    floodFill(screen, x, y, newC,0);
 
    cout << "Updated screen after call to 4 point floodFill: \n";
    for (int i=0; i<M; i++)
    {
        for (int j=0; j<N; j++)
           cout << screen[i][j] << " ";
        cout << endl;
    }

    cout << endl;

    floodFill(other_screen, x, y, newC,1);
 
    cout << "Updated screen after call to 8 point floodFill: \n";
    for (int i=0; i<M; i++)
    {
        for (int j=0; j<N; j++)
           cout << other_screen[i][j] << " ";
        cout << endl;
    }

    cout << endl;
    
        
    find_perimeter(screen,screen_r, x,y, screen[x][y] );
     
    cout << "Updated screen after call to 4 point perimeter search: \n";
    for (int i=0; i<M; i++){
        for (int j=0; j<N; j++)
            cout << screen_r[i][j] << " ";
        cout << endl;
    }
}