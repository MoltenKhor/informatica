#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_STR 101

typedef struct _string{
	char str [MAX_STR];
	int len;
}String;

int counting(const void * p_a, const void * p_b){
	String a = *((String*)p_a);
	String b = *((String*)p_b);

	if(a.len == b.len){
		return strcmp(a.str, b.str);
	}else{
		return a.len-b.len;
	}
}

int main(){
	String* a;
	int n;
	scanf("%d", &n);
	int i;
	a = (String*)malloc(n*sizeof(String));
	for(i=0; i<n; i++){
		scanf("%s", a[i].str);
		a[i].len = strlen(a[i].str);
	}	
	qsort(a, n, sizeof(String), counting);
	for(i=0; i<n; i++){
		printf("%s\n", a[i].str);
	}
	return 0;
}
