#include<thread>
#include<iostream>
#include<utility>
using namespace std;
void fun(){
    cout<<"thread fun()"<<endl;
}
thread f(thread t){//thread object作为函数参数和返回值
    return t;
}
void g(){
    thread t(fun);
    //thread g=f(t);//thread(thread&) = delete;禁止拷贝构造，所以采用move语义
    thread g = f(std::move(t));
    if(g.joinable()){//检测joinable是有必要的
        cout<<"yes"<<endl;
        g.join();
    }
}
int main(){
    g();
    return 0;
}