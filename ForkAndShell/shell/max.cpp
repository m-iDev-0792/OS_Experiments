#include <iostream>
#include <unistd.h>
using namespace std;
int main(int argc, char *argv[]) {
	if(argc!=3){
		cout<<"expected 2 arguments,but got "<<argc-1<<endl;
	}else{
		string arg1(argv[1]);
		string arg2(argv[2]);
		if((arg1.find('.')!=string::npos)||(arg2.find('.')!=string::npos)){//两个中至少有一个float
			float num1=stof(arg1);
			float num2=stof(arg2);
			cout<<"max number is "<<max(num1,num2)<<endl;
		}else{//都是int
			int num1=stoi(arg1);
			int num2=stoi(arg2);
			cout<<"max number is "<<max(num1,num2)<<endl;
		}
	}
	char * argvv[ ]={"./shell",NULL};
	char * envp[ ]={NULL};
	execve("./shell",argvv,envp);
}