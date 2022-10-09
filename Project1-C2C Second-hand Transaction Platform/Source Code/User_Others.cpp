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
void User_Login() {
    User_Login_Menu_View();
    printf(">>>�����������û�����");
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
        printf(">>>�������¼���룺");
        char cin_passwd[11]{ '\0' };
        cin >> cin_passwd;
        if (strcmp(find->passwd, cin_passwd) == 0) {
            Current_User = find;
            Sleep(500);
            printf(">>>��¼�ɹ������������û����˵�...");
            Sleep(500);
            User_Main_Menu();
        }
        else {
            Sleep(500);
            printf(">>>��¼ʧ�ܣ������������˵�...");
            Main_Menu();
        }
    }
    else {
        printf(">>>δ�ҵ����û�...");
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
N12:printf(">>>�������û���(���Ȳ�����10����ֻ��ʹ�����ĺ��ֻ�Ӣ����ĸ)��");
    cin >> buffer;
    if (sizeof(buffer) > 21) {
        printf(">>>���ȳ�������...");
        system("pause");
        Main_Menu();
    }
    User* test_cursor = users_head;
    while (test_cursor != NULL) {
        if (strcmp(buffer, test_cursor->name) == 0 && test_cursor->exist == 1) {
            printf(">>>���û����ѱ�ʹ�ã�����������...");
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
    printf(">>>�����������˺�����(���Ȳ�����20���ҽ���ʹ��Сд��ĸ������)��");
    cin >> buffer;
    if (buffer.length() > 11) {
        printf(">>>���ȳ�������...");
        system("pause");
        Main_Menu();
    }
    for (int i = 0; buffer[i] != '\0'; i++) {
        p->passwd[i] = buffer[i];
    }
}
inline void User_Register_Contact(User* p) {
    string buffer;
    printf(">>>������������ϵ��ʽ(���Ȳ�����20������ʹ������)��");
    cin >> buffer;
    if (buffer.length() > 21) {
        printf(">>>���ȳ�������...");
        system("pause");
        Main_Menu();
    }
    for (int i = 0; buffer[i] != '\0'; i++) {
        p->contact[i] = buffer[i];
    }
}
inline void User_Register_Address(User* p) {
    string buffer;
    printf(">>>���������ĵ�ַ(���Ȳ�����20���ҽ���ʹ������/Ӣ����ĸ):");
    cin >> buffer;
    if (buffer.length() > 41) {
        printf(">>>���ȳ�������...");
        system("pause");
        Main_Menu();
    }
    for (int i = 0; buffer[i] != '\0'; i++) {
        p->address[i] = buffer[i];
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
        printf(">>>�û�ע��ʧ�ܣ������������˵�...");
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
        printf(">>>�û�ע��ɹ��������������˵�...");
        Users_Update();
        Sleep(500);
        Main_Menu();
    }
    else {
        cout << ">>>δ�ҵ���ָ�����������...";
        Sleep(500);
        goto N1;
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
void User_Main_Menu() {
    User_Main_Menu_View();
    int user_operate = 0;
    cout << ">>>���������ָ�";
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
        cout << ">>>δ�ҵ���ָ�����������...";
        Sleep(500);
        User_Main_Menu();
    }
}