#include"General.h"

inline void View_My_Information() {
	User_Information_View(Current_User);
	system("pause");
	PIM();
}

inline void Modify_My_Information() {
N11:User_Information_Modify_View(Current_User);
	printf(">>>请输入需要修改的信息序号：");
	int modify_information;
	cin >> modify_information;
	char new_name[7]{ '\0' };
	char new_passwd[11]{ '\0' };
	char new_contact[21]{ '\0' };
	char new_address[41]{ '\0' };
	switch (modify_information) {
	case 1:
		printf(">>>请输入新的用户名：");
		cin >> new_name;
		for (int i = 0; Current_User->name[i] != '\0'; i++) Current_User->name[i] = '\0';
		for (int i = 0; new_name[i] != '\0'; i++) Current_User->name[i] = new_name[i];
		printf(">>>修改用户名成功！");//修改需要Debug
		Users_Update();
		system("pause");
		goto N11;
		break;
	case 2:
		printf(">>>请输入新的用户密码：");
		cin >> new_passwd;
		for (int i = 0; Current_User->passwd[i] != '\0'; i++) Current_User->passwd[i] = '\0';
		for (int i = 0; new_passwd[i] != '\0'; i++) Current_User->passwd[i] = new_passwd[i];
		printf(">>>修改密码成功！请重新登录...");
		Users_Update();
		system("pause");
		Main_Menu();
		break;
	case 3:
		printf(">>>请输入新的用户联系方式：");
		cin >> new_contact;
		for (int i = 0; Current_User->contact[i] != '\0'; i++) Current_User->contact[i] = '\0';
		for (int i = 0; new_contact[i] != '\0'; i++) Current_User->contact[i] = new_contact[i];
		printf(">>>修改联系方式成功！");
		Users_Update();
		system("pause");
		goto N11;
		break;
	case 4:
		printf(">>>请输入新的地址：");
		cin >> new_address;
		for (int i = 0; Current_User->address[i] != '\0'; i++) Current_User->address[i] = '\0';
		for (int i = 0; new_address[i] != '\0'; i++) Current_User->address[i] = new_address[i];
		printf(">>>修改地址成功！");
		Users_Update();
		system("pause");
		goto N11;
		break;
	default:
		printf(">>>未找到该指令...");
		system("pause");
		PIM();
		break;
	}
}

inline void Recharge() {
	User_Recharge_View();
	printf(">>>请输入要充值的金额：");
	int recharge_money;
	cin >> recharge_money;
	if (recharge_money >= 0) {
		Current_User->money += recharge_money;
		printf(">>>充值成功！");
		Users_Update();
	}
	else {
		printf(">>>充值失败！...");
	}
	system("pause");
	PIM();
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
void PIM() {
	User_PIM_Menu_View();
	int user_operate = 0;
	cout << ">>>请输入操作指令：";
	cin >> user_operate;
	switch (user_operate) {
	case 1:
		View_My_Information();
		break;
	case 2:
		Modify_My_Information();
		break;
	case 3:
		Recharge();
		break;
	case 4:
		User_Main_Menu();
		break;
	default:
		cout << ">>>未找到该指令，请重新输入...";
		Sleep(500);
		User_Main_Menu();
	}
}