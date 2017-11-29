#include <iostream>
#include <memory>
#include <string>

using namespace std;

class TestPointer {

public :
	string value_string;
	int value;
	static int static_value;
	string get_string(){
		return value_string;
	}

};

int main(){
	
	int *abc = new int;
	*abc = 121;
	auto cde = abc;

	// create unique_ptr
	unique_ptr<TestPointer> ptr0;
	ptr0 = make_unique<TestPointer>();
	ptr0->value = 10;

	cout << ptr0->value << endl;

	unique_ptr<int> ptr1(abc);

	cout << *(ptr1.get()) << endl;

	shared_ptr<TestPointer> ptr3(new TestPointer());
	ptr3->value = 11;
	cout << ptr3->value << endl;

	shared_ptr<TestPointer> ptr4;
	ptr4 = ptr3;
	cout << ptr4->value << endl;

	ptr3->value = 12;
	cout << ptr4->value << endl;

	shared_ptr<TestPointer> sample_one(new TestPointer());
	sample_one->value = 10;
	cout << "Pointer S1 Counter : " << sample_one.use_count() << endl;
	cout << endl;
	shared_ptr<TestPointer> sample_two = sample_one;
	shared_ptr<TestPointer> sample_four = sample_one;
	cout << "Pointer S1 Counter : " << sample_one.use_count() << endl;
	cout << endl;
	shared_ptr<TestPointer> sample_three(new TestPointer());
	sample_two = sample_three;
 	sample_four = sample_three;
	cout << "Pointer S1 Counter : " << sample_one.use_count() << endl;
	cout << "Pointer S3 Counter : " << sample_three.use_count() << endl;
	cout << endl;

	shared_ptr<TestPointer> sample_five;
	cout << "Pointer S5 Counter : " << sample_five.use_count() << endl;
	if ( sample_five == nullptr ) cout << "sample five is null" << endl;
	else cout << "sample five is not null" << endl;


	return 0;
}
