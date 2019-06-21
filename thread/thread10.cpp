#include<iostream>
#include<thread>
#include<unistd.h>
using namespace std;
class test{
public:
	test(int i=0):data(i){}
	test(const test& one){
		data=one.data;
		cout<<"test::copy constructor"<<endl;
	}
	test& operator=(const test& one){
		data=one.data;
		cout<<"test::operator=()"<<endl;
		return *this;
	}
	~test(){
		cout<<"test::destructor"<<endl;
	}
public:
	int data;
};
void func(test& one){
	cout<<"func get the data "<<one.data<<endl;
}
void oops(){
	test one(10);
	std::thread t(func, std::ref(one));
	t.join();
}
int main(){
	oops();
	return 0;
}