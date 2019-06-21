#include<iostream>
#include<thread>
using namespace std;
void do_something(int& i){
	i++;
	cout<<i<<" ";
}
class func{
public:
	func(int& i):i_(i){}
	void operator()(){
		for(int j=0;j<100;j++){
			do_something(i_);
		}
	}
public:
	int &i_;
};
void oops(){
	int local = 0;
	func my_func(local);
	std::thread my_thread(my_func);
	//my_thread.detach();
	my_thread.join();
	cout<<"oops() "<<local<<endl;
}
int main(){
	oops();
	return 0;
}