#include<thread>
#include<iostream>
using namespace std;
//using namespace boost;
class test{
public:
	void operator()() const{
		cout<<"operator() "<<*data<<endl;
	}
	test(int a=10){
		cout<<"constructor"<<endl;
		data=new int(a);
        }
	~test(){
		delete data;
	}
	int get() const{
		return *data;
	}
	test(const test& one){
		cout<<"copy constructor"<<endl;
		data=new int(one.get());//深拷贝，否则段错误
	}
private:
	int* data;
};
int main(){
	//std::thread myThread(test());//错误，会被误以为一个无参数的函数指针并返回一个test对象，从而返回一个thread对象而不是启动线程
	std::thread myThread((test()));//多余的括号用于防止被解释为一个函数
	//thread myThread{test()};//书上这种用法，编译通不过
	//也可以用函数对象test one(11);thread myThread(one);
	myThread.join();
	return 0;
}