#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* my_strcpy(char* dest, char* src){
	strcpy(dest, src);
	return dest;
}

int main(){
	unsigned char src[1000];
	unsigned char dest[1000];

	scanf("%s", &src[0]);

	char *p = my_strcpy(dest, src);

	printf("%s\n", p);
	
	return 0;

}
