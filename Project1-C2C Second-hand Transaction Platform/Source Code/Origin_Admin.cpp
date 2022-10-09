#include"General.h"


/*****************************************************************************
 函 数 名  : Admin_Main_Menu
 功能描述  : 管理员菜单
 输入参数  : 无
 输出参数  : 无
 返 回 值  : void
 调用函数  :
			函数名							所在文件					功能
* 1			View_All_Users					Admin_Functions.cpp			查看所有用户
* 2			Delete_User						Admin_Functions.cpp			删除用户
* 3			View_All_Merchandise			Admin_Functions.cpp			查看所有商品
* 4			Admin_Search_Merchandise		Admin_Functions.cpp			搜索商品
* 5			Off_Merchandise					Admin_Functions.cpp			下架商品
* 6			View_All_Orders					Admin_Functions.cpp			查看所有订单
 修改历史      :
  1.日    期   : x
	作    者   : x
	修改内容   : x

*****************************************************************************/
void Admin_Main_Menu() {
	Admin_Main_Menu_View();
	int admin_operate = 0;
	cout << ">>>请输入操作指令：";
	cin >> admin_operate;
	switch (admin_operate) {
	case 1:
		View_All_Users();
		break;
	case 2:
		Delete_User();
		break;
	case 3:
		View_All_Merchandises();
		break;
	case 4:
		Admin_Search_Merchandise();
	case 5:
		Off_Merchandise();
	case 6:
		View_All_Orders();
		break;
	case 7:
		cout << ">>>正在退出登录...";
		Sleep(500);
		Main_Menu();
	}
}



/*****************************************************************************
 函 数 名  :
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  : void
 调用函数  :
			函数名					所在文件					功能
* 1
 修改历史      :
  1.日    期   : x
	作    者   : x
	修改内容   : x

*****************************************************************************/
void Admin_Login() {
	Admin_Login_View();
	printf(">>>请输入管理员名称：");
	string buffer;
	cin >> buffer;
	if (buffer == "1") {
		printf(">>>请输入密码：");
		string admin_passwd;
		cin >> admin_passwd;
		if (admin_passwd == "1") {
			printf(">>>登录成功！");
			system("pause");
			Admin_Main_Menu();
		}
		else {
			printf(">>>密码错误！");
			Main_Menu();
		}
	}
	else {
		printf(">>>管理员名称错误！");
		system("pause");
		Main_Menu();
	}
}