#include <iostream>
#include <unistd.h>
#include <sstream>
#include <vector>
using namespace std;
int main(int argc, char *argv[]) {
	string cmd;
	cout<<"command:";
	while(getline(cin, cmd)){
		stringstream ss(cmd);
		vector<string> cmdlist;
		string temp;
		while(ss>>temp){
			cmdlist.push_back(temp);
		}
		if(cmdlist.empty()){
			cout<<"command:";
			continue;
		}
		else if(cmdlist[0]=="max"){
			if(cmdlist.size()>3){
				cout<<"expected 2 arguments,but got "<<cmdlist.size()-1<<endl;
				cout<<"command:";
				continue;
			}
			char arg1[50],arg2[50];
			strcpy(arg1, cmdlist[1].c_str());
			strcpy(arg2, cmdlist[2].c_str());
			char * argv[ ]={"./max",arg1,arg2,NULL};
			char * envp[ ]={NULL};
			execve("./max",argv,envp);
		}else if(cmdlist[0]=="min"){
			if(cmdlist.size()>3){
				cout<<"expected 2 arguments,but got "<<cmdlist.size()-1<<endl;
				cout<<"command:";
				continue;
			}
			char arg1[50],arg2[50];
			strcpy(arg1, cmdlist[1].c_str());
			strcpy(arg2, cmdlist[2].c_str());
			char * argv[ ]={"./min",arg1,arg2,NULL};
			char * envp[ ]={NULL};
			execve("./min",argv,envp);
		}else if(cmdlist[0]=="average"){
			if(cmdlist.size()!=4){
				cout<<"expected 3 arguments,but got "<<cmdlist.size()-1<<endl;
				cout<<"command:";
				continue;
			}
			char arg1[50],arg2[50],arg3[50];
			strcpy(arg1, cmdlist[1].c_str());
			strcpy(arg2, cmdlist[2].c_str());
			strcpy(arg3, cmdlist[3].c_str());
			char * argv[ ]={"./average",arg1,arg2,arg3,NULL};
			char * envp[ ]={NULL};
			execve("./average",argv,envp);
		}else if(cmdlist[0]=="quit"||cmdlist[0]=="q"){
			cout<<"good bye!"<<endl;
			return 0;
		}else{
			cout<<"unknown command:"<<cmdlist[0]<<endl;
		}
		cout<<"command:";
	}
}