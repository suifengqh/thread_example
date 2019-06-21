#include<iostream>
#include<thread>
using namespace std;
class test{
public:
	test(int i=0):data(i){}
	~test(){
		cout<<"test::destructor"<<endl;
	}
	test(const test& one){
		data=one.data;
	}
	test& operator=(const test& one){
		data=one.data;
		return *this;
	}
	void operator()(){
		cout<<"test::operator() "<<data<<endl;
	}
	void show(){
		cout<<"test::show() "<<data<<endl;
	}
public:
	int data;
};
void oops(){
	std::thread t((test()));
	t.join();
}
int main(){
	oops();
	return 0;
}