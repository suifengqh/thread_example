#include<iostream>
#include<utility>
using namespace std;
class test{
public:
	test(int i=0):data(i){}
	test(const test& one){
		cout<<"copy constructor"<<endl;
		data=one.data;
	}
	test& operator=(const test& one){
		cout<<"operator="<<endl;
		data=one.data;
		return *this;
	}
	test(test&& one){
		cout<<"move constructor"<<endl;
		data=one.data;
		one.data=0;
	}
	~test(){
		cout<<"deconstructor"<<endl;
	}
public:
    int data;
};
int main(){
    test one(10);
    cout<<"one "<<one.data<<endl;
    test two(std::move(one));
    cout<<"tow "<<two.data<<endl;
    return 0;
}