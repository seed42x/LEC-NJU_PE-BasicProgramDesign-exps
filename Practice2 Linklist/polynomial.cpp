#include <cstdio>
#include<math.h>//引入pow函数
#include<stdio.h>
#include<iostream>
using namespace std;
/*
说明：
程设基础实验-第二次作业
链表-多项式-加减乘幂次
备注：对输入的解析在题意基础上进行了泛化，可以解析不是那么严格的表达式(但对-x状况仍需进行一些修改)
2021/3/13/13:46
201220096 钟亚晨
*/

//###链表结构体#####################################################################################
//##################################################################################################
struct Polynomial {
    long long int base = 0;//系数
    long long int index = 0;//指数
    Polynomial* next = NULL;//链表结构
};
//##################################################################################################

//###打印函数#######################################################################################
//##################################################################################################
void PrintPolynomial(const Polynomial& poly)
{
    const Polynomial* cursor = &poly;
    while (cursor != NULL) {
        if (cursor->base > 0) cout << '+' << cursor->base << 'x' << '^' << cursor->index;//正数加+打印
        else if (cursor->base < 0) cout << cursor->base << 'x' << '^' << cursor->index;//负数直接打印
        cursor = cursor->next;
    }
    cout << endl;
}
//##################################################################################################


//###解析函数(程序核心)#############################################################################
//##################################################################################################
Polynomial InitPolynomial(const char* str)
{
    int cursor = 0;
    Polynomial* head = NULL;
    Polynomial* tail = NULL;
    while (str[cursor] != '\0') {
        //###新节点初始化###
        Polynomial* p = new Polynomial;
        p->next = NULL;
        //###解析系数和指数###
        if (str[cursor] == 'x') {
            p->index = 1;
            p->base = 1;
        }
        else {
            //###解析系数###
            int base_len = 0;
            if (str[cursor] == '-') {
                cursor++;
                for (int k = cursor; str[k] != '\0' && str[k] != 'x' && str[k] != '\0'; k++) base_len++;
                for (int k = cursor, j = 1; k < cursor + base_len; k++, j++)p->base -= ((long long int)str[k] - 48) * (long long int)pow(10, base_len - j);
            }
            else {
                if (str[cursor] == '+') cursor++;
                for (int k = cursor; str[k] != 'x' && str[k] != '\0' && str[k] != '-' && str[k] != '+'; k++) base_len++;
                for (int k = cursor, j = 1; k < cursor + base_len; k++, j++)p->base += ((long long int)str[k] - 48) * (long long int)pow(10, base_len - j);
            }
            cursor += base_len;
            //###解析指数###
            if (str[cursor] == '+' || str[cursor] == '-') p->index = 0;
            else if (str[cursor + 1] != '\0' && str[cursor + 1] == '^') {
                cursor += 2;
                int index_len = 0;
                for (int k = cursor; str[k] != '\0' && str[k] != '+' && str[k] != '-'; k++)index_len++;
                for (int k = cursor, j = 1; k < cursor + index_len; k++, j++) {
                    p->index += ((long long int)str[k] - 48) * (long long int)pow(10, index_len - j);
                }
                cursor += index_len;
            }
            else if (str[cursor] == 'x' && (str[cursor + 1] == '-' || str[cursor + 1] == '+' || str[cursor + 1] == '\0')) {
                p->index = 1;
                cursor++;
            }
        }
        //###节点挂载###
        if (head == NULL) {
            head = p;
            tail = p;
        }
        else {
            Polynomial* find = head;
            int flag = 0;
            //###有可直接加和节点###
            while (find != NULL) {
                if (find->index == p->index) {
                    find->base += p->base;
                    flag = 1;
                    delete p;
                    break;
                }
                find = find->next;
            }
            //###无可直接加和节点
            if (flag == 0) {
                //###有可插入节点位###
                find = head;
                if (p->index > find->index) {
                    p->next = find;
                    head = p;
                    flag = 1;
                }
                else {
                    while (find != NULL) {
                        if (find->index > p->index && find->next != NULL && find->next->index < p->index) {
                            p->next = find->next;
                            find->next = p;
                            flag = 1;
                            break;
                        }
                        find = find->next;
                    }
                }
                //###只能挂载在尾部###
                if (flag == 0) {
                    tail->next = p;
                    tail = p;
                }
            }
        }
    }
    return *head;
}
//##################################################################################################

//###加和函数#######################################################################################
//##################################################################################################
Polynomial Add(const Polynomial& lhs, const Polynomial& rhs)
{
    const Polynomial* cursor = &rhs;
    const Polynomial* head0 = &lhs;
    Polynomial* head = NULL;
    Polynomial* tail = NULL;
    //对lhs链表进行复制
    while (head0 != NULL) {
        Polynomial* p = new Polynomial;
        p->index = head0->index;
        p->base = head0->base;
        if (head == NULL) {
            head = p;
            tail = p;
        }
        else {
            tail->next = p;
            tail = p;
        }
        head0 = head0->next;
    }
    //以复制出的lhs链表为处理主体，逐次取rhs上的节点进行加和
    while (cursor != NULL) {
        Polynomial* p = new Polynomial;
        p->index = cursor->index;
        p->base = cursor->base;
        p->next = NULL;
        Polynomial* find = head;
        int flag = 0;
        //###有可直接加和节点###
        while (find != NULL) {
            if (find->index == p->index) {
                find->base += p->base;
                flag = 1;
                break;
            }
            find = find->next;
        }
        //###无可直接加和节点###
        if (flag == 0) {
            find = head;
            //###有可插入节点位###
            if (p->index > find->index) {
                p->next = find;
                head = p;
                flag = 1;
            }
            else {
                while (find != NULL) {
                    if (find->index > p->index && find->next != NULL && find->next->index < p->index) {
                        p->next = find->next;
                        find->next = p;
                        flag = 1;
                        break;
                    }
                    find = find->next;
                }
            }
            //###只能挂载在尾部###
            if (flag == 0) {
                tail->next = p;
                tail = p;
            }
        }
        cursor = cursor->next;
    }
    return *head;
}
//##################################################################################################

//###减法函数#######################################################################################
//##################################################################################################
Polynomial Minus(const Polynomial& lhs, const Polynomial& rhs)
{
    const Polynomial* cursor = &rhs;
    const Polynomial* head0 = &lhs;
    Polynomial* head = NULL;
    Polynomial* tail = NULL;
    while (head0 != NULL) {
        Polynomial* p = new Polynomial;
        p->index = head0->index;
        p->base = head0->base;
        if (head == NULL) {
            head = p;
            tail = p;
        }
        else {
            tail->next = p;
            tail = p;
        }
        head0 = head0->next;
    }
    while (cursor != NULL) {
        Polynomial* p = new Polynomial;
        p->index = cursor->index;
        p->base = -cursor->base;//该函数以加和函数为原型，仅在该步不同
        p->next = NULL;
        Polynomial* find = head;
        int flag = 0;
        //###有可直接加和节点###
        while (find != NULL) {
            if (find->index == p->index) {
                find->base += p->base;
                flag = 1;
                break;
            }
            find = find->next;
        }
        //###无可直接加和节点###
        if (flag == 0) {
            find = head;
            //###有可插入节点位###
            if (p->index > find->index) {
                p->next = find;
                head = p;
                flag = 1;
            }
            else {
                while (find != NULL) {
                    if (find->index > p->index && find->next != NULL && find->next->index < p->index) {
                        p->next = find->next;
                        find->next = p;
                        flag = 1;
                        break;
                    }
                    find = find->next;
                }
            }
            //###只能挂载在尾部###
            if (flag == 0) {
                tail->next = p;
                tail = p;
            }
        }
        cursor = cursor->next;
    }
    return *head;
}
//##################################################################################################

//###乘法函数#######################################################################################
//##################################################################################################
Polynomial Multiply(const Polynomial& lhs, const Polynomial& rhs)
{
    const Polynomial* re_scanner = &lhs;
    const Polynomial* flo_scanner = &rhs;
    Polynomial* head = NULL;
    Polynomial* tail = NULL;
    //每次取lhs中的一项与rhs中每一项相乘，相加到结果链表head中，嵌套双循环(在循环lhs节点的前提下循环rhs节点)
    while (re_scanner != NULL) {
        while (flo_scanner != NULL) {
            Polynomial* p = new Polynomial;
            p->next = NULL;
            p->index = re_scanner->index + flo_scanner->index;
            p->base = re_scanner->base * flo_scanner->base;
            if (head == NULL) {
                head = p;
                tail = p;
            }
            else {
                Polynomial* find = head;
                int flag = 0;
                while (find != NULL) {
                    if (find->index == p->index) {
                        find->base += p->base;
                        flag = 1;
                        delete p;
                        break;
                    }
                    find = find->next;
                }
                if (flag == 0) {
                    find = head;
                    if (p->index > find->index) {
                        p->next = find;
                        head = p;
                        flag = 1;
                    }
                    else {
                        while (find != NULL) {
                            if (find->index > p->index && find->next != NULL && find->next->index < p->index) {
                                p->next = find->next;
                                find->next = p;
                                flag = 1;
                                break;
                            }
                            find = find->next;
                        }
                    }
                    if (flag == 0) {
                        tail->next = p;
                        tail = p;
                    }
                }
            }
            flo_scanner = flo_scanner->next;
        }
        re_scanner = re_scanner->next;
        flo_scanner = &rhs;
    }
    return *head;
}
//##################################################################################################

//###幂次函数#######################################################################################
//##################################################################################################
Polynomial Power(const Polynomial& base, int exp)
{
    //以乘法函数为基础进行循环处理以实现幂次运算
    Polynomial result = base;
    while (exp > 1) {
        result = Multiply(result, base);
        exp--;
    }
    return result;
}
//##################################################################################################

// ATTENTION: DO NOT MODIFY THE CODE BELOW

#include "test.hpp"

int main()
{
    test();
    return 0;
}
