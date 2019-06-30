#include <mutex>
#include<unistd.h>
#include<thread>
#include<iostream>
using namespace std;
class big_object
{
public:
	big_object(int i=0):data(i){}
public:
	int data;
};
 
void swap(big_object& lhs,big_object& rhs)
{
    sleep(1);
    cout<<"swap()"<<endl;
}
class X
{
private:
	big_object some_detail;
	mutable std::mutex m;
public:
	X(big_object const& sd):some_detail(sd){}

	friend void swap(X& lhs, X& rhs)
	{
		if(&lhs==&rhs)
			return;
		std::lock(lhs.m,rhs.m);//C++库会自动生成加锁顺序，即使调用顺序不一致
		std::lock_guard<std::mutex> lock_a(lhs.m,std::adopt_lock);//adopt_lock是告诉lock_guard对象mutex已经被上锁，而lock_gurad对象将获得mutex的所有权，这样就可以保证在lock可能出现异常导致没有unlock的情形不会出现，栈对象会在异常抛出后自动析构
		std::lock_guard<std::mutex> lock_b(rhs.m,std::adopt_lock);
		swap(lhs.some_detail,rhs.some_detail);
	}
};
void threadFun(X& one,X& two){
    swap(one,two);
}
int main()
{
    big_object ten(10),hundred(100);
    X one(ten),two(hundred);
    thread threadOne(threadFun,ref(one),ref(two));//不同线程有不同的参数调用顺序
    thread threadTwo(threadFun,ref(two),ref(one));
    threadOne.join();
    threadTwo.join();
    return 0;
}