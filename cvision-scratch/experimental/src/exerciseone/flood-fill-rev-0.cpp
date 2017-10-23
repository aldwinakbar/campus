#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void flood_fill(vector<vector<int>> &screen,vector<pair<Point,int>> &region, int x, int y, int prevC, int newC, int type){

    int M = screen[0].size();
    int N = screen.size();
    // Base cases
    if (x < 0 || x >= M || y < 0 || y >= N)
        return;
    if (screen[x][y] != prevC)
        return;
 
    // Replace the color at (x, y)
    region.push_back(make_pair(Point(x,y),screen[x][y]));
    screen[x][y] = newC;
    
    if(type == 1){
        // Recur for all direction
        flood_fill(screen, region, x+1, y, prevC, newC, type);
        flood_fill(screen,region, x-1, y, prevC, newC, type);
        flood_fill(screen,region, x, y+1, prevC, newC, type);
        flood_fill(screen, region,x, y-1, prevC, newC, type);

        flood_fill(screen,region, x-1, y+1, prevC, newC, type);
        flood_fill(screen,region, x+1, y+1, prevC, newC, type);
        flood_fill(screen,region, x+1, y-1, prevC, newC, type);
        flood_fill(screen, region,x-1, y-1, prevC, newC, type);
    }
    
    else{
        // Recur for north, east, south and west
        flood_fill(screen,region, x+1, y, prevC, newC, type);
        flood_fill(screen,region, x-1, y, prevC, newC, type);
        flood_fill(screen,region, x, y+1, prevC, newC, type);
        flood_fill(screen,region, x, y-1, prevC, newC, type);
    }
}
 
// It mainly finds the previous color on (x, y) and
// calls floodFillUtil()
void flood_fill(vector<vector<int>> &screen,vector<pair<Point,int>> &region, int x, int y, int newC, int type)
{
    int prevC = screen[x][y];
    flood_fill(screen,region, x, y, prevC, newC, type);
}
pair<Point,Point> minmax_coordinate(vector<pair<Point,int>> &region){
    int x_min = region[0].first.x;
    int y_min = region[0].first.y;
    int x_max = 0;
    int y_max = 0;
    for (pair<Point,int> value : region){
        if(value.first.x < x_min) x_min = value.first.x;
        if(value.first.y < y_min) y_min = value.first.y;

        if(value.first.x > x_max) x_max = value.first.x;
        if(value.first.y > y_max) y_max = value.first.y;        
    }
    x_max -= x_min;
    y_max -= y_min;
    return make_pair(Point(x_min,y_min), Point(x_max+1, y_max+1));
}

void normalize_region(vector<pair<Point,int>> &region, Point &min_coor){
    for (pair<Point,int> &value : region){
        value.first.x -= min_coor.x;
        value.first.y -= min_coor.y;
    }
}

int main()
{
    vector<vector<int>> screen {{1, 1, 1, 1, 1, 1, 1, 1},
                                {1, 1, 1, 1, 1, 1, 0, 0},
                                {1, 0, 0, 1, 1, 2, 1, 1},
                                {1, 2, 2, 2, 2, 0, 1, 0},
                                {1, 1, 1, 2, 2, 0, 1, 0},
                                {1, 1, 1, 2, 2, 2, 2, 0},
                                {1, 1, 1, 1, 2, 1, 1, 1},
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
    vector<pair<Point,int>> region;

    cout << "Orginal screen before call to floodFill: \n";
    for (int i=0; i<M; i++)
    {
        for (int j=0; j<N; j++)
           cout << screen[i][j] << " ";
        cout << endl;
    }

    cout << endl;

    flood_fill(screen,region, x, y, newC,0);
 
    cout << "Updated screen after call to 4 point floodFill: \n";
    for (int i=0; i<M; i++)
    {
        for (int j=0; j<N; j++)
           cout << screen[i][j] << " ";
        cout << endl;
    }

    cout << endl;

    cout << "Region Coordinate: \n";
    for (pair<Point,int> value : region){
        cout << "[" << value.first.x << " " << value.first.y << "]" << " " << value.second << endl;
    }

    pair<Point,Point> minmax_coor = minmax_coordinate(region);
    cout << "Min-Max Coordinate : " << minmax_coor.first  << " " << minmax_coor.second << endl;
    
    normalize_region(region, minmax_coor.first);
    vector<vector<int>> new_screen (minmax_coor.second.x, vector<int>(minmax_coor.second.y, 0));
    
    cout << "Normalize Region Coordinate: \n";
    for (pair<Point,int> value : region){
        cout << "[" << value.first.x << " " << value.first.y << "]" << " " << value.second << endl;
        new_screen[value.first.x][value.first.y] = value.second;
    }
    cout << endl;

    cout << "Normalize Region Coordinate: \n";
    for (int i=0; i< new_screen.size(); i++){
        for (int j=0; j<new_screen[0].size(); j++)
           cout << new_screen[i][j] << " ";
        cout << endl;
    }
}