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
void Update() {
	Users_Update();
	Merchandises_Update();
	Orders_Update();
}