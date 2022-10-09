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
void User_Login() {
    User_Login_Menu_View();
    printf(">>>请输入您的用户名：");
    char cin_name[21]{ '\0' };
    cin >> cin_name;
    User* find = users_head;
    while (find != NULL) {
        if (strcmp(find->name, cin_name) == 0 && find->exist == 1) {
            break;
        }
        find = find->next;
    }
    if (find != NULL) {
        printf(">>>请输入登录密码：");
        char cin_passwd[11]{ '\0' };
        cin >> cin_passwd;
        if (strcmp(find->passwd, cin_passwd) == 0) {
            Current_User = find;
            Sleep(500);
            printf(">>>登录成功，即将进入用户主菜单...");
            Sleep(500);
            User_Main_Menu();
        }
        else {
            Sleep(500);
            printf(">>>登录失败，即将返回主菜单...");
            Main_Menu();
        }
    }
    else {
        printf(">>>未找到该用户...");
        system("pause");
        Main_Menu();
    }
}

inline void User_Register_ID(User* p) {
    int len = 0;
    int number = users_number;
    while (number != 0) {
        len++;
        number /= 10;
    }
    number = users_number;
    for (int i = 6 - len; len > 0;) {
        p->ID[i] = char((number % 10) + 48);
        number = number / 10;
        len--;
    }
}
inline void User_Register_Name(User* p) {
    char buffer[21]{ '\0' };
N12:printf(">>>请输入用户名(长度不超过10，且只能使用中文汉字或英文字母)：");
    cin >> buffer;
    if (sizeof(buffer) > 21) {
        printf(">>>长度超出限制...");
        system("pause");
        Main_Menu();
    }
    User* test_cursor = users_head;
    while (test_cursor != NULL) {
        if (strcmp(buffer, test_cursor->name) == 0 && test_cursor->exist == 1) {
            printf(">>>该用户名已被使用，请重新输入...");
            system("pause");
            goto N12;
        }
        test_cursor = test_cursor->next;
    }
    for (int i = 0; buffer[i] != '\0'; i++) {
        p->name[i] = buffer[i];
    }
}
inline void User_Register_Passwd(User* p) {
    string buffer;
    printf(">>>请输入您的账号密码(长度不超过20，且仅可使用小写字母和数字)：");
    cin >> buffer;
    if (buffer.length() > 11) {
        printf(">>>长度超出限制...");
        system("pause");
        Main_Menu();
    }
    for (int i = 0; buffer[i] != '\0'; i++) {
        p->passwd[i] = buffer[i];
    }
}
inline void User_Register_Contact(User* p) {
    string buffer;
    printf(">>>请输入您的联系方式(长度不超过20，仅可使用数字)：");
    cin >> buffer;
    if (buffer.length() > 21) {
        printf(">>>长度超出限制...");
        system("pause");
        Main_Menu();
    }
    for (int i = 0; buffer[i] != '\0'; i++) {
        p->contact[i] = buffer[i];
    }
}
inline void User_Register_Address(User* p) {
    string buffer;
    printf(">>>请输入您的地址(长度不超过20，且仅可使用中文/英文字母):");
    cin >> buffer;
    if (buffer.length() > 41) {
        printf(">>>长度超出限制...");
        system("pause");
        Main_Menu();
    }
    for (int i = 0; buffer[i] != '\0'; i++) {
        p->address[i] = buffer[i];
    }

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
void User_Register() {
    User_Register_Menu_View();
    User* p = new User;
    User_Register_ID(p);
    User_Register_Name(p);
    User_Register_Passwd(p);
    User_Register_Contact(p);
    User_Register_Address(p);
    User_Register_Sure_View(p);
    string user_operate;
N1:cin >> user_operate;
    if (user_operate == "N") {
        delete p;
        printf(">>>用户注册失败，即将返回主菜单...");
        Sleep(500);
        Main_Menu();
    }
    else if (user_operate == "Y") {
        if (users_head == NULL) {
            users_head = p;
            users_tail = p;
        }
        else {
            users_tail->next = p;
            users_tail = p;
        }
        users_number++;
        printf(">>>用户注册成功，即将返回主菜单...");
        Users_Update();
        Sleep(500);
        Main_Menu();
    }
    else {
        cout << ">>>未找到该指令，请重新输入...";
        Sleep(500);
        goto N1;
    }
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
void User_Main_Menu() {
    User_Main_Menu_View();
    int user_operate = 0;
    cout << ">>>请输入操作指令：";
    cin >> user_operate;
    switch (user_operate) {
    case 1:
        User_Seller_Menu();
        break;
    case 2:
        User_Buyer_Menu();
        break;
    case 3:
        PIM();
        break;
    case 4:
        Main_Menu();
        break;
    default:
        cout << ">>>未找到该指令，请重新输入...";
        Sleep(500);
        User_Main_Menu();
    }
}