#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
/*
2021/3/20
文件I/O-读写文本文件
201220096 钟亚晨
*/
void merge_file(const char* src1, const char* src2, const char* dst) {
    FILE* f1 = fopen(src1, "r");
    FILE* f2 = fopen(src2, "r");
    FILE* f3 = fopen(dst, "at");
    char ch;
    while ((ch = fgetc(f1)) != EOF) fputc(ch, f3);
    while ((ch = fgetc(f2)) != EOF) fputc(ch, f3);
    fclose(f1);
    fclose(f2);
    fclose(f3);
}


void upper_file(const char* src, const char* dst) {
    FILE* f1 = fopen(src, "r");
    FILE* f2 = fopen(dst, "at");
    char ch;
    while ((ch = fgetc(f1)) != EOF) fputc(toupper(ch), f2);
    fclose(f1);
    fclose(f2);
}


void lower_file(const char* src, const char* dst) {
    FILE* f1 = fopen(src, "r");
    FILE* f2 = fopen(dst, "at");
    char ch;
    while ((ch = fgetc(f1)) != EOF) fputc(tolower(ch), f2);
    fclose(f1);
    fclose(f2);
}

int my_compare(string s1, char* s2) {
    int com_index = 0;
    while (s1[com_index] != '\0' && s2[com_index] != '\0') {
        if ((int)s1[com_index] > (int)s2[com_index]) return 1;
        else if ((int)s1[com_index] < (int)s2[com_index]) return -1;
        com_index++;
    }
    if (s1[com_index] == '\0' && s2[com_index] != '\0') return -1;
    else if (s1[com_index] != '\0' && s2[com_index] == '\0') return 1;
    else return 0;
}
void my_inc_sort(char** array, int begin, int end) {
    char temp;
    int mini;
    string min;
    for (int i = begin; i < end; i++) {
        min = array[i];
        mini = i;
        for (int k = i + 1; k < end; k++) {
            if (my_compare(min, array[k]) == 1) {
                min = array[k];
                mini = k;
            }
        }
        for (int s = 0; s < 100; s++) {
            temp = array[i][s];
            array[i][s] = array[mini][s];
            array[mini][s] = temp;
        }
    }
}
void sort_inc_file(const char* src, const char* dst) {
    FILE* f1 = fopen(src, "r");
    FILE* f2 = fopen(dst, "at");
    char* buffer[100];
    for (int i = 0; i < 100; i++) buffer[i] = new char[100];
    int index = 0;
    int amount = 0;
    while (fgets(buffer[index], 100, f1)) {
        index++;
        amount++;
    }
    my_inc_sort(buffer, 0, amount);
    for (int i = 0; i < amount; i++) {
        fputs(buffer[i], f2);
    }
    fclose(f1);
    fclose(f2);
}

void my_dec_sort(char** array, int begin, int end) {
    char temp;
    int mini;
    string min;
    for (int i = begin; i < end; i++) {
        min = array[i];
        mini = i;
        for (int k = i + 1; k < end; k++) {
            if (my_compare(min, array[k]) == -1) {
                min = array[k];
                mini = k;
            }
        }
        for (int s = 0; s < 100; s++) {
            temp = array[i][s];
            array[i][s] = array[mini][s];
            array[mini][s] = temp;
        }
    }
}
void sort_dec_file(const char* src, const char* dst) {
    FILE* f1 = fopen(src, "r");
    FILE* f2 = fopen(dst, "at");
    char* buffer[100];
    for (int i = 0; i < 100; i++) buffer[i] = new char[100];
    int index = 0;
    int amount = 0;
    while (fgets(buffer[index], 100, f1)) {
        index++;
        amount++;
    }
    my_dec_sort(buffer, 0, amount);
    for (int i = 0; i < amount; i++) {
        fputs(buffer[i], f2);
    }
    fclose(f1);
    fclose(f2);
}

// ATTENTION: DO NOT MODIFY THE CODE BELOW

#include "test.hpp"

int main()
{
    test();
    return 0;
}