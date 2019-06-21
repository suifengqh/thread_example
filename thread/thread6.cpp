#include<iostream>
#include<fstream>
#include<thread>
#include<unistd.h>
using namespace std;
void show(){
	sleep(1);
	cout<<"thread show"<<endl;
}
int main(){
	{
		thread t(show);
		t.detach();
	}
	sleep(2);
	cout<<"over"<<endl;
	return 0;
}