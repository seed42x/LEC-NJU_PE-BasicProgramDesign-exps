#include"General.h"

inline void View_My_Information() {
	User_Information_View(Current_User);
	system("pause");
	PIM();
}

inline void Modify_My_Information() {
N11:User_Information_Modify_View(Current_User);
	printf(">>>��������Ҫ�޸ĵ���Ϣ��ţ�");
	int modify_information;
	cin >> modify_information;
	char new_name[7]{ '\0' };
	char new_passwd[11]{ '\0' };
	char new_contact[21]{ '\0' };
	char new_address[41]{ '\0' };
	switch (modify_information) {
	case 1:
		printf(">>>�������µ��û�����");
		cin >> new_name;
		for (int i = 0; Current_User->name[i] != '\0'; i++) Current_User->name[i] = '\0';
		for (int i = 0; new_name[i] != '\0'; i++) Current_User->name[i] = new_name[i];
		printf(">>>�޸��û����ɹ���");//�޸���ҪDebug
		Users_Update();
		system("pause");
		goto N11;
		break;
	case 2:
		printf(">>>�������µ��û����룺");
		cin >> new_passwd;
		for (int i = 0; Current_User->passwd[i] != '\0'; i++) Current_User->passwd[i] = '\0';
		for (int i = 0; new_passwd[i] != '\0'; i++) Current_User->passwd[i] = new_passwd[i];
		printf(">>>�޸�����ɹ��������µ�¼...");
		Users_Update();
		system("pause");
		Main_Menu();
		break;
	case 3:
		printf(">>>�������µ��û���ϵ��ʽ��");
		cin >> new_contact;
		for (int i = 0; Current_User->contact[i] != '\0'; i++) Current_User->contact[i] = '\0';
		for (int i = 0; new_contact[i] != '\0'; i++) Current_User->contact[i] = new_contact[i];
		printf(">>>�޸���ϵ��ʽ�ɹ���");
		Users_Update();
		system("pause");
		goto N11;
		break;
	case 4:
		printf(">>>�������µĵ�ַ��");
		cin >> new_address;
		for (int i = 0; Current_User->address[i] != '\0'; i++) Current_User->address[i] = '\0';
		for (int i = 0; new_address[i] != '\0'; i++) Current_User->address[i] = new_address[i];
		printf(">>>�޸ĵ�ַ�ɹ���");
		Users_Update();
		system("pause");
		goto N11;
		break;
	default:
		printf(">>>δ�ҵ���ָ��...");
		system("pause");
		PIM();
		break;
	}
}

inline void Recharge() {
	User_Recharge_View();
	printf(">>>������Ҫ��ֵ�Ľ�");
	int recharge_money;
	cin >> recharge_money;
	if (recharge_money >= 0) {
		Current_User->money += recharge_money;
		printf(">>>��ֵ�ɹ���");
		Users_Update();
	}
	else {
		printf(">>>��ֵʧ�ܣ�...");
	}
	system("pause");
	PIM();
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
void PIM() {
	User_PIM_Menu_View();
	int user_operate = 0;
	cout << ">>>���������ָ�";
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
		cout << ">>>δ�ҵ���ָ�����������...";
		Sleep(500);
		User_Main_Menu();
	}
}