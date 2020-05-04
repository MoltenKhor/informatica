#include <stdio.h>

int my_strlen(char *s){
	int len=0;
	int i=0;
	char *p=s;
	while(p[i] != '\0'){
		len++;
		i++;
	}
	return len;
}

int main(){
	char s[1000];
	scanf("%s", &s[0]);
	int count = my_strlen(s);
	printf("%d\n", count);
	return 0;
}
