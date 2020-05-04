#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* product(char *str, int k){
	int i=0;
	char appo[1000];
	strcpy(appo, str);
	for (i; i<k-1; i++){
		strcat(str, appo);
	}
	return str;
}

int main(){
	unsigned char str[1000];
	int k;
	scanf("%s", &str[0]);
	scanf("%d", &k);
	char *p;
	p = product(str, k);
	printf("%s\n", str);
	return 0;
}
