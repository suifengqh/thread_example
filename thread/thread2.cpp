#include<thread>
#include<iostream>
using namespace std;
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
		data = nullptr;
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
    test one;
    std::thread myThread(one);//函数对象被拷贝进线程空间
    myThread.join();
    return 0;
}