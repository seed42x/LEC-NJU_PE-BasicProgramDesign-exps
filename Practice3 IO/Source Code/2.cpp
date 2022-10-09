#include<stdlib.h>
#include<iostream>
#include<stdio.h>
#include<iomanip>
#include<fstream>
#include<iostream>
#include<iomanip>
#include<algorithm>
using namespace std;
struct Student
{
    int id;
    char name[11];
    int age;
    char birthplace[11];
    double score;
};
/*
第三周作业-文件I/O
2021/3/21 23:00
201220096 钟亚晨
*/

//###convert函数###
//#################
void convert_file(const char* src, const char* dst) {
/*convert函数，以结构体成员为单位读写*/
    FILE* f1 = fopen(src, "r");
    FILE* f2 = fopen(dst, "w");
    if (f1 == NULL) { exit(-1); }
    if (f2 == NULL) { exit(-1); }
    Student buffer;
    //都带回车情况(自己命名155情况)
    fscanf(f1, "%d %s %d %s %lf", &buffer.id, buffer.name, &buffer.age, buffer.birthplace, &buffer.score);
    while (!feof(f1)) {
        fwrite(&buffer, sizeof(buffer), 1, f2);
        fscanf(f1, "%d %s %d %s %lf", &buffer.id, buffer.name, &buffer.age, buffer.birthplace, &buffer.score);
    }
    fclose(f1);
    fclose(f2);
}


//###modify_file函数###
//####################//index-1配套modify_file函数使用
//Part1
void my_sort(Student buffer[], int index) {
/*排序函数，选择排序GPA，选择排序学号*/
    double max;
    int maxi;
    Student temp;
    for (int i = 0; i < index - 1; i++) {
        max = buffer[i].score;
        maxi = i;
        for (int k = i + 1; k < index - 1; k++) {
            if (buffer[k].score > max) {
                max = buffer[k].score;
                maxi = k;
            }
        }
        temp = buffer[i];
        buffer[i] = buffer[maxi];
        buffer[maxi] = temp;
    }
    for(int i = 0; i < index - 1; i++){
	    for (int i = 0; i < index - 2; i++) {
	        if (buffer[i].score == buffer[i + 1].score && buffer[i].id > buffer[i + 1].id) {
	            temp = buffer[i];
	            buffer[i] = buffer[i + 1];
	            buffer[i + 1] = temp;
	        }
	    }
	}
}
//Part2
void modify_file(const char* src, const char* dst) {
/*modify函数，以结构体为单位读写，用my_sort排序*/
    FILE* f1 = fopen(src, "r");
    FILE* f2 = fopen(dst, "w");
    if (f1 == NULL) { exit(-1); }
    if (f2 == NULL) { exit(-1); }
    int index = 0;
    Student buffer[200];
    while (!feof(f1)) {
        fread(&buffer[index], sizeof(Student), 1, f1);
        index++;
    }
    for (int i = 0; i < index - 1; i++) {//由于feof函数多循环一次，此处index必然比实际多1，特殊处理
        if (buffer[i].birthplace[0] == 'N' && buffer[i].birthplace[1] == 'a' && buffer[i].birthplace[2] == 'n' && buffer[i].birthplace[3] == 'j' && buffer[i].birthplace[4] == 'i'
            && buffer[i].birthplace[5] == 'n' && buffer[i].birthplace[6] == 'g' && buffer[i].birthplace[7] == '\0') buffer[i].id += 10000000;
    }
    my_sort(buffer, index);
    for (int i = 0; i < index - 1; i++) {
        fwrite(&buffer[i], sizeof(Student), 1, f2);
    }
    fclose(f1);
    fclose(f2);
}


//###print_file函数###
//###################
void print_file(const char* src) {
/*利用printf打印文件结果*/
    FILE* f1 = fopen(src, "r");
    if (f1 == NULL) { exit(-1); }
    Student buffer;
    //都带回车情况(自己命名155情况)
    fread(&buffer, sizeof(Student), 1, f1);
    while (!feof(f1)) {
        printf("%d %s %d %s %.1lf\n", buffer.id, buffer.name, buffer.age, buffer.birthplace, buffer.score);
        //cout << buffer.id << ' ' << buffer.name << ' ' << buffer.age << ' ' << buffer.birthplace << ' ' << fixed << setprecision(1) << buffer.score << endl;
        fread(&buffer, sizeof(Student), 1, f1);
    }
    fclose(f1);
}


// ATTENTION: DO NOT MODIFY THE CODE BELOW

#include "test.hpp"

int main()
{
    test();
    return 0;
}