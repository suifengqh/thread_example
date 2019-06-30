#include<mutex>
#include<exception>
#include<iostream>
int main(){
	std::mutex one,two;
	try{
		{
			std::lock(one,two);
			std::lock_guard<std::mutex> lock1(one, std::adopt_lock);
			std::lock_guard<std::mutex> lock2(two, std::adopt_lock);
			throw 1;
			std::cout<<"locking..."<<std::endl;
		}
	}catch(int){
		std::cout<<"catch..."<<std::endl;
	}
	if(!one.try_lock()|| !two.try_lock())
		std::cout<<"failure"<<std::endl;
	else
		std::cout<<"success"<<std::endl;
	return 0;
}