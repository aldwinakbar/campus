#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void find_region(vector<vector<int>> &screen,vector<vector<bool>> &marker, vector<pair<Point,int>> &region, int x, int y, int target, int type){

    int M = screen[0].size();
    int N = screen.size();
    // Base cases
    if (x < 0 || x >= M || y < 0 || y >= N)
        return;
    if (screen[x][y] != target)
        return;
    if (screen[x][y] == target && marker[x][y])
        return;
 
    // Replace the color at (x, y)
    region.push_back(make_pair(Point(x,y),screen[x][y]));
    marker[x][y] = true;
    
    if(type == 1){
        // Recur for all direction
        find_region(screen,marker, region, x+1, y, target,type);
        find_region(screen,marker,region, x-1, y, target, type);
        find_region(screen,marker,region, x, y+1, target,type);
        find_region(screen,marker, region,x, y-1, target, type);

        find_region(screen,marker,region, x-1, y+1, target, type);
        find_region(screen,marker,region, x+1, y+1, target,  type);
        find_region(screen,marker,region, x+1, y-1, target,  type);
        find_region(screen,marker, region,x-1, y-1, target,  type);
    }
    
    else{
        // Recur for north, east, south and west
        find_region(screen,marker,region, x+1, y, target,  type);
        find_region(screen,marker,region, x-1, y, target,  type);
        find_region(screen,marker,region, x, y+1, target,  type);
        find_region(screen,marker,region, x, y-1, target, type);
    }
}

vector<pair<Point,int>> find_vector_region(vector<vector<int>> &screen, int x, int y, int type){
    vector<pair<Point,int>> region;
    vector<vector<bool>> marker(screen.size(),vector<bool>(screen[0].size(), false));
    int target = screen[x][y];

    find_region(screen,marker,region, x, y, target, type);
    return region;
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
                                {1, 1, 2, 2, 2, 0, 1, 0},
                                {1, 1, 2, 2, 2, 2, 2, 0},
                                {1, 1, 2, 1, 2, 1, 1, 1},
                                {1, 1, 1, 1, 1, 1, 1, 1},};
    vector<vector<int>> other_screen(screen);

    int M = screen[0].size();
    int N = screen.size();
    int x = 4, y = 4;

    vector<pair<Point,int>> region = find_vector_region(screen,x, y,1);

    cout << "Orginal screen: \n";
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