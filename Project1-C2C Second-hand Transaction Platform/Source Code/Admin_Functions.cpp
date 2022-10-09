#include"General.h"

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
void View_All_Users() {
	Admin_View_All_Users_View();
	User* cursor = users_head;
	while (cursor != NULL) {
		if (cursor->exist == 1) {
			printf("%-11s %-13s %-14s %-19s %-18s %-8.lf\n", cursor->ID, cursor->name, cursor->passwd, cursor->contact, cursor->address, cursor->money);
		}
		cursor = cursor->next;
	}
	printf("******************************************************************************************\n");
	system("pause");
	Admin_Main_Menu();
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

inline void Delete_All_His_Merchandises(char delete_id[]) {
	Merchandise* cursor = merchandises_head;
	while (cursor != NULL) {
		if (strcmp(delete_id, cursor->bussiness_id) == 0) cursor->state = 2;
		cursor = cursor->next;
	}
}

inline void Return_All_Orders_Money_To_Buyers(char delete_id[]) {
	Order* orders_cursor = orders_head;
	User* users_cursor = users_head;
	while (orders_cursor != NULL) {
		if (strcmp(delete_id, orders_cursor->ID) == 0) {
			orders_cursor->exist = 0;
			while (users_cursor != NULL) {
				if (strcmp(orders_cursor->buyer_id, users_cursor->ID) == 0) {
					users_cursor->money += orders_cursor->tamount;
					//被删除用户扣钱...
				}
				users_cursor = users_head;
				users_cursor = users_cursor->next;
			}
		}
		orders_cursor = orders_cursor->next;
	}
}

void Delete_User() {
	Admin_Delete_User_View();
	printf(">>>请输入要删除的用户ID：");
	char delete_id[7];
N9:cin >> delete_id;
	User* find = users_head;
	while (find != NULL) {
		if (find->exist == 1 && strcmp(delete_id, find->ID) == 0) break;
		find = find->next;
	}
	if (find == NULL) {
		printf(">>>该用户不存在...");
		system("pause");
		Admin_Main_Menu();
	}
	else {
		Admin_Delete_User_Sure_View(find);
		string admin_operate;
		cin >> admin_operate;
		if (admin_operate == "N") {
			printf(">>>删除用户失败...");
			system("pause");
			Admin_Main_Menu();
		}
		else if (admin_operate == "Y") {
			Delete_All_His_Merchandises(delete_id);
			Return_All_Orders_Money_To_Buyers(delete_id);
			find->exist = 0;
			printf(">>>删除用户成功！正在返回管理员主菜单...");
			Users_Update();
			system("pause");
			Admin_Main_Menu();
		}
		else {
			printf(">>>未找到该指令，请重新输入...");
			goto N9;
		}
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
void View_All_Merchandises() {
	Admin_View_All_Merchandises_View();
	Merchandise* cursor = merchandises_head;
	while (cursor != NULL) {
		printf("%-9s %-21s %-12.1lf %-12s %-4d-%-2d-%-2d", cursor->ID, cursor->name, cursor->price, cursor->bussiness_id, cursor->launch_time.year, cursor->launch_time.month, cursor->launch_time.day);
		cout << "       " << cursor->state_table[cursor->state] << endl;
		cursor = cursor->next;
	}
	printf("******************************************************************************************\n");
	system("pause");
	Admin_Main_Menu();
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
void Admin_Search_Merchandise() {
	Admin_Search_Merchandise_View();
	printf(">>>请输入要查找的商品ID：");
	char target_id[7];
	cin >> target_id;
	Merchandise* find = merchandises_head;
	while (find != NULL) {
		if (strcmp(target_id, find->ID) == 0) break;
		find = find->next;
	}
	if (find == NULL) {
		printf(">>>该商品不存在...");
		system("pause");
		Admin_Main_Menu();
	}
	else {
		Admin_Found_Merchandise_View(find);
		system("pause");
		Admin_Main_Menu();
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
void Off_Merchandise() {
	Admin_Off_Merchandise_View();
	printf(">>>请输入要下架的商品ID：");
	char target_id[7];
	cin >> target_id;
	Merchandise* find = merchandises_head;
	while (find != NULL) {
		if (strcmp(find->ID, target_id) == 0) break;
		find = find->next;
	}
	if (find == NULL) {
		printf(">>>该商品不存在...");
		system("pause");
		Admin_Main_Menu();
	}
	else if(find->state == 2){
		printf(">>>该商品已下架...");
		system("pause");
		Admin_Main_Menu();
	}
	else {
		Admin_Off_Merchandise_Sure_View(find);
		string admin_operate;
	N9:cin >> admin_operate;
		if (admin_operate == "N") {
			printf(">>>商品下架失败...");
			system("pause");
			Admin_Main_Menu();
		}
		else if (admin_operate == "Y") {
			find->state = 2;
			printf(">>>商品下架成功!正在返回管理员主菜单...");
			Merchandises_Update();
			system("pause");
			Admin_Main_Menu();
		}
		else {
			printf(">>>未找到该指令，请重新输入...");//此处倘若输入中文指令会直接退出程序...
			system("pause");
			goto N9;
		}
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
void View_All_Orders() {
	Admin_View_All_Orders_View();
	system("pause");
	Admin_Main_Menu();
}