#include"General.h"
using namespace std;
int Tables_Amount = 0;
string User_Order;

string History_Orders_Lib[200]{ "" };
int Orders_Num = 0;
int Orders_Cursor = 0;

int main() {
	Doc_Init();
	while (true) {
		Tab();
		int ifwell_formed = 1;
		//getline(cin, User_Order);
		if (User_Order.substr(0, 6) == "CREATE") {
			Create(User_Order);
		}
		else if (User_Order == "SHOW TABLES;") {
			Show_Tables();
		}
		else if (User_Order.substr(0, 10) == "DROP TABLE") {
			Drop(User_Order);
		}
		else if (User_Order.substr(0, 6) == "INSERT") {
			Insert(User_Order);
		}
		else if (User_Order.substr(0, 6) == "SELECT") {
			Select(User_Order);
		}
		else if (User_Order.substr(0, 6) == "UPDATE") {
			Update(User_Order);
		}
		else if (User_Order.substr(0, 11) == "DELETE FROM") {
			Delete(User_Order);
		}
		else if (User_Order.substr(0, 12) == "ALTER TABLE ") {
			Alter(User_Order);
		}
		else {
			printf(">>>The Order is not correct!\n");
			ifwell_formed = 0;
		}
		if (ifwell_formed == 1) {
			History_Orders_Lib[Orders_Num] = User_Order;
			Orders_Num++;
		}
		User_Order = "";
		Doc_Update();
	}
	return 0;
}
