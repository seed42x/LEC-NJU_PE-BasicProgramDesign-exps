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
inline void Get_Product_ID(Merchandise* p) {
	int len = 0;
	int number = merchandises_number;
	while (number != 0) {
		len++;
		number /= 10;
	}
	number = merchandises_number;
	for (int i = 6 - len; len > 0;) {
		p->ID[i] = char((number % 10) + 48);
		number = number / 10;
		len--;
	}
}
inline void Get_Product_Name(Merchandise* p) {
	string buffer;
	printf(">>>�������ϼ���Ʒ����(���Ȳ�����10����ֻ��ʹ�����ĺ��ֻ�Ӣ����ĸ)��");
	cin >> buffer;
	if (buffer.length() > 21) {
		printf(">>>���ȳ�������...");
		system("pause");
		User_Seller_Menu();
	}
	for (int i = 0; buffer[i] != '\0'; i++) {
		p->name[i] = buffer[i];
	}
}
inline void Get_Product_Price(Merchandise* p) {
	double price;
	printf(">>>�������ϼ���Ʒ�۸�:");
	cin >> price;
	p->price = price;
}
inline void Get_Product_Discribe(Merchandise* p) {
	string buffer;
	printf(">>>��������Ʒ������");
	string str = "\n";
	getline(cin, str);
	getline(cin, buffer);
	if (buffer.length() > 201) {
		printf(">>>���ȳ�������...");
		system("pause");
		User_Seller_Menu();
	}
	for (int i = 0; buffer[i] != '\0'; i++) {
		p->discribe[i] = buffer[i];
	}
}
inline void Get_Product_Launch_Time(Merchandise* p) {
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	p->launch_time.year = sys.wYear;
	p->launch_time.month = sys.wMonth;
	p->launch_time.day = sys.wDay;
}

inline void Release_Product() {
	User_Seller_Release_Product_View();
	Merchandise* p = new Merchandise;
	Get_Product_ID(p);
	Get_Product_Name(p);
	Get_Product_Price(p);
	Get_Product_Discribe(p);
	for (int i = 0; Current_User->ID[i] != '\0'; i++) p->bussiness_id[i] = Current_User->ID[i];
	Get_Product_Launch_Time(p);
	User_Seller_Release_Product_Sure_View(p);
	string seller_operate;
N2:cin >> seller_operate;
	if (seller_operate == "N") {
		delete p;
		printf(">>>��Ʒ�ϼ�ʧ�ܣ����������������˵�...");
		system("pause");
		User_Seller_Menu();
	}
	else if (seller_operate == "Y") {
		if (merchandises_head == NULL) {
			merchandises_head = p;
			merchandises_tail = p;
		}
		else {
			merchandises_tail->next = p;
			merchandises_tail = p;
		}
		merchandises_number++;
		printf(">>>��Ʒ�ϼܳɹ������������������˵�...");
		system("pause");
		User_Seller_Menu();
	}
	else {
		printf(">>>δ�ҵ���ָ�����������...");
		system("pause");
		goto N2;
	}
}

inline void View_My_Products() {
	User_Seller_My_Products_View();
	system("pause");
	User_Seller_Menu();
}

inline void Modify_Product() {
	User_Seller_Modify_Product_View();
	printf(">>>������Ҫ�޸ĵ���ƷID:");
	char modify_id[7];
	cin >> modify_id;
	Merchandise* find = merchandises_head;
	while (find != NULL) {
		if (strcmp(find->ID, modify_id) == 0 && strcmp(find->bussiness_id, Current_User->ID) == 0 && find->state != 2) break;
		find = find->next;
	}
	if (find == NULL) {
		printf(">>>δ�ҵ�����Ʒ...");
		system("pause");
		User_Seller_Menu();
	}
	else {
		printf(">>>���ҵ�����Ʒ...");
		system("pause");
	N4:User_Seller_Modify_Product_Tails(find);
		string seller_operate;
		cin >> seller_operate;
		if (seller_operate == "N") {
			printf(">>>�޸���Ʒʧ�ܣ������˳�...");
			system("pause");
			User_Seller_Menu();
		}
		else if (seller_operate == "Y") {
			printf(">>>��������Ҫ�޸ĵ���Ϣ��ţ�");
			int modify_number;
			cin >> modify_number;
			string buffer;
			double price_buffer;
			switch (modify_number) {
			case 1:
			N5:printf(">>>�������µ���Ʒ���ƣ�");
				cin >> buffer;
				if (buffer.length() > 21) {
					printf(">>>���ȳ�������...");
					system("pause");
					goto N5;
				}
				for (int i = 0; find->name[i] != '\0'; i++) find->name[i] = '\0';
				for (int i = 0; buffer[i] != '\0'; i++) {
					find->name[i] = buffer[i];
				}
				printf(">>>��Ʒ�����޸ĳɹ���...");
				Sleep(500);
				goto N4;
				break;
			case 2:
				printf(">>>�������µ���Ʒ�۸�");
				cin >> price_buffer;
				find->price = price_buffer;
				printf(">>>��Ʒ�۸��޸ĳɹ���...");
				Sleep(500);
				goto N4;
				break;
			case 3:
			N6: printf(">>>�������µ���Ʒ������");
				cin >> buffer;
				if (buffer.length() > 201) {
					printf(">>>���ȳ�������...");
					system("pause");
					goto N6;
				}
				for (int i = 0; find->discribe[i] != '\0'; i++) find->discribe[i] = '\0';
				for (int i = 0; buffer[i] != '\0'; i++) find->discribe[i] = buffer[i];
				printf("��Ʒ�����޸ĳɹ�!...");
				Sleep(500);
				goto N4;
				break;
			case 4:
			N7:printf(">>>�������µ���Ʒ״̬(������/���۳�/���¼�)��");
				cin >> buffer;
				if (buffer == "������") find->state = 0;
				else if (buffer == "���۳�") find->state = 1;
				else if (buffer == "���¼�") find->state = 2;
				else {
					printf(">>>�޸�״̬,����������...");
					system("pause");
					goto N7;
				}
				goto N4;
				break;
			default:
				printf(">>>δ�ҵ���ָ�����������...");//�˴�������������ָ���ֱ���˳�����...
				system("pause");
				goto N4;
			};
		}
	}
}

inline void Off_Product() {
	User_Seller_Off_Product_View();
	printf(">>>������Ҫ�¼ܵ���ƷID:");
	char off_product[7];
	cin >> off_product;
	Merchandise* find = merchandises_head;
	while (find != NULL) {
		if (strcmp(find->ID, off_product) == 0 && strcmp(find->bussiness_id, Current_User->ID) == 0 && find->state != 2) break;
		find = find->next;
	}
	if (find == NULL) {
		printf(">>>δ�ҵ�����Ʒ...");
		system("pause");
		User_Seller_Menu();
	}
	else {
		User_Seller_Off_Product_Sure_View(find);
		string user_operate;
	N8:cin >> user_operate;
		if (user_operate == "N") {
			printf(">>>��Ʒ�¼�ʧ��...");
			system("pause");
			User_Seller_Menu();
		}
		else if (user_operate == "Y") {
			find->state = 2;
			printf(">>>��Ʒ�¼ܳɹ�!���ڷ������Ҳ˵�...");
			Merchandises_Update();
			system("pause");
			User_Seller_Menu();
		}
		else {
			printf(">>>δ�ҵ���ָ�����������...");//�˴�������������ָ���ֱ���˳�����...
			system("pause");
			goto N8;
		}
	}
}

inline void Seller_View_Orders() {
	User_Seller_View_All_Orders_View();
	system("pause");
	User_Seller_Menu();
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
void User_Seller_Menu() {
	User_Seller_Menu_View();
	int user_operate = 0;
	cout << ">>>���������ָ�";
	cin >> user_operate;
	switch (user_operate) {
	case 1:
		Release_Product();
		break;
	case 2:
		View_My_Products();
		break;
	case 3:
		Modify_Product();
		break;
	case 4:
		Off_Product();
		break;
	case 5:
		Seller_View_Orders();
		break;
	case 6:
		User_Main_Menu();
		break;
	default:
		cout << ">>>δ�ҵ���ָ�����������...";
		Sleep(500);
		User_Seller_Menu();
	}
}