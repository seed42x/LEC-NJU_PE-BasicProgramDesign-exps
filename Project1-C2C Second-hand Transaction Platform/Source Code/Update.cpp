#include"General.h"

void Users_Update() {
	FILE* f = fopen(".\\Users_Data.txt", "w");
	User* cursor = users_head;
	while (cursor != NULL) {
		fprintf(f, "%-8s %-22s %-12s %-22s %-42s %-7lf %d\n", cursor->ID, cursor->name, cursor->passwd, cursor->contact, cursor->address, cursor->money, cursor->exist);
		cursor = cursor->next;
	}
	fclose(f);
}
void Merchandises_Update() {
	FILE* f = fopen(".\\Merchandises_Data.txt", "w");
	Merchandise* cursor = merchandises_head;
	while (cursor != NULL) {
		fprintf(f, "%-8s %-22s %-8.1lf %-202s %-8s %d-%d-%d %d\n", cursor->ID, cursor->name, cursor->price, cursor->discribe, cursor->bussiness_id, cursor->launch_time.year, cursor->launch_time.month, cursor->launch_time.day, cursor->state);
		cursor = cursor->next;
	}
	fclose(f);
}
void Orders_Update() {
	FILE* f = fopen(".\\Orders_Data.txt", "w");
	Order* cursor = orders_head;
	while (cursor != NULL) {
		fprintf(f, "%-8s %-8s %-8.1lf %d-%d-%d %-8s %-8s %d\n", cursor->ID, cursor->mer_id, cursor->tamount, cursor->time.year, cursor->time.month, cursor->time.day, cursor->seller_id, cursor->buyer_id, cursor->exist);
		cursor = cursor->next;
	}
	fclose(f);
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
void Update() {
	Users_Update();
	Merchandises_Update();
	Orders_Update();
}