#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){

    vector<vector<bool>> marker(10,vector<bool>(5, false));
    cout << marker.size() << endl;
    for(bool logic : marker[0]){
        cout << "o" << endl;
    }

    string test = std::to_string(-10);
    cout << test;
    return 0;
}