#include<iostream>
#include<thread>
using namespace std;
int main(){
	std::thread t([](){cout<<"lambda test"<<endl;});
	t.join();
	return 0;
}