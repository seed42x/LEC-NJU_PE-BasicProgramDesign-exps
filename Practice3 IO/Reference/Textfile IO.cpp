#define _CRT_SECURE_NO_WARNINGS
#define PROGRAM 3

#if PROGRAM==1
//Student Scores  ASCII file

//Test Data
/*
001 zhang 4 70 80 85 90
002 li 5 85 60 75 90 80
E
*/
//003 wang 3 85 90 86
//004 zhao 5 88 90 98 78 90
//E

#include <cstdio>
#include <cstdlib>
//using namespace std;

int main()
{
	FILE *fp=fopen("scores.txt", "w");  //ASCII FILE
	if (fp==NULL)
	{
		printf("Open Failed!\n");
		exit(-1);
	}
	char id[11], name[9];
	int num_of_courses, score;
	printf("Please input Stu.ID., Name, No. Selection and Grade(Ending with \"E\")\n ");
	scanf("%10s", id);
	while(id[0]!='E')
	{
		scanf("%8s", name);
		scanf("%d", &num_of_courses);
		fprintf(fp, "%s %s %d ", id, name, num_of_courses);
		for(int i=0; i<num_of_courses; i++)
		{
			scanf("%d", &score);
			fprintf(fp, "%d ", score);
		}
		fputc('\n', fp);
		scanf("%10s", id);
	}
	fclose(fp);
	return 0;
}

#endif

#if PROGRAM==2
//Students.dat Binary File
//Test Data
//001 zhang 0 1980 5 3 Nanjing 5
//002 li 1 1985 12 4 Shanghai 3
//E


#include <cstdio>
#include <cstdlib>
//using namespace std;
//average calc.
int main()
{
	FILE *fp=fopen("scores.txt", "r");  //ASCII FILE
	if (fp==NULL)
	{
		printf("Open Failed\n");
		exit(-1);
	}
	char id[11], name[9];
	int num_of_courses, score, total;
	fscanf(fp, "%10s", id);
	while(!feof(fp))
	{
		fscanf(fp, "%8s", name);
		fscanf(fp, "%d", &num_of_courses);
		total=0;
		for(int i=0; i<num_of_courses; i++)
		{
			fscanf(fp, "%d", &score);
			total+=score;
		}
		printf("%s, %s, %d\n", id, name, total/num_of_courses);
		fscanf(fp, "%10s", id);
	}
	fclose(fp);
	return 0;
}
#endif
