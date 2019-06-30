#include <thread>
#include <chrono>
#include <iostream>
#include <mutex>
#include <string>
using namespace std;
struct bank_account//银行账户
{
	explicit bank_account(string name, int money)
	{
		sName = name;
		iMoney = money;
	}

	string sName;
	int iMoney;
	mutex mMutex;//账户都有一个锁mutex
};
void transfer( bank_account &from, bank_account &to, int amount )//个人觉得这里缺少一个&from == &to的条件判断
{
	if(&from == &to){
		return;
	}
	unique_lock<mutex> lock1( from.mMutex, defer_lock );//defer_lock表示延迟加锁，此处只管理mutex
	unique_lock<mutex> lock2( to.mMutex, defer_lock );
	lock(lock1, lock2 );//lock一次性锁住多个mutex防止deadlock
	//使用方法#2,采用lock_guard和tag std::adopt_lock组合也满足要求
	//lock(from.mMutex, to.mMutex);//lock一次性锁住多个mutex防止deadlock//#2
	//std::lock_guard<std::mutex> lock1(from.mMutex, std::adopt_lock);//#2
	//std::lock_guard<std::mutex> lock2(to.mMutex, std::adopt_lock);//#2
	from.iMoney -= amount;
	to.iMoney += amount;
	cout << "Transfer " << amount << " from "<< from.sName << " to " << to.sName << endl;
	cout << from.sName << " " << from.iMoney << ", " << to.sName << " " << to.iMoney << endl;
}
int main()
{
	bank_account Account1( "User1", 100 );
	bank_account Account2( "User2", 50 );
	thread t1( [&](){ transfer( Account1, Account2, 10 ); } );//lambda表达式
	thread t2( [&](){ transfer( Account2, Account1, 5 ); } );
	t1.join();
	t2.join();
	return 0;
}