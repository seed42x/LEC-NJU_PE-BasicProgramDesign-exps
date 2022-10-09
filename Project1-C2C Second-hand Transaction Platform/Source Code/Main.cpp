#include"General.h"

/******************************************************************************

								 全局变量定义

 ******************************************************************************
*       1.                x_head                      头节点指针组
*       2.                x_tail                      尾节点指针组
*       3.                x_number                    数目组-用于生成ID
******************************************************************************/
User* users_head = NULL;
Merchandise* merchandises_head = NULL;
Order* orders_head = NULL;
User* users_tail = NULL;
Merchandise* merchandises_tail = NULL;
Order* orders_tail = NULL;
int users_number = 1;
int merchandises_number = 1;
int orders_number = 1;
User* Current_User;

/*****************************************************************************
 函 数 名  : Main_Menu
 功能描述  : 主菜单
 输入参数  : 无
 输出参数  : 无
 返 回 值  : void
 调用函数  :
			函数名					所在文件					功能
* 1			User_Login				User_Others.cpp				用户登录
* 2			User_Register			User_Others.cpp				用户注册
* 3			Admin_Login				Admin_Origin_Admin.cpp		管理员登录
* 4			Update					Update.cpp					数据更新至数据文件

 修改历史      :
  1.日    期   : x
	作    者   : x
	修改内容   : x

*****************************************************************************/
void Main_Menu() {
	Main_Menu_View();
	int root_operate = 0;
	cout << ">>>请输入操作指令：";
	cin >> root_operate;
	switch (root_operate) {
	case 1:
		User_Login();
		break;
	case 2:
		User_Register();
		break;
	case 3:
		Admin_Login();
		break;
	case 4:
		Update();
		exit(1);
		break;
	default:
		cout << ">>>未找到该指令，请重新输入...";
		Sleep(500);
		Main_Menu();
	}
}



/*****************************************************************************
 函 数 名  : main
 功能描述  : 组织所有文件运行
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 0
 调用函数  :
			函数名					所在文件					功能
* 1			Init					Init.cpp					初始化
* 2			Main_Menu				Main.cpp					主菜单
* 3			Update					Update.cpp					更新数据文件
 修改历史      :
  1.日    期   : x
	作    者   : x
	修改内容   : x

*****************************************************************************/
int main() {
	Init();
	Main_Menu();
	return 0;
}