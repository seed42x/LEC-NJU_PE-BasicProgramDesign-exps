#include<stdio.h>
#include<iostream>
using namespace std;
string obj1, obj2;//俩字符串数字
int result[2000]{ 0 };//逐位存储最后结果
int final_index;
int interger_number(string obj) {
	int counter = 0;
	for (int i = 0; obj[i] != '\0' && obj[i] != '.'; i++) counter++;
	return counter;
}
void analysis_f(string obj1, string obj2) {
	int obj1_int = interger_number(obj1);//obj1整数位数
	int obj2_int = interger_number(obj2);
	if (obj1_int >= obj2_int) {
		for (int i = 1; obj1[i - 1] != '\0'; i++) result[i] += int(obj1[i - 1]) - 48;
		for (int i = obj1_int - obj2_int + 1, j = 0; obj2[j] != '\0'; i++, j++) result[i] += int(obj2[j]) - 48;
	}
	else {
		for (int i = 1; obj2[i - 1] != '\0'; i++) result[i] += int(obj2[i - 1]) - 48;
		for (int i = obj2_int - obj1_int + 1, j = 0; obj1[j] != '\0'; i++, j++) result[i] += int(obj1[j]) - 48;
	}
}
void carry_f() {
	int flag = 0;
	for (int i = 1999; i > 0; i--) {
		if (result[i] > 0 && flag == 0) {
			final_index = i;
			flag = 1;
		}
		if (result[i] >= 10) {
			if (result[i - 1] >= 0) {//前一位不为小数点所在位时，正常进位
				result[i - 1] += int(result[i] / 10);
				result[i] = result[i] % 10;
			}
			else if (result[i - 1] < 0) {//前一点为小数点所在位时，跳过其进位
				result[i - 2] += int(result[i] / 10);
				result[i] = result[i] % 10;
			}
		}
	}
}
void output_f() {
	int first_index = 0;
	int output_buffer;//输出缓冲
	int judge = 0;
	for (int i = 0; i <= final_index; i++) {
		if (result[i] < 0) {
			judge = 1;
			break;
		}
	}
	if (judge == 1) {
		while (result[final_index] <= 0) final_index--;
	}
	while (result[first_index] == 0) first_index++;//寻找最左位
	if (result[0] == 0) {//未进位状况
		for (int i = first_index; i <= final_index; i++) {
			output_buffer = result[i];
			if (output_buffer < 0) {
				if (i == first_index && i != final_index) cout << 0 << '.';//小数点打头，左侧个位补0
				else if (i == first_index && i == final_index) cout << 0;
				else if (i != first_index && i == final_index);
				else cout << '.';//左右边都有非零数
			}
			else cout << output_buffer;//大于等于零为真值的某一位，直接输出
		}
	}
	else {//进位状况
		for (int i = first_index; i <= final_index; i++) {
			output_buffer = result[i];
			if (output_buffer < 0) cout << '.';
			else cout << output_buffer;
		}
	}
	cout << endl;
}
int main() {
	int test_case_amount;
	cin >> test_case_amount;
	for (int i = 0; i < test_case_amount; i++) {
		cin >> obj1 >> obj2;
		analysis_f(obj1, obj2);
		carry_f();
		output_f();
		for (int i = 0; i < 2000; i++) result[i] = 0;
		final_index = 0;
	}
	return 0;
}