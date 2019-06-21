#include<iostream>
#include<thread>
using namespace std;
class thread_guard{
public:
        explicit thread_guard(std::thread& t):t_(t){}
        ~thread_guard(){
            if(t_.joinable()){//检测是很有必要的，因为thread::join只能调用一次，要防止其它地方意外join了
               t_.join();
            }
        }
        thread_guard(const thread_guard&) = delete;//c++11中这样声明表示禁用copy constructor需要-std=c++0x支持，这里采用boost::noncopyable已经禁止了拷贝和复制
        thread_guard& operator=(const thread_guard&) = delete;
private:
        std::thread& t_;
};
void do_something(int& i){
	i++;
}
class func{
public:
	func(int& i):i_(i){}
	void operator()(){
		for(int j=0;j<100;j++)
		do_something(i_);
	}
public:
	int& i_;
};
void do_something_in_current_thread(){}
void fun(){
	int local=0;
	func my_func(local);
	std::thread t(my_func);
	thread_guard g(t);
	do_something_in_current_thread();
}
int main(){
	fun();
	return 0;
}