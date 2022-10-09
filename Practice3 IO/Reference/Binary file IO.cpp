#define _CRT_SECURE_NO_WARNINGS
#define PROGRAM 3

#if PROGRAM==1
//Student Scores  Binary file  Input


#include <cstdio>
#include <cstdlib>
//using namespace std;
/*
001 zhang 0 1994 6 6 Nanjing 2
002 li 1 1995 8 8 Beijing 3
003 wu 1 1995 8 8 Beijing 3
E
*/ 
enum Sex {MALE, FEMALE};

struct Date
{
	int year;
	int month;
	int day;
};

enum Major {MATHEMATICS, PHYSICS, CHEMISTRY, COMPUTER, GEOGRAPHY, ASTRONOMY, ENGLISH, CHINESE, PHILOSOPHY};

struct Student
{
	char id[11];
	char name[9];
	Sex sex;
	Date birth_date;
	char birth_place[40];
	Major major;
};

int main()
{
	
	FILE *fp=fopen("students.dat", "wb");  //Binary File
	if(fp==NULL)
	{
		printf("Open Failed!\n");
		exit(-1);
	}
	Student st;
	int tsex; //input sex 0: MALE, 1: FEMALE
	int tmajor; //input Major
	printf("Please input Stu. ID, Name, Sex, Birth date, Hometown and Major(Ending with 'E' in the Stu.ID. place):\n");
	scanf("%s", st.id);  
	while(st.id[0]!='E')
	{
		scanf("%s", st.name);
		scanf("%d", &tsex);
		switch(tsex)
		{
		case 0: st.sex=MALE; break;
		case 1: st.sex=FEMALE; break;
		default: printf("Sex Confusing!\n"); exit(-1);
		}
		scanf("%d %d %d", &st.birth_date.year, &st.birth_date.month, &st.birth_date.day);
		scanf("%39s", st.birth_place);
		scanf("%d", &tmajor);
		switch(tmajor)
		{
		case 0: st.major=MATHEMATICS; break;
		case 1: st.major=PHYSICS; break;
		case 2: st.major=CHEMISTRY; break;
		case 3: st.major=COMPUTER; break;
		case 4: st.major=GEOGRAPHY; break;
		case 5: st.major=ASTRONOMY; break;
		case 6: st.major=ENGLISH; break;
		case 7: st.major=CHINESE; break;
		case 8: st.major=PHILOSOPHY; break;
		default: printf("Major not Found!\n"); exit(-1);
		}
		/*
		size_t fwrite(const void* buffer, size_t size, size_t count, FILE* stream);
         1buffer:a pointer to fetch the address of data;
         2size:the byte number which will be wrote;
         3count:the number of data will be wrote;
         4stream:target pointer;
         5return the actual number of count.
		*/ 
		fwrite(&st, sizeof(Student), 1, fp);
		scanf("%10s", st.id);
	}
	fclose(fp);
	return 0;
}

#endif


#if PROGRAM==2
//Students.dat Binary File  Input
//Display all Record
#include <cstdio>
#include <cstdlib>
//using namespace std;

enum Sex {MALE, FEMALE};

struct Date
{
	int year;
	int month;
	int day;
};

enum Major {MATHEMATICS, PHYSICS, CHEMISTRY, COMPUTER, GEOGRAPHY, ASTRONOMY, ENGLISH, CHINESE, PHILOSOPHY};

struct Student
{
	char id[11];
	char name[9];
	Sex sex;
	Date birth_date;
	char birth_place[40];
	Major major;
};

int main()
{

	FILE *fp=fopen("students.dat", "rb");  //Binary File
	if(fp==NULL)
	{
		printf("Open Failed\n");
		exit(-1);
	}
	Student st;
//	int count=0;
   

	printf("Stu. ID.\t Name\t Sex\t Birth             Date\t Hometown\t Major\n");
	
	fread(&st, sizeof(Student), 1, fp);
	while(!feof(fp))
	{
		printf("%8s\t%6s\t", st.id, st.name);
		switch(st.sex)
		{
		case MALE: printf("MALE\t"); break;
		case FEMALE: printf("FEMALE\t"); break;
		//default: printf("Sex Confusing!\n"); exit(-1);
		}
		printf("Year %d Month %d Day %d\t", st.birth_date.year, st.birth_date.month, st.birth_date.day);
		printf("%10s\t", st.birth_place);
		switch(st.major)
		{
		case MATHEMATICS: printf("MATHEMATICS"); break;
		case PHYSICS: printf("PHYSICS"); break;
		case CHEMISTRY: printf("CHEMISTRY"); break;
		case COMPUTER: printf("COMPUTER"); break;
		case GEOGRAPHY: printf("GEOGRAPHY"); break;
		case ASTRONOMY: printf("ASTRONOMY"); break;
		case ENGLISH: printf("ENGLISH"); break;
		case CHINESE: printf("CHINESE"); break;
		case PHILOSOPHY: printf("PHILOSOPHY"); break;
		//default: printf("Major not Found!\n"); exit(-1);
		}
		printf("\n");
		fread(&st, sizeof(Student), 1, fp);
	}
	fclose(fp);
	return 0;
}
#endif

