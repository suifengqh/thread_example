#include<iostream>
#include<thread>
#include<memory>
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
public:
	int data;
};
void fun(std::shared_ptr<test> ptr){
	ptr->data++;
}
void fun_(test* ptr){
	ptr->data++;
}
void oops(){
	std::shared_ptr<test> ptr(new test(10));
	std::thread my_thread(fun,ptr);
	my_thread.join();
	cout<<"shared_ptr "<<ptr->data<<endl;
	test* one=new test(10);
	std::thread t(fun_,one);
	t.join();
	cout<<"test* "<<one->data<<endl;
	delete one;
}
int main(){
	oops();
	return 0;
}