#include<thread>
#include<unistd.h>
#include<sys/syscall.h>
#include<iostream>
using namespace std;
void show(){
	cout<<"hello wolrd "<<syscall(SYS_gettid)<<endl;
}
int main(){
	std::thread t(show);//这里还可以t(&show)也能成功和pthread_create一样
	cout<<"main pid "<<syscall(SYS_gettid)<<" "<<t.get_id()<<endl;
	//t.detach();
	if(!t.joinable())
		cout<<"thread unjoinable"<<endl;
	else{
		cout<<"thread joinable"<<endl;
		t.join();
	}
	return 0;
}