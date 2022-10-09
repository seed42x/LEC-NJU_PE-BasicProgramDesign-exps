#include<stdio.h>
#include <string>
#include <conio.h>
#include <map>
#include<windows.h>
#include<stdlib.h>
#include<wincon.h>
using namespace std;


// tab键 获取相关值，并打印到屏幕上。
void tab_find_char(std::map<int, char*> store_compare_, char* store_input, int i_store_input_count, int& tab_count);
// 从字符中找到相关字符，并返回相关字符。
char* get_attach(const char* stacks_, const char* needle_);


void console_start();
void console_end();

void write(const char* message, int length);
void write(const char* message);
void read(char* buffer, size_t size);
#include <iostream>
#include "conio.h"
// 记录屏幕光标位置
static COORD curser_position;

void main()
{
	console_start();
	// 自定义的可搜索库字符集
	static std::map<int, char*> store_compare;
	store_compare[0] = "thread_parameter_";
	store_compare[1] = "parameter_";
	store_compare[2] = "build";
	store_compare[3] = "compile";

	int count = 0;
	char ch;
	while (true)
	{
		int tab_count = 0;
		char store_input[256];
		int i_store_input_count = 0;
		// 记录光标位置
		HANDLE hOut;
		CONSOLE_SCREEN_BUFFER_INFO bInfo;
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hOut, &bInfo);
		curser_position.X = bInfo.dwCursorPosition.X;
		curser_position.Y = bInfo.dwCursorPosition.Y;

		do
		{
			ch = (char)_getch();
			if (ch != '\n')
			{
				if (ch == 'q')
				{
					break;
				}
				else if (ch == 9)
				{
					tab_find_char(store_compare, store_input, i_store_input_count, tab_count);
					tab_count++;
				}
				// 接受数字和全部字母和部分特殊符号。
				else if ((ch >= 48 && ch <= 57) || (ch >= 65 && ch <= 122))
				{
					char* temp_char = new char[1];
					temp_char[0] = ch;
					write(temp_char, 1);
					store_input[i_store_input_count] = ch;
					i_store_input_count++;
				}
			}
		} while (ch != '\r');
		write("\n");
	}
	console_end();
}

void tab_find_char(std::map<int, char*> store_compare_, char* store_input, int i_store_input_count, int& tab_count)
{
	if (i_store_input_count < 0 || tab_count < 0)
	{
		return;
	}

	int map_size = store_compare_.size();
	tab_count = tab_count % map_size;

	i_store_input_count += 1;
	store_input[i_store_input_count - 1] = '\0';
	char* pri_temp_input = new char[i_store_input_count];
	strncpy(pri_temp_input, store_input, i_store_input_count);
	int i_catch_times = 0;

	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < map_size; i++)
	{
		char* pri_get_supply = get_attach(store_compare_[i], pri_temp_input);
		if (NULL != pri_get_supply)
		{
			if (tab_count > i_catch_times)
			{
				i_catch_times++;
				continue;
			}

			//clear
			SetConsoleCursorPosition(hOut, curser_position);
			string out_put_string = "                                            ";
			write(out_put_string.c_str());

			SetConsoleCursorPosition(hOut, curser_position);
			write(store_compare_[i]);
			break;
		}
	}
	delete pri_temp_input;
	pri_temp_input = NULL;
	i_store_input_count -= 1;
	return;
}


char* get_attach(const char* stacks_, const char* needle_)
{
	char* pri_string_stack = (char*)stacks_;
	char* pri_string_needle = (char*)needle_;
	char* pri_string = strstr(pri_string_stack, pri_string_needle);
	return pri_string;
}


/*---------------------------------------------------------*/

void console_start()
{
	AllocConsole();

	DWORD dwConsoleMode;
	GetConsoleMode(NULL, &dwConsoleMode);
	dwConsoleMode ^= ENABLE_LINE_INPUT;
	dwConsoleMode ^= ENABLE_ECHO_INPUT;
	//wConsoleMode ^= ENABLE_AUTO_POSITION;

	SetConsoleMode(NULL, dwConsoleMode);
	const char* message = "welcome! test started. atuhor by zhang pengju\n";
	write(message);
}

void console_end()
{
	FreeConsole();
}

void write(const char* message, int length)
{
	if (length <= 0)
	{
		return;
	}
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), message, length, NULL, NULL);
}


void write(const char* message)
{
	int length = strlen(message);
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), message, length, NULL, NULL);
}

void read(char* buffer, size_t size)
{
	DWORD nNumberOfCharsToRead;
	BOOL result = ReadConsoleA(GetStdHandle(STD_INPUT_HANDLE), buffer, size, &nNumberOfCharsToRead, NULL);
	buffer[nNumberOfCharsToRead - 2] = 0;
}