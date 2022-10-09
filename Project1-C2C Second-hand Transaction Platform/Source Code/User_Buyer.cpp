#include"General.h"

inline void User_Search_Merchandise() {
	User_Buyer_Search_Merchandise_View();
	printf(">>>������Ҫ���ҵ���ƷID��");
	char target_id[7];
	cin >> target_id;
	Merchandise* find = merchandises_head;
	while (find != NULL) {
		if (strcmp(target_id, find->ID) == 0 && find->state != 2) break;
		find = find->next;
	}
	if (find == NULL) {
		printf(">>>����Ʒ������...");
		system("pause");
		User_Buyer_Menu();
	}
	else {
		User_Buyer_Found_View(find);
		system("pause");
		User_Buyer_Menu();
	}
}

inline void View_Merchandises_List() {
	Admin_View_All_Merchandises_View();
	Merchandise* cursor = merchandises_head;
	while (cursor != NULL) {
		if (cursor->state != 2) {
			printf("%-9s %-21s %-12.1lf %-12s %-4d-%-2d-%-2d", cursor->ID, cursor->name, cursor->price, cursor->bussiness_id, cursor->launch_time.year, cursor->launch_time.month, cursor->launch_time.day);
			cout << "       " << cursor->state_table[cursor->state] << endl;
		}
		cursor = cursor->next;
	}
	printf("******************************************************************************************\n");
	system("pause");
	User_Buyer_Menu();
}

inline void View_More_Details() {
	User_Buyer_View_More_Details_View();
	printf(">>>������Ҫ�鿴����ƷID��");
	char target_id[7];
	cin >> target_id;
	Merchandise* find = merchandises_head;
	while (find != NULL) {
		if (strcmp(target_id, find->ID) == 0 && find->state != 2) break;
		find = find->next;
	}
	if (find == NULL) {
		printf(">>>����Ʒ������...");
		system("pause");
		User_Buyer_Menu();
	}
	else {
		User_Buyer_View_Details_View(find);
		system("pause");
		User_Buyer_Menu();
	}
}


inline void Get_Order_ID(Order* p) {
	int len = 0;
	int number = orders_number;
	while (number != 0) {
		len++;
		number /= 10;
	}
	number = orders_number;
	for (int i = 6 - len; len > 0;) {
		p->ID[i] = char((number % 10) + 48);
		number = number / 10;
		len--;
	}
}

inline void Get_Order_Time(Order* p) {
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	p->time.year = sys.wYear;
	p->time.month = sys.wMonth;
	p->time.day = sys.wDay;
}

inline void Creat_Order(Order* p, Merchandise* find) {
	Get_Order_ID(p);
	for (int i = 0; find->ID[i] != '\0'; i++) p->mer_id[i] = find->ID[i];
	p->tamount = find->price;
	Get_Order_Time(p);
	for (int i = 0; find->bussiness_id[i] != '\0'; i++) p->seller_id[i] = find->bussiness_id[i];
	for (int i = 0; Current_User->ID[i] != '\0'; i++) p->buyer_id[i] = Current_User->ID[i];
	if (orders_head == NULL) {
		orders_head = p;
		orders_tail = p;
	}
	else {
		orders_tail->next = p;
		orders_tail = p;
	}
	orders_number++;
}

inline void Buy_Merchandise() {
	User_Buyer_Buy_Merchandise_View();
	printf(">>>������Ҫ�������ƷID��");
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
		User_Buyer_Menu();
	}
	else if (find->state == 2) {
		printf(">>>����Ʒ���¼�...");
		system("pause");
		User_Buyer_Menu();
	}
	else {
		User_Buyer_Buy_Merchandise_Sure_View(find);
		string buyer_operate;
	N10:cin >> buyer_operate;
		if (buyer_operate == "N") {
			printf(">>>������ֹ...");
			system("pause");
			User_Buyer_Menu();
		}
		else if (buyer_operate == "Y") {
			if (Current_User->money >= find->price) {
				Current_User->money -= find->price;
				User* cursor = users_head;
				while (cursor != NULL) {
					if (strcmp(cursor->ID, find->bussiness_id) == 0) break;
					cursor = cursor->next;
				}
				cursor->money += find->price;
				find->state = 1;
				Order* p = new Order;
				Creat_Order(p, find);
				Merchandises_Update();
				printf(">>>����ɹ������ڷ���������˵�...");
				system("pause");
				User_Buyer_Menu();
			}
			else {
				printf(">>>���㣬���ֵ����й���...");
				system("pause");
				User_Buyer_Menu();
			}
		}
		else {
			printf(">>>δ�ҵ���ָ�����������...");
			system("pause");
			goto N10;
		}
	}
	Merchandises_Update();
}

inline void Buyer_View_Orders() {
	User_Buyer_View_All_Orders_View();
	system("pause");
	User_Buyer_Menu();
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
void User_Buyer_Menu() {
	User_Buyer_Menu_View();
	int user_operate = 0;
	cout << ">>>���������ָ�";
	cin >> user_operate;
	switch (user_operate) {
	case 1:
		User_Search_Merchandise();
		break;
	case 2:
		View_Merchandises_List();
		break;
	case 3:
		View_More_Details();
		break;
	case 4:
		Buy_Merchandise();
		break;
	case 5:
		Buyer_View_Orders();
		break;
	case 6:
		User_Main_Menu();
		break;
	default:
		cout << ">>>δ�ҵ���ָ�����������...";
		Sleep(500);
		User_Buyer_Menu();
	}
}