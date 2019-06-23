#include<iostream>
#include<thread>
#include<unistd.h>
using namespace std;
class thread_gurad{
public:
	explicit thread_gurad(thread& t):t_(t)
	{
		if(!t_.joinable())
			cout<<"t_ can't joinable"<<endl;
		cout<<"thread_gurad"<<endl;
	}
	~thread_gurad(){
		t_.join();
		cout<<"~thread_gurad"<<endl;
	}
	thread_gurad(const thread_gurad&) = delete;
	thread_gurad& operator=(const thread_gurad&) = delete;
private:
	thread& t_;
};
void fun(){
    sleep(1);
}
int main(){
    thread t(fun);
    thread_gurad guard(t);
    return 0;
}