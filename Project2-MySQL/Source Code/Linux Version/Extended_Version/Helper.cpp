#include"General.h"
void StrChar_Trans(string a, char* b) {
	for (int i = 0; b[i] != '\0'; i++) {
		b[i] = '\0';
	}
	for (int i = 0; a[i] != '\0'; i++) {
		b[i] = a[i];
	}
}
int C_Num_Counter(string a) {
	int result = 0;
	for (int i = 0; a[i] != '\0'; i++) {
		if (a[i] == ',') result++;
	}
	return result + 1;
}
void Mystrcpy(char a[], char b[]) {
	for (int i = 0; b[i] != '\0'; i++) b[i] = '\0';
	for (int i = 0; a[i] != '\0'; i++) b[i] = a[i];
}
void Modify(char a[], char b[]) {
	for (int i = 0; i < 100; i++) a[i] = '\0';
	for (int i = 0; b[i] != '\0'; i++) a[i] = b[i];
}
void CharClear(char a[]) {
	for (int i = 0; a[i] != '\0'; i++) {
		a[i] = '\0';
	}
}
int getch(void)
{
     struct termios tm, tm_old;
     int fd = 0, ch;
 
     if (tcgetattr(fd, &tm) < 0) {
          return -1;
     }
 
     tm_old = tm;
     cfmakeraw(&tm);
     if (tcsetattr(fd, TCSANOW, &tm) < 0) {
          return -1;
     }

     ch = getchar();
     if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {
          return -1;
     }

     return ch;
}
//void Sort(int array[], int len) {
//	for (int i = 0; i < len; i++) {
//		int min = array[i];
//		int temp_index = i;
//		for (int k = i + 1; k < len; k++) {
//			if (array[k] < min) {
//				min = array[k];
//				temp_index = k;
//			}
//		}
//		int temp = array[i];
//		array[i] = min;
//		array[temp_index] = temp;
//	}
//}
