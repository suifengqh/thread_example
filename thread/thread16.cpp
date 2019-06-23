#include<thread>
#include<utility>
#include<stdexcept>
#include<stdio.h>
#include<unistd.h>
using namespace std;
class scoped_thread{
public:
	explicit scoped_thread(std::thread t)
		:t_(std::move(t))
	{
		printf("scoped_thread\n");
		if(!t_.joinable())
			throw std::logic_error("No thread");
	}
	~scoped_thread()
	{
		t_.join();
		printf("~scoped_thread\n");
	}
	scoped_thread(const scoped_thread& )=delete;
	scoped_thread& operator=(const scoped_thread&)=delete;
private:
	std::thread t_;
};
void do_something_in_current_thread(){
	
}
class func{
public:
	func(int i=0):data(i){}
	void operator()(){
		sleep(1);
	}
public:
	int data;
};
void f(){
    int local=0;
    func my_fun(local);
	//scoped_thread t(thread(my_fun));//这样是错误的
	//scoped_thread t((thread(my_fun)));//这样是正确的
    thread myThread(my_fun);
    scoped_thread t(std::move(myThread));
    printf("f() exit\n");
}
int main(){
    f();
    return 0;
}