#include"General.h"

Table Lib[100];

void Doc_Init() {//�ļ���ʼ��
    //FILE* contentf = fopen("E:\\Project2\\Test_Data\\Data_Content.txt", "r");
    FILE* contentf = fopen("./Data_Content.txt", "r");
    if (contentf == NULL) return;
    fscanf(contentf, "\n");
    while (!feof(contentf)) {
        char address[200]{ '\0' };
        fscanf(contentf, "%s\n", address);
        FILE* f = fopen(address, "r");
        fscanf(f, "\n");
        Table* p = new Table;
        for (int i = 0; i < 100; i++) p->Keys[i] = new char[100]{ '\0' };//���ֶα��ڶ������г�ʼ��
        fscanf(f, "Table_Name:\t %s\nKeys_Number:\t %d\nPrimary_Keys:\t %d\nBars_Number:\t %d\n", p->Name, &(p->Keys_Amount), &(p->Primary_index), &(p->Bars_Num));
        //cout << p->Name << " " << p->Keys_Amount << " " << p->Primary_index << " " << p->Bars_Num << endl;
        for (int i = 0; i < p->Keys_Amount; i++) {
            fscanf(f, "%s", p->Keys[i]);
            //cout << p->Keys[i] << " ";
        }
        //cout << endl;
        fscanf(f, "\n");
        for (int i = 0; i < p->Bars_Num; i++) {
            Infor_Bar* k = new Infor_Bar;
            k->C_Num = p->Keys_Amount;
            for (int m = 0; m < k->C_Num; m++) {
                fscanf(f, "%s", k->val[m]);
                //cout << k->val[m] << " ";
            }
            //cout << endl;
            fscanf(f, "\n");
            //���й�����Ϣ��
            Infor_Bar* find = p->head;
            if (find == NULL) {
                p->head = k;
            }
            else {
                int flag = 0;
                int s = p->Primary_index;
                while (find != NULL) {
                    if (strcmp(find->val[s], k->val[s]) <= 0 && ((find->Next != NULL && strcmp(find->Next->val[s], k->val[s]) >= 0) | (find->Next == NULL))) {
                        k->Next = find->Next;
                        find->Next = k;
                        break;
                    }
                    find = find->Next;
                }
            }
        }
        //���ر��ȫ�ֽṹ�庯��
        Lib[Tables_Amount] = *p;
        Tables_Amount++;
        fclose(f);
    }
    fclose(contentf);
}

void Doc_Update() {//�ļ�����
    //FILE* contentf = fopen("E:\\Project2\\Test_Data\\Data_Content.txt", "w");
    FILE* contentf = fopen("./Data_Content.txt", "w");
    for (int i = 0; i < Tables_Amount; i++) {
        //�ñ������ļ�����
        //���ʵ����ļ���ַ
        //string address = "E:\\Project2\\Test_Data\\";
        string address = "./";

        for (int k = 0; Lib[i].Name[k] != '\0'; k++) address.push_back(Lib[i].Name[k]);
        address += ".txt";
        //Ŀ¼�ļ��и���
        fprintf(contentf, "%s\n", address.c_str());
        FILE* f = fopen(address.c_str(), "w");
        //д�������Ϣ
        //1.д������������������������±�
        fprintf(f, "Table_Name:\t %s\nKeys_Number:\t %d\nPrimary_Keys:\t %d\nBars_Number:\t %d\n", Lib[i].Name, Lib[i].Keys_Amount, Lib[i].Primary_index, Lib[i].Bars_Num);
        //2.д�������ֶ�
        for (int m = 0; m < Lib[i].Keys_Amount; m++) {
            fprintf(f, "%s\t", Lib[i].Keys[m]);
        }
        fprintf(f, "\n");
        //3.д��������Ϣ��
        Infor_Bar* cursor = Lib[i].head;
        while (cursor != NULL) {
            for (int m = 0; m < Lib[i].Keys_Amount; m++) {
                fprintf(f, "%s\t", cursor->val[m]);
            }
            fprintf(f, "\n");
            cursor = cursor->Next;
        }
        fclose(f);
    }
    fclose(contentf);
}

//����������
void Create(string User_Order) {
    //�½�����ʼ��
    Table* p = new Table;
    for (int i = 0; i < 100; i++) p->Keys[i] = new char[100]{'\0'};
    //ȥ��ָ������
    string Information = User_Order.substr(13);
    //cout << Information << endl;
    //��ȡ����-����
    int i = 0;
    for (; Information[i] != ' '; i++) {
        p->Name[i] = Information[i];
    }
    //����
    for (int m = 0; m < Tables_Amount; m++) {
        if (strcmp(Lib[m].Name, p->Name) == 0) {
            printf(">>>Duplicate Table Name..\n");
            delete p;
            return;
        }
    }
    //ȥ���������ŷֺ�
    Information = Information.substr(i + 2);
    Information.pop_back();
    Information.pop_back();
    //cout << Information << endl;

    //��ȡ�ַ����ֶ���-����
    while (Information.find(",") != string::npos) {
        int end = Information.find(",");
        string buffer = Information.substr(0, end);
        //������������ͨ��
        if (buffer.find(" ") != string::npos) {
            buffer = buffer.substr(0, buffer.find(" "));
            p->Primary_index = p->Keys_Amount;
        }
        StrChar_Trans(buffer, p->Keys[p->Keys_Amount]);
        //cout << p->Keys[p->Keys_Amount] << endl;
        p->Keys_Amount++;
        Information = Information.substr(end + 1);
    }
    //ĩβ����
    StrChar_Trans(Information, p->Keys[p->Keys_Amount]);
    //cout << p->Keys[p->Keys_Amount] << endl;
    p->Keys_Amount++;
    //cout << p->Primary_index << " " << p->Keys_Amount << endl;
    Lib[Tables_Amount] = *p;
    Tables_Amount++;
    printf(">>>Created Successfully!\n");
}

//չʾ���б��
void Show_Tables() {
    printf("%d table(s):\n", Tables_Amount);
    for (int i = 0; i < Tables_Amount; i++) {
        printf("%s(", Lib[i].Name);
        for (int k = 0; k < Lib[i].Keys_Amount; k++) {
            if (k == Lib[i].Primary_index) printf("%s PRIMARY_KEY", Lib[i].Keys[k]);
            else printf("%s", Lib[i].Keys[k]);
            if (k != Lib[i].Keys_Amount - 1) printf(",");
        }
        printf(")\n");
    }
}

//ɾ�����
void Drop(string User_Order) {
    string Information = User_Order.substr(11);
    Information.pop_back();
    cout << Information << endl;
    const char* buffer = Information.c_str();
    int Find_It = 0;
    for (int i = 0; i < Tables_Amount; i++) {
        if (strcmp(buffer, Lib[i].Name) == 0) {
            for (int k = i; k < Tables_Amount - 1; k++) {
                Lib[k] = Lib[k + 1];
            }
            Tables_Amount--;
            Find_It = 1;
            break;
        }
    }
    if (Find_It == 1) printf(">>>Successfully Deleted!\n");
    else if (Find_It == 0) printf(">>>The table does not exist...\n");
}

//�������ݲ���
void Insert(string User_Order) {
    int Index = -1;
    Infor_Bar* p = new Infor_Bar;
    string Information = User_Order.substr(12);
    //cout << Information << endl;
    //Ѱ�Ҷ�����
    char Target[100]{ '\0' };
    int i = 0;
    for (; Information[i] != ' '; i++) Target[i] = Information[i];
    int Find_Flag = 0;
    for (int k = 0; k < Tables_Amount; k++) {
        if (strcmp(Target, Lib[k].Name) == 0) {
            Find_Flag = 1;
            Index = k;
            break;
        }
    }
    if (Find_Flag == 0) {
        printf(">>>The table does not exist...\n");
    }
    else {
        //ȥ��ָ������
        Information = Information.substr(i + 9);
        Information.pop_back();
        Information.pop_back();
        //cout << Information << endl;
        //��������Ƿ�Ե���
        if (C_Num_Counter(Information) != Lib[Index].Keys_Amount) {
            //cout << C_Num_Counter(Information) << " " << Lib[Index].Keys_Amount;
            printf(">>>Column number mismatch...\n");
        }
        else {
            //�洢����Bar�ṹ��
            int o = 0;//�洢�α�
            p->C_Num = Lib[Index].Keys_Amount;
            while (Information.find(",") != string::npos) {
                string buffer = Information.substr(0, Information.find(","));
                StrChar_Trans(buffer, p->val[o]);
                //cout << p->val[o] << endl;
                o++;
                Information = Information.substr(Information.find(",") + 1);
            }
            StrChar_Trans(Information, p->val[o]);
            //cout << p->val[o] << endl;
        }
        //��������
        Infor_Bar* cursor = Lib[Index].head;
        while (cursor != NULL) {
            if (strcmp(cursor->val[Lib[Index].Primary_index], p->val[Lib[Index].Primary_index]) == 0) {
                printf(">>>Duplicate primary key...\n");
                delete p;
                return;
            }
            cursor = cursor->Next;
        }

        //û����Ĺ���
        Infor_Bar* find = Lib[Index].head;
        if (find == NULL) {
            Lib[Index].head = p;
        }
        else {
            int flag = 0;
            int s = Lib[Index].Primary_index;
            while (find != NULL) {
                if (strcmp(find->val[s], p->val[s]) <= 0 && ((find->Next != NULL && strcmp(find->Next->val[s], p->val[s]) >= 0) | (find->Next == NULL))) {
                    p->Next = find->Next;
                    find->Next = p;
                    break;
                }
                find = find->Next;
            }
        }
        Lib[Index].Bars_Num++;
        printf(">>>Successfully Insertes!\n");
    }
}

//�������ݲ���
void Select(string User_Order) {
    //��ͷȥβ
    User_Order = User_Order.substr(7);
    User_Order.pop_back();

    string Target_Keys;
    string Target_Name1;
    string Limit;
    //����Ƿ��ظ�
    int ifrepeat = 1;
    if (User_Order.substr(0, 8) == "DISTINCT") {
        ifrepeat = 0;
        User_Order = User_Order.substr(9);
    }
    //��������
    int ifall = 0;
    if (User_Order.substr(0, 1) == "*") {
        ifall = 1;
        User_Order = User_Order.substr(7);
    }
    else {
        Target_Keys = User_Order.substr(0, User_Order.find(" "));
        User_Order = User_Order.substr(User_Order.find(" ") + 6);
    }
    //�Ƿ���Լ������
    int iflimit = 0;
    if (User_Order.find(" ") == string::npos) {
        Target_Name1 = User_Order.substr(0);
    }
    else {
        Target_Name1 = User_Order.substr(0, User_Order.find(" "));
        User_Order = User_Order.substr(User_Order.find(" ") + 7);
        Limit = User_Order.substr(0);
        iflimit = 1;
    }
    //��ѯ���Ƿ����
    const char* Target_Name = Target_Name1.c_str();
    int iffind = 0;
    int o = 0;
    for (int i = 0; i < Tables_Amount; i++) {
        if (strcmp(Lib[i].Name, Target_Name) == 0) {
            iffind = 1;
            o = i;
            break;
        }
    }
    if (iffind == 0) {
        printf(">>>The table does not exist...\n");
        return;
    }
    //��������������
    //��Լ�����������
    if (ifall == 1 && iflimit == 0) {
        for (int i = 0; i < Lib[o].Keys_Amount; i++) {
            printf("%-25s", Lib[o].Keys[i]);
        }
        printf("\n");
        Infor_Bar* cursor = Lib[o].head;
        while (cursor != NULL) {
            for (int i = 0; i < Lib[o].Keys_Amount; i++) {
                printf("%-25s", cursor->val[i]);
            }
            printf("\n");
            cursor = cursor->Next;
        }
        return;
    }
    //��Լ������Լ������
    int Limit_number = 0;//Լ����������
    int Limit_type = 0;//0Ϊ��Լ����1ΪAND��2ΪOR
    int Limit_Index[2]{ 0 };
    char Limit_Content[2][100]{ '\0' };
    if (iflimit == 1) {
        char find[100]{ '\0' };
        for (int i = 0; Limit[i] != '='; i++) find[i] = Limit[i];
        Limit = Limit.substr(Limit.find("=") + 1);
        int flag = 0;
        for (int i = 0; i < Lib[o].Keys_Amount; i++) {
            if (strcmp(find, Lib[o].Keys[i]) == 0) {
                Limit_Index[0] = i;
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            printf(">>>The key '%s' does not exist\n", find);
            return;
        }
        if (Limit.find(" ") == string::npos) {
            Limit_number = 1;
            StrChar_Trans(Limit, Limit_Content[0]);
        }
        else {
            Limit_number = 2;
            StrChar_Trans(Limit.substr(0, Limit.find(" ")), Limit_Content[0]);
            Limit = Limit.substr(Limit.find(" ") + 1);
            if (Limit.substr(0, 2) == "OR") {
                Limit_type = 2;
                Limit = Limit.substr(3);
            }
            else if (Limit.substr(0, 3) == "AND") {
                Limit_type = 1;
                Limit = Limit.substr(4);
            }
            char find[100]{ '\0' };
            for (int i = 0; Limit[i] != '='; i++) find[i] = Limit[i];
            Limit = Limit.substr(Limit.find("=") + 1);
            int flag = 0; 
            for (int i = 0; i < Lib[o].Keys_Amount; i++) {
                if (strcmp(find, Lib[o].Keys[i]) == 0) {
                    Limit_Index[1] = i;
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                printf(">>>The key '%s' does not exist\n", find);
                return;
            }
            else {
                StrChar_Trans(Limit, Limit_Content[1]);
            }
        }
    }
    //���ִ�ӡ�����ִ�ӡ
    int Print_Keys_Number = 0;
    int Print_Keys[100]{ 0 };
    if (ifall == 0) {
        Print_Keys_Number = C_Num_Counter(Target_Keys);
        int store_index = 0;
        while (Target_Keys.find(",") != string::npos) {
            string buffer = Target_Keys.substr(0, Target_Keys.find(","));
            Target_Keys = Target_Keys.substr(Target_Keys.find(",") + 1);
            const char* find = buffer.c_str();
            Infor_Bar* cursor = Lib[o].head;
            int flag = 0;
            for (int i = 0; i < Lib[o].Keys_Amount; i++) {
                if (strcmp(Lib[o].Keys[i], find) == 0) {
                    flag = 1;
                    Print_Keys[store_index] = i;
                    store_index++;
                    break;
                }
            }
            if (flag == 0) {
                printf(">>>The key '%s' does not exist...\n", find);
                return;
            }
        }
        int flag = 0;
        const char* find = Target_Keys.c_str();
        for (int i = 0; i < Lib[o].Keys_Amount; i++) {
            if (strcmp(Lib[o].Keys[i], find) == 0) {
                flag = 1;
                Print_Keys[store_index] = i;
                break;
            }
        }
        if (flag == 0) {
            printf(">>>The key '%s' does not exist...\n", find);
            return;
        }
    }
    else if (ifall == 1) Print_Keys_Number = Lib[o].Keys_Amount;
    //�����������ڴ洢������������Ƿ���Ҫȥ��
    int Result_Number = 0;
    char** Main_Buffer[100];
    for (int i = 0; i < 100; i++) {
        Main_Buffer[i] = new char* [100];
        for (int k = 0; k < 100; k++) {
            Main_Buffer[i][k] = new char[100]{ '\0' };
        }
    }
    //��ѯ���������������ƴ��뻺����
    if (iflimit == 1) {
        Infor_Bar* cursor = Lib[o].head;
        while (cursor != NULL) {
            if (Limit_type == 0 && strcmp(cursor->val[Limit_Index[0]], Limit_Content[0]) == 0) {//������Լ��
                if (ifall == 1) {
                    for (int i = 0; i < Lib[o].Keys_Amount; i++) {
                        Mystrcpy(cursor->val[i], Main_Buffer[Result_Number][i]);
                    }
                }
                else if (ifall == 0) {
                    for (int i = 0; i < Print_Keys_Number; i++) {
                        Mystrcpy(cursor->val[Print_Keys[i]], Main_Buffer[Result_Number][i]);
                    }
                }
                Result_Number++;
            }
            else if (Limit_type == 1 && (strcmp(cursor->val[Limit_Index[0]], Limit_Content[0]) == 0 && strcmp(cursor->val[Limit_Index[1]], Limit_Content[1]) == 0)) {//˫����ANDԼ��
                if (ifall == 1) {
                    for (int i = 0; i < Lib[o].Keys_Amount; i++) {
                        Mystrcpy(cursor->val[i], Main_Buffer[Result_Number][i]);
                    }
                }
                else if (ifall == 0) {
                    for (int i = 0; i < Print_Keys_Number; i++) {
                        Mystrcpy(cursor->val[Print_Keys[i]], Main_Buffer[Result_Number][i]);
                    }
                }
                Result_Number++;
            }
            else if (Limit_type == 2 && (strcmp(cursor->val[Limit_Index[0]], Limit_Content[0]) == 0 || strcmp(cursor->val[Limit_Index[1]], Limit_Content[1]) == 0)) {//˫����ANDԼ��
                /*for (int i = 0; i < Lib[o].Keys_Amount; i++) {
                    Mystrcpy(cursor->val[i], Main_Buffer[Result_Number][i]);
                }*/
                if (ifall == 1) {
                    for (int i = 0; i < Lib[o].Keys_Amount; i++) {
                        Mystrcpy(cursor->val[i], Main_Buffer[Result_Number][i]);
                    }
                }
                else if (ifall == 0) {
                    for (int i = 0; i < Print_Keys_Number; i++) {
                        Mystrcpy(cursor->val[Print_Keys[i]], Main_Buffer[Result_Number][i]);
                    }
                }
                Result_Number++;
            }
            cursor = cursor->Next;
        }
    }
    else if (iflimit == 0) {
        Infor_Bar* cursor = Lib[0].head;
        while (cursor != NULL) {
            if (ifall == 1) {
                for (int i = 0; i < Lib[o].Keys_Amount; i++) {
                    Mystrcpy(cursor->val[i], Main_Buffer[Result_Number][i]);
                }
            }
            else if (ifall == 0) {
                for (int i = 0; i < Print_Keys_Number; i++) {
                    Mystrcpy(cursor->val[Print_Keys[i]], Main_Buffer[Result_Number][i]);
                }
            }
            Result_Number++;
            cursor = cursor->Next;
        }
    }
    //�����Ƿ����
    int norepeat[100]{ 0 };
    int norepeat_number = 0;
    if (ifrepeat == 0) {
        for (int i = 0; i < Result_Number; i++) {
            int test = 0;
            for (int k = i + 1; k < Result_Number; k++) {
                for (int s = 0; s < Print_Keys_Number; s++) {
                    if (strcmp(Main_Buffer[i][s], Main_Buffer[k][s]) == 0) {
                        test = 1;
                        break;
                    }
                }
            }
            if (test == 0) {
                norepeat[norepeat_number] = i;
                norepeat_number++;
            }
        }
    }
    //�������
    //�������ƣ������Ϸ�ʵ��
    //���ظ���
    if (ifall == 1) {
        for (int i = 0; i < Lib[o].Keys_Amount; i++) {
            printf("%-25s", Lib[o].Keys[i]);
        }
        printf("\n");
        for (int i = 0; i < Result_Number; i++) {
            for (int k = 0; k < Print_Keys_Number; k++) {
                printf("%-25s", Main_Buffer[i][k]);
            }
            printf("\n");
        }
    }
    //������ֲ����ظ���
    else if (ifall == 0 && ifrepeat == 0) {
        for (int i = 0; i < Print_Keys_Number; i++) {
            printf("%-25s", Lib[o].Keys[Print_Keys[i]]);
        }
        printf("\n");
        for (int i = 0; i < norepeat_number; i++) {
            for (int k = 0; k < Print_Keys_Number; k++) {
                printf("%-25s", Main_Buffer[norepeat[i]][k]);
            }
            printf("\n");
        }
    }
    else if (ifall == 0 && ifrepeat == 1) {
        for (int i = 0; i < Print_Keys_Number; i++) {
            printf("%-25s", Lib[o].Keys[Print_Keys[i]]);
        }
        printf("\n");
        for (int i = 0; i < Result_Number; i++) {
            for (int k = 0; k < Print_Keys_Number; k++) {
                printf("%-25s", Main_Buffer[i][k]);
            }
            printf("\n");
        }
    }
}

//���±��
void Update(string User_Order) {
    //��ͷȥβ
    User_Order = User_Order.substr(7);
    User_Order.pop_back();
    //��ȡ����λ����
    char target_name[100]{ '\0' };
    for (int i = 0; User_Order[i] != ' '; i++) {
        target_name[i] = User_Order[i];
    }
    int iffind = 0;
    int target_index = 0;
    for (int i = 0; i < Tables_Amount; i++) {
        if (strcmp(Lib[i].Name, target_name) == 0) {
            target_index = i;
            iffind = 1;
        }
    }
    if (iffind == 0) {
        printf(">>>The table does not exist...\n");
        return;
    }
//��ȡ�޸Ķ�������
    User_Order = User_Order.substr(User_Order.find(" ") + 5);
    char modify_key[100]{ '\0' };
    for (int i = 0; User_Order[i] != '='; i++) {
        modify_key[i] = User_Order[i];
    }
    User_Order = User_Order.substr(User_Order.find("=") + 1);

    int modify_index = 0;
    char modify_content[100]{ '\0' };
    //�ж�Ŀ����޸ļ��Ƿ����
    iffind = 0;
    for (int i = 0; i < Lib[target_index].Keys_Amount; i++) {
        if (strcmp(Lib[target_index].Keys[i], modify_key) == 0) {
            iffind = 1;
            modify_index = i;
            break;
        }
    }
    if (iffind == 0) {
        printf("The key '%s' does not exist...\n", modify_key);
        return;
    }
    //��ʼ�޸�
    int Limit_Type = 0;//0Ϊ��Լ����1ΪOR˫Լ����2ΪAND˫Լ��
    char Limit_Content[2][100]{ '\0' };
    int Limit_Index[2]{ 0 };
    //��Լ���������޸�
    if (User_Order.find(" ") == string::npos) {
        for (int i = 0; User_Order[i] != '\0'; i++) modify_content[i] = User_Order[i];
        //���ɽ���������ȫ���޸�Ϊһ��
        if (modify_index == Lib[target_index].Primary_index) {
            printf(">>>Can't modify all primary keys as the same key...\n");
            return;
        }
        Infor_Bar* cursor = Lib[target_index].head;
        while (cursor != NULL) {
            Modify(cursor->val[modify_index], modify_content);
            cursor = cursor->Next;
        }
        printf(">>>Successfully Updated!\n");
        return;
    }
    //��Լ��������ǰ����Ϣ׼��
    else {
        //��ȡ�޸�Ŀ������
        StrChar_Trans(User_Order.substr(0, User_Order.find(" ")), modify_content);
        User_Order = User_Order.substr(User_Order.find(" ") + 7);
        //������Լ��
        if (User_Order.find(" ") == string::npos) {
            Limit_Type = 0;
            char find_index[100]{ '\0' };
            StrChar_Trans(User_Order.substr(0, User_Order.find("=")), find_index);
            int flag = 0;
            for (int i = 0; i < Lib[target_index].Keys_Amount; i++) {
                if (strcmp(Lib[target_index].Keys[i], find_index) == 0) {
                    Limit_Index[0] = i;
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                printf("The key '%s' does not exist...\n", find_index);
                return;
            }
            User_Order = User_Order.substr(User_Order.find("=") + 1);
            StrChar_Trans(User_Order, Limit_Content[0]);
        }
        //˫����Լ��
        else {
            //��ȡ��һ���������±꼰����
            char find_index[100]{ '\0' };
            StrChar_Trans(User_Order.substr(0, User_Order.find("=")), find_index);
            int flag = 0;
            for (int i = 0; i < Lib[target_index].Keys_Amount; i++) {
                if (strcmp(Lib[target_index].Keys[i], find_index) == 0) {
                    Limit_Index[0] = i;
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                printf("The key '%s' does not exist...\n", find_index);
                return;
            }
            User_Order = User_Order.substr(User_Order.find("=") + 1);
            StrChar_Trans(User_Order.substr(0, User_Order.find(" ")), Limit_Content[0]);
            User_Order = User_Order.substr(User_Order.find(" ") + 1);
            //��ȡ˫Լ������
            if (User_Order.substr(0, 2) == "OR") {
                Limit_Type = 1;
                User_Order = User_Order.substr(3);
            }
            else if (User_Order.substr(0, 3) == "AND") {
                Limit_Type = 2;
                User_Order = User_Order.substr(4);
            }
            //��ȡ�ڶ����������±꼰����
            StrChar_Trans(User_Order.substr(0, User_Order.find("=")), find_index);
            flag = 0;
            for (int i = 0; i < Lib[target_index].Keys_Amount; i++) {
                if (strcmp(Lib[target_index].Keys[i], find_index) == 0) {
                    Limit_Index[1] = i;
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                printf("The key '%s' does not exist...\n", find_index);
                return;
            }
            User_Order = User_Order.substr(User_Order.find("=") + 1);
            StrChar_Trans(User_Order, Limit_Content[1]);
            //cout << Limit_Index[0] << " " << Limit_Index[1] << endl;
            //cout << Limit_Content[0] << " " << Limit_Content[1] << endl;
        }
    }
    //�������µ��޸�
    if (Limit_Type == 0) {
        Infor_Bar* cursor = Lib[target_index].head;
        while (cursor != NULL) {
            if (strcmp(cursor->val[Limit_Index[0]], Limit_Content[0]) == 0) {
                Mystrcpy(modify_content, cursor->val[modify_index]);
            }
            cursor = cursor->Next;
        }
    }
    else if (Limit_Type == 1) {
        Infor_Bar* cursor = Lib[target_index].head;
        while (cursor != NULL) {
            if (strcmp(cursor->val[Limit_Index[0]], Limit_Content[0]) == 0 || strcmp(cursor->val[Limit_Index[1]], Limit_Content[1]) == 0) {
                Mystrcpy(modify_content, cursor->val[modify_index]);
            }
            cursor = cursor->Next;
        }
    }
    else if (Limit_Type == 2) {
        Infor_Bar* cursor = Lib[target_index].head;
        while (cursor != NULL) {
            if (strcmp(cursor->val[Limit_Index[0]], Limit_Content[0]) == 0 && strcmp(cursor->val[Limit_Index[1]], Limit_Content[1]) == 0) {
                Mystrcpy(modify_content, cursor->val[modify_index]);
            }
            cursor = cursor->Next;
        }
    }
    printf(">>>Successfully Updated!\n");
    return;
}

//ɾ��ָ������
void Delete(string User_Order) {
    //��ͷȥβ
    User_Order = User_Order.substr(12);
    User_Order.pop_back();
    //��ոñ���������
    if (User_Order.find(" ") == string::npos) {
        //��ȡ����1
        char target[100]{ '\0' };
        StrChar_Trans(User_Order, target);
        //���ұ��ҵ�ɾ���������ݣ��Ҳ�������
        int flag = 0;
        for (int i = 0; i < Tables_Amount; i++) {
            if (strcmp(Lib[i].Name, target) == 0) {
                flag = 1;
                Infor_Bar* exist_head = Lib[i].head;
                Infor_Bar* end = exist_head;
                while (exist_head != NULL) {
                    exist_head = exist_head->Next;
                    delete end;
                    end = exist_head;
                }
                return;
            }
        }
        if (flag == 0) {
            printf("The table '%s' does not exist...\n", target);
            return;
        }
    }
    //��ոñ������ݣ�����������
    int target_index = 0;
    int Limit_Type = 0;//0Ϊ��Լ����1ΪOR˫Լ����2ΪAND˫Լ��
    char Limit_Content[2][100]{ '\0' };
    int Limit_Index[2]{ 0 };
    //��ȡ����������2
    char target[100]{ '\0' };
    int iffind = 0;
    StrChar_Trans(User_Order.substr(0, User_Order.find(" ")), target);
    for (int i = 0; i < Tables_Amount; i++) {
        if (strcmp(target, Lib[i].Name) == 0) {
            target_index = i;
            iffind = 1;
            break;
        }
    }
    if (iffind == 0) {
        printf("The table '%s' does not exist...\n", target);
        return;
    }
    User_Order = User_Order.substr(User_Order.find(" ") + 7);
    //��ʼ��������������ɾ������
    if (User_Order.find(" ") == string::npos) {//���������
        Limit_Type = 0;
        char find[100]{ '\0' };
        StrChar_Trans(User_Order.substr(0, User_Order.find("=")), find);
        int flag = 0;
        for (int i = 0; i < Lib[target_index].Keys_Amount; i++) {
            if (strcmp(Lib[target_index].Keys[i], find) == 0) {
                Limit_Index[0] = i;
                flag = 1;
            }
        }
        if (flag == 0) {
            printf(">>>The key '%s' does not exist...\n", target);
            return;
        }
        User_Order = User_Order.substr(User_Order.find("=") + 1);
        StrChar_Trans(User_Order, Limit_Content[0]);
        //��ʼɾ������
        Infor_Bar* obj = Lib[target_index].head;
        if (obj == NULL) { ; }
        else {
            if (strcmp(obj->val[Limit_Index[0]], Limit_Content[0]) == 0) {
                Lib[target_index].head = obj->Next;
                delete obj;
                obj = Lib[target_index].head;
            }
            while (obj != NULL && obj->Next != NULL) {
                if (strcmp(obj->Next->val[Limit_Index[0]], Limit_Content[0]) == 0) {
                    Infor_Bar* help = obj->Next;
                    obj->Next = obj->Next->Next;
                    delete help;
                }
                obj = obj->Next;
            }
            if (obj != NULL && strcmp(obj->val[Limit_Index[0]], Limit_Content[0]) == 0) {
                Lib[target_index].head = obj->Next;
                delete obj;
            }
         }
    }
    else {//˫�������
        //��ȡ��һ����
        char find[100]{ '\0' };
        StrChar_Trans(User_Order.substr(0, User_Order.find("=")), find);
        int flag = 0;
        for (int i = 0; i < Lib[target_index].Keys_Amount; i++) {
            if (strcmp(Lib[target_index].Keys[i], find) == 0) {
                Limit_Index[0] = i;
                flag = 1;
            }
        }
        if (flag == 0) {
            printf(">>>The key '%s' does not exist...\n", target);
            return;
        }
        User_Order = User_Order.substr(User_Order.find("=") + 1);
        StrChar_Trans(User_Order.substr(0, User_Order.find(" ")), Limit_Content[0]);
        User_Order = User_Order.substr(User_Order.find(" ") + 1);
        //�ж�˫����Լ������
        if (User_Order.substr(0, 2) == "OR") {
            Limit_Type = 1;
            User_Order = User_Order.substr(3);
        }
        else if (User_Order.substr(0, 3) == "AND") {
            Limit_Type = 2;
            User_Order = User_Order.substr(4);
        }
        //��ȡ�ڶ�����
        StrChar_Trans(User_Order.substr(0, User_Order.find("=")), find);
        flag = 0;
        for (int i = 0; i < Lib[target_index].Keys_Amount; i++) {
            if (strcmp(Lib[target_index].Keys[i], find) == 0) {
                Limit_Index[1] = i;
                flag = 1;
            }
        }
        if (flag == 0) {
            printf(">>>The key '%s' does not exist...\n", target);
            return;
        }
        User_Order = User_Order.substr(User_Order.find("=") + 1);
        StrChar_Trans(User_Order, Limit_Content[1]);
        cout << "0: " << Limit_Type << endl;
        cout << "1: " << Limit_Index[0] << " " << Limit_Index[1] << endl;
        cout << "2: " << "|" << Limit_Content[0] << "|" << " " << "|" << Limit_Content[1] << "|" << endl;
        //��ʼɾ������
        N1:if (Limit_Type == 1) {//OR����
            Infor_Bar* obj = Lib[target_index].head;
            if (obj == NULL) { ; }
            else {
                if (strcmp(obj->val[Limit_Index[0]], Limit_Content[0]) == 0 || strcmp(obj->val[Limit_Index[1]], Limit_Content[1]) == 0) {
                    Lib[target_index].head = obj->Next;
                    delete obj;
                    obj = Lib[target_index].head;
                    goto N1;
                }
                while (obj != NULL && obj->Next != NULL) {
                    if (strcmp(obj->val[Limit_Index[0]], Limit_Content[0]) == 0 || strcmp(obj->val[Limit_Index[1]], Limit_Content[1]) == 0) {
                        Infor_Bar* help = obj->Next;
                        obj->Next = obj->Next->Next;
                        delete help;
                    }
                    obj = obj->Next;
                }
                if (obj != NULL && (strcmp(obj->val[Limit_Index[0]], Limit_Content[0]) == 0 || strcmp(obj->val[Limit_Index[1]], Limit_Content[1]) == 0)) {
                    Lib[target_index].head = obj->Next;
                    delete obj;
                }
            }
        }
        else if (Limit_Type == 2) {//AND����
            Infor_Bar* obj = Lib[target_index].head;
            if (obj == NULL) { ; }
            else {
                if (strcmp(obj->val[Limit_Index[0]], Limit_Content[0]) == 0 && strcmp(obj->val[Limit_Index[1]], Limit_Content[1]) == 0) {
                    Lib[target_index].head = obj->Next;
                    delete obj;
                    obj = Lib[target_index].head;
                    goto N1;
                }
                while (obj != NULL && obj->Next != NULL) {
                    if (strcmp(obj->val[Limit_Index[0]], Limit_Content[0]) == 0 && strcmp(obj->val[Limit_Index[1]], Limit_Content[1]) == 0) {
                        Infor_Bar* help = obj->Next;
                        obj->Next = obj->Next->Next;
                        delete help;
                    }
                    obj = obj->Next;
                }
                if (obj != NULL && (strcmp(obj->val[Limit_Index[0]], Limit_Content[0]) == 0 && strcmp(obj->val[Limit_Index[1]], Limit_Content[1]) == 0)) {
                    Lib[target_index].head = obj->Next;
                    delete obj;
                }
            }
        }
    }
}

//����Ϊ��չ����

//���ֶ�Ϊ������еĲ���
void Alter(string User_Order) {
    //��ͷȥβ
    User_Order = User_Order.substr(12);
    User_Order.pop_back();
    int target_index = 0;
    int iffind = 0;
    //��ȡ����λ����
    char target[100]{ '\0' };
    StrChar_Trans(User_Order.substr(0, User_Order.find(" ")), target);
    for (int i = 0; i < Tables_Amount; i++) {
        if (strcmp(Lib[i].Name, target) == 0) {
            target_index = i;
            iffind = 1;
            break;
        }
    }
    if (iffind == 0) {
        printf(">>>The table '%s' does not exist...\n", target);
        return;
    }
    User_Order = User_Order.substr(User_Order.find(" ") + 1);
    //��ȡ��������
    int operate_type = 0;//1Ϊ������ͣ�2Ϊɾ������
    if (User_Order.substr(0, 3) == "ADD") {
        operate_type = 1;
        User_Order = User_Order.substr(4);
    }
    else if (User_Order.substr(0, 4) == "DROP") {
        operate_type = 2;
        User_Order = User_Order.substr(5);
    }
    //�����ͽ����޸�
    if (operate_type == 1) {//������
        //��ȡ�ֶ���
        char add_key[100]{ '\0' };
        for (int i = 0; User_Order[i] != '\0'; i++) {
            add_key[i] = User_Order[i];
        }
        //����
        for (int i = 0; i < Lib[target_index].Keys_Amount; i++) {
            if (strcmp(Lib[target_index].Keys[i], add_key) == 0) {
                printf(">>>The new key has existed...\n");
                return;
            }
        }
        //�����ֶ�
        for (int i = 0; add_key[i] != '\0'; i++) {
            Lib[target_index].Keys[Lib[target_index].Keys_Amount][i] = add_key[i];
        }
        Lib[target_index].Keys_Amount++;
        printf(">>>Successfully added the key '%s'!\n", add_key);
    }
    else if (operate_type == 2) {//ɾ����
        //��ȡ�ֶ���
        char drop_key[100]{ '\0' };
        for (int i = 0; User_Order[i] != '\0'; i++) {
            drop_key[i] = User_Order[i];
        }
        //����
        int flag = 0;
        int delete_index = 0;
        for (int i = 0; i < Lib[target_index].Keys_Amount; i++) {
            if (strcmp(Lib[target_index].Keys[i], drop_key) == 0) {
                flag = 1;
                delete_index = i;
                break;
            }
        }
        if (flag == 0) {
            printf(">>>The key '%s' does not exist...\n", target);
            return;
        }
        //ɾ�����ֶΣ�ͬʱɾ���������ݵ����и��ֶ�����
        Infor_Bar* cursor = Lib[target_index].head;
        //ɾ���������ݵĸ��ֶ�
        while (cursor != NULL) {
            for (int i = delete_index; i < Lib[target_index].Keys_Amount - 1; i++) {
                Mystrcpy(cursor->val[i + 1], cursor->val[i]);
            }
            cursor->C_Num = Lib[target_index].Keys_Amount - 1;
            CharClear(cursor->val[Lib[target_index].Keys_Amount - 1]);
            cursor = cursor->Next;
        }
        //ɾ����ļ���ĸ��ֶ�
        for (int i = delete_index; i < Lib[target_index].Keys_Amount - 1; i++) {
            Mystrcpy(Lib[target_index].Keys[i + 1], Lib[target_index].Keys[i]);
        }
        CharClear(Lib[target_index].Keys[Lib[target_index].Keys_Amount - 1]);
        Lib[target_index].Keys_Amount--;
        printf(">>>Successfully droped the key '%s'!\n", drop_key);
    }
}

//Tab�Զ���ȫ-�д�����(³����Ƿȱ)
//������չ��������ʷ��¼
void Tab() {
    string lib[14]{ "ALTER TABLE ", "ADD ", "CREATE TABLE ","DROP TABLE ", "DISTINCT ", "DELETE FROM ","INSERT INTO ","VALUES ","FROM ", "UPDATE ","WHERE ","SHOW TABLES;", "SELECT ", "SET " };
    string find = "";
    int iffind = 0;
    int add_num = 0;
    string buf = "";
    int iftab = 0;
    int screen_chars_num = 0;
    int History_User_state = 0;//�Ƿ�����ʹ����ʷָ��
    while (true) {
        int ch = _getch();
        if (ch == 9) {//tab��
            for (int i = 0; i < 14; i++) {
                if (buf == lib[i].substr(0, buf.length())) {
                    find = lib[i];
                    iffind = 1;
                    break;
                }
            }
            if (iffind == 1) {
                for (int i = buf.length(); i < find.length(); i++) {
                    printf("%c", find[i]);
                    buf.push_back(find[i]);
                    add_num++;
                }
            }
            iftab = 1;
        }
        else if (ch == 13) {//enter��
            printf("\n");
            User_Order += buf;
            buf = "";
            return;
        }
        else if (ch == 8) {//�˸��
            printf("%c", 8);
            printf(" ");
            printf("%c", 8);
            if (buf.empty()) {
                if (!User_Order.empty())User_Order.pop_back();
            }
            else if (!buf.empty())buf.pop_back();
        }
        else if (ch == 27) {//ese��
            for (int i = 0; i < add_num; i++) {
                printf("%c", 8);
                printf(" ");
                printf("%c", 8);
                if (!buf.empty())buf.pop_back();
            }
            iftab = 0;
        }
        else if (ch == 45) {//-��
            for (int i = 0; i < 100; i++) {
                printf("%c", 8);
                printf(" ");
                printf("%c", 8);
            }
            if (History_User_state == 0) {
                cout << History_Orders_Lib[Orders_Cursor];
                History_User_state = 1;
            }
            else {
                if (Orders_Cursor > 0) Orders_Cursor--;
                cout << History_Orders_Lib[Orders_Cursor];
            }
            buf = "";
            User_Order = History_Orders_Lib[Orders_Cursor];
        }
        else if (ch == 61) {//+��
            for (int i = 0; i < 100; i++) {
                printf("%c", 8);
                printf(" ");
                printf("%c", 8);
            }
            if (History_User_state == 0) {
                cout << History_Orders_Lib[Orders_Cursor];
                History_User_state = 1;
            }
            else {
                if (Orders_Cursor < Orders_Num - 1) Orders_Cursor++;
                cout << History_Orders_Lib[Orders_Cursor];
            }
            buf = "";
            User_Order = History_Orders_Lib[Orders_Cursor];
        }
        else {
            if (iftab == 1) {
                User_Order += buf;
                buf = "";
                iffind = 0;
            }
            printf("%c", ch);
            buf.push_back(char(ch));
            if (ch == 32) {
                User_Order += buf;
                buf = "";
            }
        }
    }
}
