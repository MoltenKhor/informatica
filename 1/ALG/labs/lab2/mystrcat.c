#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* my_strcat(char* s1, char* s2){
	unsigned char appo[strlen(s1)];
	int size = strlen(s2)+strlen(s2)+1;
	strcat(appo, s1);
	s1 = malloc(size);
	strcpy(s1, appo);
	strcat(s1, s2);
	return s1;
}

int main(){
	unsigned char s1[1000];
	unsigned char s2[1000];

	scanf("%s", &s1[0]);
	scanf("%s", &s2[0]);

	char *p = my_strcat(s1,s2);
	printf("%s\n", p);

	return 0;
}
