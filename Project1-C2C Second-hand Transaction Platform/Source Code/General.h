/******************************************************************************

							201220096  钟亚晨

 ******************************************************************************
  项 目 名   : C2C_Project1
  功能描述   : 简易交易平台
  文件列表   :
*       1.Admin组：                        管理员功能集合
*       2.Merchandises组：                 x
*       3.Orders组:                        x
*       4.Users组:                         用户功能集合
*       5.Data组：                         初始化与更新
*       6.View组：                         菜单界面集合
*       7.Main.cpp                         组织所有文件&全局变量定义
******************************************************************************/


/******************************************************************************

								引用的系统头文件

 ******************************************************************************
*       1.                stdio.h                      x
*       2.                iostream                     x
*       3.                algorithm                    x
*       4.                windows.h                    x
*       5.                iomanip                      x
*       6.                time.h                       x
******************************************************************************/
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<windows.h>
#include<iomanip>
#include<time.h>
#include<string>
using namespace std;

/******************************************************************************

								   结构体定义

 ******************************************************************************
*       1.                User                      用户节点
*       2.                Merchandise               商品节点
*       3.                Order                     订单节点
******************************************************************************/
struct Time {
	int year = 0;
	int month = 0;
	int day = 0;
};

struct User {
	char ID[7]{ 'U', '0', '0', '0', '0', '0', '\0' };
	char name[21]{ '\0' };
	char passwd[11]{ '\0' };
	char contact[21]{ '\0' };
	char address[41]{ '\0' };
	double money = 0;
	int exist = 1;
	User* next = NULL;
};

struct Merchandise {
	char ID[7]{ 'M', '0', '0', '0', '0', '0', '\0' };
	char name[21]{ '\0' };
	double price = 0;
	char discribe[201]{ '\0' };
	char bussiness_id[7]{ 'U', '0', '0', '0', '0', '0', '\0' };
	Time launch_time;
	int state = 0;//0-销售中，1-已售出，2-已下架
	string state_table[3]{ "销售中", "已售出", "已下架" };
	Merchandise* next = NULL;
};

struct Order {
	char ID[7]{ 'T', '0', '0', '0', '0', '0', '\0' };
	char mer_id[7]{ 'M', '0', '0', '0', '0', '0', '\0' };
	double tamount = 0;
	Time time;
	char seller_id[7]{ 'U', '0', '0', '0', '0', '0', '\0' };
	char buyer_id[7]{ 'U', '0', '0', '0', '0', '0', '\0' };
	int exist = 1;
	Order* next = NULL;
};

/******************************************************************************

							 所有函数声明(函数列表)

 ******************************************************************************
Main.cpp:
	int main()              组织全局
******************************************************************************/
int main();
void Main_Menu();
void Init();
void Users_Update();
void Merchandises_Update();
void Orders_Update();
void Update();

void Main_Menu_View();

void User_Register_Menu_View();
void User_Register_Sure_View(User* p);
void User_Register();

void User_Login_Menu_View();
void User_Login();

void Admin_Login();

void User_Main_Menu_View();
void User_Main_Menu();

void User_Seller_Menu_View();
void User_Seller_Menu();
void User_Seller_Release_Product_View();
void User_Seller_Release_Product_Sure_View(Merchandise* p);
void User_Seller_My_Products_View();
void User_Seller_Modify_Product_View();
void User_Seller_Modify_Product_Tails(Merchandise* p);
void User_Seller_Off_Product_View();
void User_Seller_Off_Product_Sure_View(Merchandise* p);
void User_Buyer_View_All_Orders_View();
void User_Seller_View_All_Orders_View();


void User_Buyer_Menu_View();
void User_Buyer_Search_Merchandise_View();
void User_Buyer_Found_View(Merchandise* p);
void User_Buyer_View_More_Details_View();
void User_Buyer_View_Details_View(Merchandise* p);
void User_Buyer_Buy_Merchandise_View();
void User_Buyer_Buy_Merchandise_Sure_View(Merchandise* p);
void User_Buyer_Menu();

void User_PIM_Menu_View();
void User_Recharge_View();
void User_Information_View(User* p);
void User_PIM_Menu_View();
void User_Information_Modify_View(User* p);
void PIM();

void Admin_Login_View();
void Admin_Main_Menu_View();
void Admin_Main_Menu();

void Admin_View_All_Users_View();
void View_All_Users();
void Admin_Delete_User_View();
void Admin_Delete_User_Sure_View(User* p);
void Delete_User();
void Admin_View_All_Merchandises_View();
void View_All_Merchandises();
void Admin_Search_Merchandise_View();
void Admin_Found_Merchandise_View(Merchandise* p);
void Admin_Search_Merchandise();
void Admin_Off_Merchandise_View();
void Admin_Off_Merchandise_Sure_View(Merchandise* p);
void Off_Merchandise();
void Admin_View_All_Orders_View();
void View_All_Orders();



/******************************************************************************

								 全局变量声明

 ******************************************************************************
*       1.                x_head                      头节点指针组
*       2.                x_tail                      尾节点指针组
*       3.                x_number                    数目组-用于生成ID
******************************************************************************/
extern User* users_head;
extern Merchandise* merchandises_head;
extern Order* orders_head;

extern User* users_tail;
extern Merchandise* merchandises_tail;
extern Order* orders_tail;

extern int users_number;
extern int merchandises_number;
extern int orders_number;

extern User* Current_User;

