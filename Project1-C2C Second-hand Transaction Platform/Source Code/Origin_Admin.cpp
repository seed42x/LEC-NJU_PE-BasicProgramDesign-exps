#include"General.h"


/*****************************************************************************
 �� �� ��  : Admin_Main_Menu
 ��������  : ����Ա�˵�
 �������  : ��
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
			������							�����ļ�					����
* 1			View_All_Users					Admin_Functions.cpp			�鿴�����û�
* 2			Delete_User						Admin_Functions.cpp			ɾ���û�
* 3			View_All_Merchandise			Admin_Functions.cpp			�鿴������Ʒ
* 4			Admin_Search_Merchandise		Admin_Functions.cpp			������Ʒ
* 5			Off_Merchandise					Admin_Functions.cpp			�¼���Ʒ
* 6			View_All_Orders					Admin_Functions.cpp			�鿴���ж���
 �޸���ʷ      :
  1.��    ��   : x
	��    ��   : x
	�޸�����   : x

*****************************************************************************/
void Admin_Main_Menu() {
	Admin_Main_Menu_View();
	int admin_operate = 0;
	cout << ">>>���������ָ�";
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
		cout << ">>>�����˳���¼...";
		Sleep(500);
		Main_Menu();
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
void Admin_Login() {
	Admin_Login_View();
	printf(">>>���������Ա���ƣ�");
	string buffer;
	cin >> buffer;
	if (buffer == "1") {
		printf(">>>���������룺");
		string admin_passwd;
		cin >> admin_passwd;
		if (admin_passwd == "1") {
			printf(">>>��¼�ɹ���");
			system("pause");
			Admin_Main_Menu();
		}
		else {
			printf(">>>�������");
			Main_Menu();
		}
	}
	else {
		printf(">>>����Ա���ƴ���");
		system("pause");
		Main_Menu();
	}
}