#include <iostream>
#include <vector>

using namespace std;

template <class T> class Test;
 
template <>
class Test <int>{
public:
   Test(){
       // Initializstion of data memnbers
       cout << "Specialized template object\n";
   }

   void print(){
        //Initializstion of data memnbers
        cout << "Specialized template object\n";
    }
};


int main(){

    return 0;
}