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

vector<vector<int>> create_region_array(vector<vector<int>> screen,int x, int y, int type){

    vector<pair<Point,int>> region = find_vector_region(screen,x, y,type);
    pair<Point,Point> minmax_coor = minmax_coordinate(region);
    normalize_region(region, minmax_coor.first);
    vector<vector<int>> new_screen (minmax_coor.second.x, vector<int>(minmax_coor.second.y, 0));

    for (pair<Point,int> value : region){
        new_screen[value.first.x][value.first.y] = value.second;
    }
    return new_screen;
}

vector<vector<int>> create_perimeter_array(vector<pair<Point,int>> region){

    vector<pair<Point,int>> perimeter;
    pair<Point,Point> minmax_coor = minmax_coordinate(region);
    normalize_region(region, minmax_coor.first);
    vector<vector<int>> temp_screen (minmax_coor.second.x, vector<int>(minmax_coor.second.y, 0));    
    vector<vector<bool>> marker(minmax_coor.second.x, vector<bool>(minmax_coor.second.y, false));

    for (pair<Point,int> value : region){
        temp_screen[value.first.x][value.first.y] = value.second;
    }

    for (pair<Point,int> value : region){
        marker[value.first.x][value.first.y] = true;
    }

    int x_size = marker.size();
    int y_size = marker[0].size();
    for (int i=0; i < x_size; i++){
        for (int j=0; j < y_size; j++){
           if(marker[i][j] == false ) continue;
           else if (marker[i][j] == true){
               // for 4-point style
                /*if(j-1 < 0 || i-1 < 0 || i+1 >= x_size || j+1 >= y_size || 
                   !marker[i-1][j] || !marker[i+1][j] || !marker[i][j+1] ||
                   !marker[i][j-1]){
                       perimeter.push_back(make_pair(Point(i,j),temp_screen[i][j]));
                   }
                   */
                  
                // for 8-point style
                if(j-1 < 0 || i-1 < 0 || i+1 >= x_size || j+1 >= y_size || 
                   !marker[i-1][j] || !marker[i+1][j] || !marker[i][j+1] ||
                   !marker[i][j-1] || !marker[i-1][j+1] || !marker[i+1][j+1] || 
                   !marker[i+1][j-1] || !marker[i-1][j-1]){
                       perimeter.push_back(make_pair(Point(i,j),temp_screen[i][j]));
                   }
           }
        }
    }

    vector<vector<int>> temp_perimeter (minmax_coor.second.x, vector<int>(minmax_coor.second.y, 0));

    for (pair<Point,int> value : perimeter){
        temp_perimeter[value.first.x][value.first.y] = value.second;
    }

    return temp_perimeter;
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
    int M = screen[0].size();
    int N = screen.size();
    int x = 4, y = 4;

    cout << "Orginal screen: \n";
    for (int i=0; i<M; i++)
    {
        for (int j=0; j<N; j++)
           cout << screen[i][j] << " ";
        cout << endl;
    }

    cout << endl;

    vector<vector<int>> other_screen = create_region_array(screen,x,y,0);
 
    cout << "New Array: \n";
    for (int i=0; i< other_screen.size(); i++){
        for (int j=0; j<other_screen[0].size(); j++)
           cout << other_screen[i][j] << " ";
        cout << endl;
    }

    vector<vector<int>> perimeter = create_perimeter_array(find_vector_region(screen,x, y,0));
    cout << "\nNew Perimeter: \n";
    for (int i=0; i< perimeter.size(); i++){
        for (int j=0; j<perimeter[0].size(); j++)
           cout << perimeter[i][j] << " ";
        cout << endl;
    }
}