#include<stdio.h>
#include<iostream>
using namespace std;
/*
Vowel_move_right
2021/3/5
201220096 钟亚晨
*/

//###元音右移###
//##############
string move(string vowel_buffer, int vowel_amount, int offset) {
	char result[100]{};//存储右移后的元音
	int real_offset = 0;
	if(vowel_amount != 0) real_offset = offset % vowel_amount;//去除无效右移
	int result_cursor = 0;
	//考虑“整体前移”以实现等价右移
	for (int i = vowel_amount - real_offset; vowel_buffer[i] != '\0'; i++) {//倒数offset的那一段移至前边
		result[result_cursor] = vowel_buffer[i];
		result_cursor++;
	}
	for (int i = 0; i < vowel_amount - real_offset; i++) {//其余移至后边
		result[result_cursor] = vowel_buffer[i];
		result_cursor++;
	}
	return result;
}


//###单个单词处理###
//##################
void handle_f() {
	int offset;//右移量
	int vowel_amount = 0;//元音数目
	int no_vowel_amount = 0;//非元音数目
	int final_word_index = 0;//游标
	string word;//单词
	char final_word[100]{};//最终单词
	char vowel_buffer[100]{};//元音右移场所
	int vowel_index[100]{};//元音于原单词下标记录

	cin >> word >> offset;
	for (int i = 0; word[i] != '\0'; i++) {
		if (word[i] == 'a' || word[i] == 'i' || word[i] == 'u' || word[i] == 'e' || word[i] == 'o') {//记录元音
			vowel_buffer[vowel_amount] = word[i];//整合元音
			vowel_index[vowel_amount] = i;//下标记录
			vowel_amount++;
		}
		else {//非元音原位不动
			final_word[final_word_index] = word[i];
		}
		final_word_index++;
	}
	string vowel_lib = move(vowel_buffer, vowel_amount, offset);//在场所中实现“元音右移”
	for (int i = 0; i < vowel_amount; i++) {//导入右移完成的元音
		final_word[vowel_index[i]] = vowel_lib[i];
	}
	cout << final_word << endl;//输出结果
}

//###main函数控制###
//##################
int main() {
	int words_amount;//总共处理单词数目
	cin >> words_amount;
	for (int i = 0; i < words_amount; i++) {
		handle_f();
	}
	return 0;
}