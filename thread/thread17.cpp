#include<iostream>
#include<thread>
#include<functional>
#include<algorithm>
#include<vector>
#include<stdio.h>
using namespace std;
class fun{
public:
	explicit fun(int i=0):data(i){}
	void operator()(){
		printf("%d\n",data);//cout会出现乱序
	}
private:
	int data;
};
int main(){
    std::vector<thread> threads;
    for(int i=0;i<10;i++)
        threads.push_back(thread(fun(i)));
    for_each(threads.begin(),threads.end(),std::mem_fn(&thread::join));//std::mem_fn这里将一个类成员函数转换为普通函数来使用
    return 0;
}