#include<iostream>
#include<mutex>
#include<unistd.h>
#include<thread>
#include<functional>
using namespace std;
class test{
public:
	friend void orderLock(test& one,test& two){
		if(&one.m>&two.m){
			lock_guard<mutex> smallGuard(two.m);
			sleep(1);
			cout<<"the second argument's mutex smaller"<<endl;
			lock_guard<mutex> bigGuard(one.m);
		}
		else if(&one.m==&two.m)
			cout<<"lock the same mutex"<<endl;
		else{
			lock_guard<mutex> smallGuard(one.m);
			sleep(1);
			cout<<"the first argument's mutex smaller"<<endl;
			lock_guard<mutex> bigGuard(two.m);
		}
	}
private:
	mutex m;
};
void threadFun(test& one,test& two){//#2
    orderLock(one,two);
    cout<<&one<<" "<<&two<<" lock success"<<endl;
}
int main(){
    test one,two;
    cout<<&one<<" "<<&two<<endl;
    //orderLock(one,two);//#1#
    //orderLock(two,one);//#1#
    thread threadOne(threadFun,ref(one),ref(two));//#2   注意这里要用ref将test对象转换为引用传递到子线程中去，否则thread会拷贝test对象从而拷贝mutex，而mutex::mutex(const mutex&)=delete从而会报错
    thread threadTwo(threadFun,ref(two),ref(one));//#2
    threadOne.join();
    threadTwo.join();//这里要说明的是多线程间共享锁不是什么好事情
    return 0;
}