#include <iostream>

using namespace std;

int adder(int a, int b){

    return a+b;
}

int& adder(int& a){
    
    return a;
}

int adder_rr(int&& a, int b){ // int&& a is rvalue-references
    
    return a+b;
}

int adder_constr(int const &a, int b){ // int&& a is rvalue-references
    
    return a+b;
}

int adder_const(int const a, int b){ // int&& a is rvalue-references
    
    return a+b;
}

/*
            non-const lvalue   const lvalue   non-const rvalue   const rvalue
const T&       yes                yes            yes                yes
T&&             no                 no             yes                no
*/

int main(){

    int ref_ret = 10;
    adder(ref_ret) = ref_ret + 5;
    cout << "References Return :  " << ref_ret << endl;
    
    int sum = adder(5,10);
    cout << "LValue References :  " << sum << endl;

    //sum = adder_rr(5,10); // error at compile
    sum = adder_rr(adder(1,2),10);
    cout << "RValue References :  " << sum << endl;

    sum = adder_constr(adder(1,2),10);
    cout << "RConstValue References :  " << sum << endl;

    sum = adder_const(3,210);
    cout << "ConstValue References :  " << sum << endl;

    return 0;
}