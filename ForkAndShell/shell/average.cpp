#include <iostream>
#include <unistd.h>

using namespace std;
int main(int argc, char *argv[]) {
	if(argc!=4){
		cout<<"expected 3 arguments,but got "<<argc-1<<endl;
	}else{
	string arg1(argv[1]);
	string arg2(argv[2]);
	string arg3(argv[3]);
	float num1=stof(arg1);
	float num2=stof(arg2);
	float num3=stof(arg3);
	cout<<"average is "<<(num1+num2+num3)/3<<endl;	
	}
	char * argvv[ ]={"./shell",NULL};
	char * envp[ ]={NULL};
	execve("./shell",argvv,envp);	
}