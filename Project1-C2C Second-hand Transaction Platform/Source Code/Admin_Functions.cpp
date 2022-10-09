#include"General.h"

/*****************************************************************************
 �� �� ��  : 
 ��������  : 
 �������  : ��
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
			������					�����ļ�					����
* 1
 �޸���ʷ      :
  1.��    ��   : x
	��    ��   : x
	�޸�����   : x

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
 �� �� ��  :
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
			������					�����ļ�					����
* 1
 �޸���ʷ      :
  1.��    ��   : x
	��    ��   : x
	�޸�����   : x

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
					//��ɾ���û���Ǯ...
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
	printf(">>>������Ҫɾ�����û�ID��");
	char delete_id[7];
N9:cin >> delete_id;
	User* find = users_head;
	while (find != NULL) {
		if (find->exist == 1 && strcmp(delete_id, find->ID) == 0) break;
		find = find->next;
	}
	if (find == NULL) {
		printf(">>>���û�������...");
		system("pause");
		Admin_Main_Menu();
	}
	else {
		Admin_Delete_User_Sure_View(find);
		string admin_operate;
		cin >> admin_operate;
		if (admin_operate == "N") {
			printf(">>>ɾ���û�ʧ��...");
			system("pause");
			Admin_Main_Menu();
		}
		else if (admin_operate == "Y") {
			Delete_All_His_Merchandises(delete_id);
			Return_All_Orders_Money_To_Buyers(delete_id);
			find->exist = 0;
			printf(">>>ɾ���û��ɹ������ڷ��ع���Ա���˵�...");
			Users_Update();
			system("pause");
			Admin_Main_Menu();
		}
		else {
			printf(">>>δ�ҵ���ָ�����������...");
			goto N9;
		}
	}
}



/*****************************************************************************
 �� �� ��  :
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
			������					�����ļ�					����
* 1
 �޸���ʷ      :
  1.��    ��   : x
	��    ��   : x
	�޸�����   : x

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
 �� �� ��  :
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
			������					�����ļ�					����
* 1
 �޸���ʷ      :
  1.��    ��   : x
	��    ��   : x
	�޸�����   : x

*****************************************************************************/
void Admin_Search_Merchandise() {
	Admin_Search_Merchandise_View();
	printf(">>>������Ҫ���ҵ���ƷID��");
	char target_id[7];
	cin >> target_id;
	Merchandise* find = merchandises_head;
	while (find != NULL) {
		if (strcmp(target_id, find->ID) == 0) break;
		find = find->next;
	}
	if (find == NULL) {
		printf(">>>����Ʒ������...");
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
 �� �� ��  :
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
			������					�����ļ�					����
* 1
 �޸���ʷ      :
  1.��    ��   : x
	��    ��   : x
	�޸�����   : x

*****************************************************************************/
void Off_Merchandise() {
	Admin_Off_Merchandise_View();
	printf(">>>������Ҫ�¼ܵ���ƷID��");
	char target_id[7];
	cin >> target_id;
	Merchandise* find = merchandises_head;
	while (find != NULL) {
		if (strcmp(find->ID, target_id) == 0) break;
		find = find->next;
	}
	if (find == NULL) {
		printf(">>>����Ʒ������...");
		system("pause");
		Admin_Main_Menu();
	}
	else if(find->state == 2){
		printf(">>>����Ʒ���¼�...");
		system("pause");
		Admin_Main_Menu();
	}
	else {
		Admin_Off_Merchandise_Sure_View(find);
		string admin_operate;
	N9:cin >> admin_operate;
		if (admin_operate == "N") {
			printf(">>>��Ʒ�¼�ʧ��...");
			system("pause");
			Admin_Main_Menu();
		}
		else if (admin_operate == "Y") {
			find->state = 2;
			printf(">>>��Ʒ�¼ܳɹ�!���ڷ��ع���Ա���˵�...");
			Merchandises_Update();
			system("pause");
			Admin_Main_Menu();
		}
		else {
			printf(">>>δ�ҵ���ָ�����������...");//�˴�������������ָ���ֱ���˳�����...
			system("pause");
			goto N9;
		}
	}
}




/*****************************************************************************
 �� �� ��  :
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
			������					�����ļ�					����
* 1
 �޸���ʷ      :
  1.��    ��   : x
	��    ��   : x
	�޸�����   : x

*****************************************************************************/
void View_All_Orders() {
	Admin_View_All_Orders_View();
	system("pause");
	Admin_Main_Menu();
}