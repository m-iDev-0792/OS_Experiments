#include <iostream>
#include <unistd.h>
using namespace std;
int main(int argc, char *argv[]) {
	auto pid=fork();
	if(pid==0){//son process
		auto pid2=fork();
		if(pid2==0){
			cout<<"我是孙子进程,我的pid是"<<getpid()<<endl;
		}else if(pid2>0){
			cout<<"我是子进程,我的pid是"<<getpid()<<endl;
		}else{
			cerr<<"创建孙子进程失败"<<endl;
			return -1;
		}
	}else if(pid>0){//father process
		cout<<"我是父进程,我的pid是"<<getpid()<<endl;
	}else{
		cerr<<"创建子进程失败"<<endl;
		return -1;
	}
}