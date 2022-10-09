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
void Admin_Login_View() {
	system("cls");
	printf("******************************************************************************************\n");
	printf("                                   ��  ��  Ա  ��  ¼\n");
	printf("******************************************************************************************\n");
}

void Admin_Main_Menu_View() {
	system("cls");
	printf("******************************************************************************************\n");
	printf("                              ��   ��   Ա   ��   ��   ��\n");
	printf("******************************************************************************************\n");
	printf("1.�鿴�����û�  2.ɾ���û�  3.�鿴������Ʒ  4.������Ʒ  5.�¼���Ʒ  6.�鿴���ж���  7.ע��\n");
	printf("******************************************************************************************\n");
}

void Admin_View_All_Users_View() {
	system("cls");
	printf("******************************************************************************************\n");
	printf("                               ��     ��     ��     ��\n");
	printf("******************************************************************************************\n");
	printf("ID          ����          ����           ��ϵ��ʽ            ��ַ               ���      \n");
	printf("******************************************************************************************\n");
}

void Admin_Delete_User_View() {
	system("cls");
	printf("******************************************************************************************\n");
	printf("                                   ��    ��    ɾ    ��    \n");
	printf("******************************************************************************************\n");
}

void Admin_Delete_User_Sure_View(User* p) {
	printf("******************************************************************************************\n");
	printf("                             ɾ    ��    ��    ��    ȷ    ��    \n");
	printf("******************************************************************************************\n");
	printf("ID:	        %-7s\n", p->ID);
	printf("�û�����	%-21s\n", p->name);
	printf("���룺		%-11s\n", p->passwd);
	printf("��ϵ��ʽ:	%-21s\n", p->contact);
	printf("��ַ:		%-41s\n", p->address);
	printf("��		%-7.1lf\n", p->money);
	printf("*****************************�Ƿ����������Ϣɾ�����û���(Y/N)****************************\n");
}

void Admin_View_All_Merchandises_View() {
	system("cls");
	printf("******************************************************************************************\n");
	printf("                               ��     ��     ��     Ʒ\n");
	printf("******************************************************************************************\n");
	printf("ID        ����                  �۸�         ����ID       �ϼ�ʱ��         ״̬    \n");
	printf("******************************************************************************************\n");
}

void Admin_Search_Merchandise_View() {
	system("cls");
	printf("******************************************************************************************\n");
	printf("                               ��    ��     ��     Ʒ\n");
	printf("******************************************************************************************\n");
}

void Admin_Found_Merchandise_View(Merchandise* p) {
	system("pause");
	printf("******************************************************************************************\n");
	printf("                                     ���ҵ�������Ʒ\n");
	printf("******************************************************************************************\n");
	printf("ID:	        %s\n", p->ID);
	printf("���ƣ�		%s\n", p->name);
	printf("�۸�		%.1lf\n", p->price);
	printf("������		%s\n", p->discribe);
	printf("����ID:		%s\n", p->bussiness_id);
	printf("�ϼ�ʱ�䣺	%d-%d-%d\n", p->launch_time.year, p->launch_time.month, p->launch_time.day);
	cout << "��Ʒ״̬��	" << p->state_table[p->state] << endl;
	printf("******************************************************************************************\n");
}

void Admin_Off_Merchandise_View() {
	system("cls");
	printf("******************************************************************************************\n");
	printf("                               ��    ��     ��     Ʒ\n");
	printf("******************************************************************************************\n");
}

void Admin_Off_Merchandise_Sure_View(Merchandise* p) {
	printf("***********************************************************************************\n");
	printf("                                ���ҵ���Ʒ����\n");
	printf("***********************************************************************************\n");
	printf("ID:	        %s\n", p->ID);
	printf("���ƣ�		%s\n", p->name);
	printf("�۸�		%.1lf\n", p->price);
	printf("������		%s\n", p->discribe);
	printf("����ID:		%s\n", p->bussiness_id);
	printf("�ϼ�ʱ�䣺	%d-%d-%d\n", p->launch_time.year, p->launch_time.month, p->launch_time.day);
	cout << "��Ʒ״̬��	" << p->state_table[p->state] << endl;
	printf("*****************************�Ƿ����������Ϣ�¼���Ʒ��(Y/N)**********************\n");
}

void Admin_View_All_Orders_View() {
	string state_table[2]{ "����", "��ɾ��" };
	system("cls");
	printf("***********************************************************************************\n");
	printf("                       ��       ��       ��       ��\n");
	printf("***********************************************************************************\n");
	printf("ID       ��ƷID       ���׽��       ����ʱ��       ����ID       ���ID      ״̬  \n");
	printf("***********************************************************************************\n");
	Order* cursor = orders_head;
	while (cursor != NULL) {
		printf("%-18s %-10s %-10.1lf %d-%d-%d %-10s %-9s ", cursor->ID, cursor->mer_id, cursor->tamount, cursor->time.year, cursor->time.month, cursor->time.day, cursor->seller_id, cursor->buyer_id);
		cout << state_table[cursor->exist] << endl;
		cursor = cursor->next;
	}
	printf("***********************************************************************************\n");
}