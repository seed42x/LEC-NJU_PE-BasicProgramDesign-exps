#include<stdio.h>
#include<iostream>
#include<string>
#include<algorithm> //引入sort()
using namespace std;
/*
Jumble猜字谜
2021/3/5
201220096 钟亚晨
对所有单词排序比对进行查找，一次性输出所有结果
*/

//###全局变量###
//#############
string key_dict[100]; //答案字典
string sorted_key_dict[100];//经排序处理的字典
string riddles_dict[100];//谜语字典
int key_amount = 0;//字典长度
int riddles_amount = 0;//谜语长度

//######获取输入######
//####################
void get_all_dict() {
	string key_buffer;//答案缓冲
	string riddles_buffer;//谜语缓冲
	
	while (cin >> key_buffer) {//答案字典获取
		if (key_buffer == "XXXXXX") break;
		else {
			key_dict[key_amount] = key_buffer;
			sort(key_buffer.begin(), key_buffer.end());
			sorted_key_dict[key_amount] = key_buffer;
			key_amount++;
		}
	}
	while (cin >> riddles_buffer) {//谜语获取
		if (riddles_buffer == "XXXXXX") break;
		else {
			sort(riddles_buffer.begin(), riddles_buffer.end());
			riddles_dict[riddles_amount] = riddles_buffer;
			riddles_amount++;
		}
	}
}

//######查询及输出######
//######################
void find_and_print() {
	string output_buffer[100];//输出缓存
	for (int i = 0; i < riddles_amount; i++) {
		int find_len = 0;//查询游标
		int current_key_amount = 0;//当前答案的暂存长度
		while (!(find_len > key_amount)) {
			if (sorted_key_dict[find_len] == riddles_dict[i]) {//查找核心部分，将找到结果存到输出缓冲
				output_buffer[current_key_amount] = key_dict[find_len];
				current_key_amount++;
			}
			find_len++;
		}
		sort(output_buffer, output_buffer + current_key_amount);//输出缓冲排序，字母序输出
		if (current_key_amount == 0) {
			cout << "NOT A VALID WORD" << endl;
			cout << "******" << endl;
		}
		else {
			for (int i = 0; i < current_key_amount - 1; i++) cout << output_buffer[i] << endl;
			cout << output_buffer[current_key_amount - 1] << endl;
			cout << "******" << endl;
		}
	}
}

//###main函数控制###
//##################
int main() {
	get_all_dict();//获取输入
	find_and_print();//查找并输出结果
	return 0;
}