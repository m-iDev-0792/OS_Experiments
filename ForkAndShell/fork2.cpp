#include <iostream>
#include <unistd.h>
using namespace std;
int main(int argc, char *argv[]) {
	auto son1=fork();
	if(son1==0){
		cout<<"我是第一个子进程,我的pid是"<<getpid()<<endl;
	}else if(son1>0){
		cout<<"我是父进程,我的第一个子进程的pid为"<<son1<<endl;
		auto son2=fork();
		if(son2==0){
			cout<<"我是第二个子进程,我的pid是"<<getpid()<<endl;
		}else if(son2>0){
			cout<<"我是父进程,我的第二个子进程的pid为"<<son2<<endl;
		}else{
			cerr<<"我是父进程,我的第二个子进程分配失败了"<<endl;
		}
	}else{
		cerr<<"我是父进程,我的第一个子进程分配失败了"<<endl;
	}
}