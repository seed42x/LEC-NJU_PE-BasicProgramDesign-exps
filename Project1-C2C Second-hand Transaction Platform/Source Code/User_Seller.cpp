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
	printf(">>>请输入上架商品名称(长度不超过10，且只能使用中文汉字或英文字母)：");
	cin >> buffer;
	if (buffer.length() > 21) {
		printf(">>>长度超出限制...");
		system("pause");
		User_Seller_Menu();
	}
	for (int i = 0; buffer[i] != '\0'; i++) {
		p->name[i] = buffer[i];
	}
}
inline void Get_Product_Price(Merchandise* p) {
	double price;
	printf(">>>请输入上架商品价格:");
	cin >> price;
	p->price = price;
}
inline void Get_Product_Discribe(Merchandise* p) {
	string buffer;
	printf(">>>请输入商品描述：");
	string str = "\n";
	getline(cin, str);
	getline(cin, buffer);
	if (buffer.length() > 201) {
		printf(">>>长度超出限制...");
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
		printf(">>>商品上架失败，即将返回卖家主菜单...");
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
		printf(">>>商品上架成功，即将返回卖家主菜单...");
		system("pause");
		User_Seller_Menu();
	}
	else {
		printf(">>>未找到该指令，请重新输入...");
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
	printf(">>>请输入要修改的商品ID:");
	char modify_id[7];
	cin >> modify_id;
	Merchandise* find = merchandises_head;
	while (find != NULL) {
		if (strcmp(find->ID, modify_id) == 0 && strcmp(find->bussiness_id, Current_User->ID) == 0 && find->state != 2) break;
		find = find->next;
	}
	if (find == NULL) {
		printf(">>>未找到该商品...");
		system("pause");
		User_Seller_Menu();
	}
	else {
		printf(">>>已找到该商品...");
		system("pause");
	N4:User_Seller_Modify_Product_Tails(find);
		string seller_operate;
		cin >> seller_operate;
		if (seller_operate == "N") {
			printf(">>>修改商品失败，正在退出...");
			system("pause");
			User_Seller_Menu();
		}
		else if (seller_operate == "Y") {
			printf(">>>请输入需要修改的信息序号：");
			int modify_number;
			cin >> modify_number;
			string buffer;
			double price_buffer;
			switch (modify_number) {
			case 1:
			N5:printf(">>>请输入新的商品名称：");
				cin >> buffer;
				if (buffer.length() > 21) {
					printf(">>>长度超出限制...");
					system("pause");
					goto N5;
				}
				for (int i = 0; find->name[i] != '\0'; i++) find->name[i] = '\0';
				for (int i = 0; buffer[i] != '\0'; i++) {
					find->name[i] = buffer[i];
				}
				printf(">>>商品名称修改成功！...");
				Sleep(500);
				goto N4;
				break;
			case 2:
				printf(">>>请输入新的商品价格：");
				cin >> price_buffer;
				find->price = price_buffer;
				printf(">>>商品价格修改成功！...");
				Sleep(500);
				goto N4;
				break;
			case 3:
			N6: printf(">>>请输入新的商品描述：");
				cin >> buffer;
				if (buffer.length() > 201) {
					printf(">>>长度超出限制...");
					system("pause");
					goto N6;
				}
				for (int i = 0; find->discribe[i] != '\0'; i++) find->discribe[i] = '\0';
				for (int i = 0; buffer[i] != '\0'; i++) find->discribe[i] = buffer[i];
				printf("商品描述修改成功!...");
				Sleep(500);
				goto N4;
				break;
			case 4:
			N7:printf(">>>请输入新的商品状态(销售中/已售出/已下架)：");
				cin >> buffer;
				if (buffer == "销售中") find->state = 0;
				else if (buffer == "已售出") find->state = 1;
				else if (buffer == "已下架") find->state = 2;
				else {
					printf(">>>无该状态,请重新输入...");
					system("pause");
					goto N7;
				}
				goto N4;
				break;
			default:
				printf(">>>未找到该指令，请重新输入...");//此处倘若输入中文指令会直接退出程序...
				system("pause");
				goto N4;
			};
		}
	}
}

inline void Off_Product() {
	User_Seller_Off_Product_View();
	printf(">>>请输入要下架的商品ID:");
	char off_product[7];
	cin >> off_product;
	Merchandise* find = merchandises_head;
	while (find != NULL) {
		if (strcmp(find->ID, off_product) == 0 && strcmp(find->bussiness_id, Current_User->ID) == 0 && find->state != 2) break;
		find = find->next;
	}
	if (find == NULL) {
		printf(">>>未找到该商品...");
		system("pause");
		User_Seller_Menu();
	}
	else {
		User_Seller_Off_Product_Sure_View(find);
		string user_operate;
	N8:cin >> user_operate;
		if (user_operate == "N") {
			printf(">>>商品下架失败...");
			system("pause");
			User_Seller_Menu();
		}
		else if (user_operate == "Y") {
			find->state = 2;
			printf(">>>商品下架成功!正在返回卖家菜单...");
			Merchandises_Update();
			system("pause");
			User_Seller_Menu();
		}
		else {
			printf(">>>未找到该指令，请重新输入...");//此处倘若输入中文指令会直接退出程序...
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
void User_Seller_Menu() {
	User_Seller_Menu_View();
	int user_operate = 0;
	cout << ">>>请输入操作指令：";
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
		cout << ">>>未找到该指令，请重新输入...";
		Sleep(500);
		User_Seller_Menu();
	}
}