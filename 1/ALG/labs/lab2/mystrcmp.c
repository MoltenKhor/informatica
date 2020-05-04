#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int my_strcmp(char* s1, char *s2){
	unsigned int is1 = 0;
	unsigned int is2 = 0;
	int size1, size2;
	size1 = strlen(s1);
	size2 = strlen(s2);
	int i;
	for(i=0; i< size1; i++){
		is1 += s1[i];
	}
	for(i=0; i<size2; i++){
		is2 += s2[i];
	}
	if(is1 == is2){
		return 0;
	}else if (is1 < is2){
		return -1;
	}else return 1;
}

int main(){
	unsigned char s1[1000];
	unsigned char s2[1000];

	scanf("%s", &s1[0]);
	scanf("%s", &s2[0]);

	int result = my_strcmp(s1,s2);
	if(result == 1){
		printf("+%d\n", result);
	}else printf("%d\n", result);


	return 0;
}
