//###Win下的自动补全###

// tab.cpp: 定义控制台应用程序的入口点。
//
#include <stdio.h>
#include <string>
#include <conio.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
vector <string> vc_of_str;
/*
ubuntu中的tab自动补全功能
在输入第一个操作数的时候是补全所有的指令
输入第二个操作数的时候是补全所有的当前目录下的东西
*/
int main() {
	string s1, s2;
	vc_of_str.push_back("cd");
	vc_of_str.push_back("mkdir");
	vc_of_str.push_back("ls");
	vc_of_str.push_back("vi");
	vc_of_str.push_back("sudo");
	vc_of_str.push_back("rm");
	vc_of_str.push_back("touch");
	vc_of_str.push_back("man");
	vc_of_str.push_back("cat");
	vc_of_str.push_back("clear");
	string s;
	int tabcount = 0;
	while (1) {
		int ch = _getch();
		if (ch == 8) {				//退格
			printf("%c", 8);
			printf(" ");
			printf("%c", 8);
			if (!s.empty())
				s.pop_back();
		}
		else if (ch == 13) {		//回车
			printf("\n");
			s = "";
		}
		else if (ch == 9) {			//tab
			int count = 0; vector<int>v;
			for (int i = 0; i < vc_of_str.size(); i++) {
				if (vc_of_str[i].length() >= s.length() && vc_of_str[i].substr(0, s.length()) == s) {
					count++; v.push_back(i);
				}
			}
			if (count < 1) {
				s.push_back(' ');
				printf(" ");
			}
			if (count == 1) {
				for (int i = s.length(); i < vc_of_str[v[0]].length(); i++) {
					s.push_back(vc_of_str[v[0]][i]);
					printf("%c", vc_of_str[v[0]][i]);
				}
			}
			if (count > 1 && tabcount) {
				cout << "\n" << vc_of_str[v[0]];
				for (int i = 1; i < v.size(); i++) {
					cout << "    " << vc_of_str[v[i]];
				}
				cout << endl << s;
			}

		}
		else if (ch == ' ') {

		}
		else {
			printf("%c", ch);
			s.push_back(ch);
		}
		if (ch == 9) {
			tabcount++;
		}
		else {
			tabcount = 0;
		}
	}
}


//###Linux下的getch()###
#include <termios.h>
int getch(void)
{
     struct termios tm, tm_old;
     int fd = 0, ch;
 
     if (tcgetattr(fd, &tm) < 0) {//保存现在的终端设置
          return -1;
     }
 
     tm_old = tm;
     cfmakeraw(&tm);//更改终端设置为原始模式，该模式下所有的输入数据以字节为单位被处理
     if (tcsetattr(fd, TCSANOW, &tm) < 0) {//设置上更改之后的设置
          return -1;
     }

     ch = getchar();
     if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {//更改设置为最初的样子
          return -1;
     }

     return ch;
}