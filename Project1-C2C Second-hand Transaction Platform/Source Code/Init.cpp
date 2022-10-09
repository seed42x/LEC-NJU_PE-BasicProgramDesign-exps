#include"General.h"

inline void Users_Init() {
	FILE* f = fopen("E:\\C2C_Data_Test\\Users_Data.txt", "r");
	fscanf(f, "\n");
	while (f != NULL && !feof(f)) {
		User* p = new User;
		fscanf(f, "%s %s %s %s %s %lf %d\n", p->ID, p->name, p->passwd, p->contact, p->address, &p->money, &p->exist);
		users_number++;
		if (users_head == NULL) {
			users_head = p;
			users_tail = p;
		}
		else {
			users_tail->next = p;
			users_tail = p;
		}
	}
	fclose(f);
}

inline void Merchandises_Init() {
	FILE* f = fopen("E:\\C2C_Data_Test\\Merchandises_Data.txt", "r");
	fscanf(f, "\n");
	while (f != NULL && !feof(f)) {
		Merchandise* p = new Merchandise;
		fscanf(f, "%s %s %lf %s %s %d-%d-%d %d\n", p->ID, p->name, &p->price, p->discribe, p->bussiness_id, &p->launch_time.year, &p->launch_time.month, &p->launch_time.day, &p->state);
		merchandises_number++;
		if (merchandises_head == NULL) {
			merchandises_head = p;
			merchandises_tail = p;
		}
		else {
			merchandises_tail->next = p;
			merchandises_tail = p;
		}
	}
	fclose(f);
}

inline void Orders_Init() {
	FILE* f = fopen("E:\\C2C_Data_Test\\Orders_Data.txt", "r");
	fscanf(f, "\n");
	while (f != NULL && !feof(f)) {
		Order* p = new Order;
		fscanf(f, "%s %s %lf %d-%d-%d %s %s %d", p->ID, p->mer_id, &p->tamount, &p->time.year, &p->time.month, &p->time.day, p->seller_id, p->buyer_id, &p->exist);
		orders_number++;
		if (orders_head == NULL) {
			orders_head = p;
			orders_tail = p;
		}
		else {
			orders_tail->next = p;
			orders_tail = p;
		}
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
void Init() {
	Users_Init();
	Merchandises_Init();
	Orders_Init();
}