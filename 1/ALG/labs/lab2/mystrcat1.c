#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* my_strcat1(char *s1, char *s2){
	char* string = malloc(strlen(s1)+strlen(s2)+1);
	strcpy(string, s1);
	strcat(string, s2);
	return string;
}

int main(){
	unsigned char S1[1000];
	unsigned char S2[1000];

	scanf("%s", &S1[0]);
	scanf("%s", &S2[0]);
	char *p = my_strcat1(S1, S2);

	printf("%s\n", p);
	return 0;
}
