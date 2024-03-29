#include<iostream>
#include<thread>
using namespace std;
void do_something(int& i){
    i++;
}
class func{
public:
	func(int& i):i_(i){}
	void operator() (){
		for(int j=0;j<100;j++)
		do_something(i_);
	}
public:
	int& i_;
};
void do_something_in_current_thread(){}
void f(){
	int local = 0;
	func my_func(local);
	std::thread t(my_func);
	try{
		do_something_in_current_thread();
	}
	catch(...){
		t.join();//确保在异常条件下join子线程
		throw;
	}
	t.join();
}
int main(){
	f();
	return 0;
}