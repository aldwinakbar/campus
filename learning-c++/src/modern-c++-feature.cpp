#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <memory>

#include <string.h>



using namespace std;

int main(){

    string test = "banana";

    shared_ptr<unsigned char> sample_uchar_sptr (new unsigned char[test.length()], std::default_delete<unsigned char[]>());
    unsigned char *sample_uchar = new unsigned char[test.length()];
    strcpy( (char*)( sample_uchar_sptr.get() ), test.c_str() );

    /* auto type-deduction */
    auto sample_vec = vector<pair<int,int>>{make_pair(1,2),make_pair(3,4)};
    for ( auto i : sample_vec){
        cout << i.first << " " << i.second << endl;
    }

    /* initializer_list usage */
    auto sample_init_list = {1,2,3,4,5};
    auto sample_init_list_two = {"aldwin", "akbar", "hermanudin"};
    for (auto i : sample_init_list){
        cout << i << endl;
    }
    for (auto i : sample_init_list_two){
        cout << i << endl;
    }

    /* tuples */
    auto sample_tuple = make_tuple(22, "Aldwin Hermanudin", "aldwin@hermanudin.com");

    /* lambda expression */
    auto calculate = [&](auto a, auto b){
        return a+b;
    };
    cout << calculate(12.1,32.1) << endl;
    string a = "1213";
    string b = " baana";
    cout << calculate(a, b) << endl;

    /* decltype usage */
    int test_int = 1;
    double test_double = 102.2;
    decltype(test_double + test_int) test_decltype; /* converts to double */
    test_decltype = 23.1;
    cout << test_decltype << endl;

    return 0;
}