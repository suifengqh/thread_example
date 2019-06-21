#include<iostream>
#include<thread>
#include<unistd.h>
using namespace std;
void show(){
	cout<<"thread show()"<<endl;
}
int main(){
	std::thread t(show);
	sleep(1);
	if(t.joinable()){
		cout<<"joinable"<<endl;
		t.join();
	}
	else{
		cout<<"unjoinable"<<endl;
	}
	return 0;
}