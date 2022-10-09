#include"General.h"

/******************************************************************************

								 ȫ�ֱ�������

 ******************************************************************************
*       1.                x_head                      ͷ�ڵ�ָ����
*       2.                x_tail                      β�ڵ�ָ����
*       3.                x_number                    ��Ŀ��-��������ID
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
 �� �� ��  : Main_Menu
 ��������  : ���˵�
 �������  : ��
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
			������					�����ļ�					����
* 1			User_Login				User_Others.cpp				�û���¼
* 2			User_Register			User_Others.cpp				�û�ע��
* 3			Admin_Login				Admin_Origin_Admin.cpp		����Ա��¼
* 4			Update					Update.cpp					���ݸ����������ļ�

 �޸���ʷ      :
  1.��    ��   : x
	��    ��   : x
	�޸�����   : x

*****************************************************************************/
void Main_Menu() {
	Main_Menu_View();
	int root_operate = 0;
	cout << ">>>���������ָ�";
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
		cout << ">>>δ�ҵ���ָ�����������...";
		Sleep(500);
		Main_Menu();
	}
}



/*****************************************************************************
 �� �� ��  : main
 ��������  : ��֯�����ļ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : 0
 ���ú���  :
			������					�����ļ�					����
* 1			Init					Init.cpp					��ʼ��
* 2			Main_Menu				Main.cpp					���˵�
* 3			Update					Update.cpp					���������ļ�
 �޸���ʷ      :
  1.��    ��   : x
	��    ��   : x
	�޸�����   : x

*****************************************************************************/
int main() {
	Init();
	Main_Menu();
	return 0;
}