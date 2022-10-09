#pragma once
#include<iostream>
#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#include<stdlib.h>
#include <termios.h>
using namespace std;
//文件管理类
void Doc_Update();
void Doc_Init();
//基础功能类
void Create(string User_Order);
void Show_Tables();
void Drop(string User_Order);
void Insert(string User_Order);
void Select(string User_Order);
void Update(string User_Order);
void Delete(string User_Urder);
//Helper小函数类
void StrChar_Trans(string a, char* b);
int C_Num_Counter(string a);
void Mystrcpy(char a[], char b[]);
void Modify(char a[], char b[]);
void CharClear(char a[]);
int getch(void);
//拓展类
void Alter(string User_Order);
void Tab();

struct Infor_Bar {
	int C_Num = 0;
	char val[100][100]{ '\0' };
	Infor_Bar* Next = NULL;
};
struct Table {
	char Name[100]{ '\0' };
	int Keys_Amount = 0;
	int Primary_index = 0;
	char* Keys[100];
	int Bars_Num = 0;
	Infor_Bar* head = NULL;
};


extern int Tables_Amount;
extern string User_Order;
extern int Orders_Num;
extern int Orders_Cursor;
extern string History_Orders_Lib[200];
