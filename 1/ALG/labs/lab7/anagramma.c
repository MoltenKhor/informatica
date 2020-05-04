#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _string{
	char string[101];
	char firstAn[101];
}String;

int compareChar(const void * p_a, const void * p_b){
	char a = *((char*)p_a);
	char b = *((char*)p_b);
	return a-b;
}
int compareString(const void * p_a, const void * p_b){
	String a = *((String*)p_a);
	String b = *((String*)p_b);
	int cmp = strcmp(a.firstAn ,b.firstAn);
	if(cmp == 0){
		return strcmp(a.string, b.string);
	}
	return cmp;
}

String * readString(int * N){
	int n;
	String * stringa = NULL;
	scanf("%d", &n);

	stringa = (String*)malloc(n*sizeof(String));
	if(stringa == NULL){ printf("BAD MALLOC\n"); 
	}else{
		for(int i=0; i<n; i++){
			scanf("%s", stringa[i].string);
			strcpy(stringa[i].firstAn, stringa[i].string);
			qsort(stringa[i].firstAn, strlen(stringa[i].firstAn), sizeof(char), compareChar);
		}
	}	
	*N = n;
	return stringa;
}

int main(){
	String *s;
	int n;
	int j = -1;
	s = readString(&n);
	qsort(s, n, sizeof(String), compareString);
	for(int i = 0; i<n; i++){
		if(j==-1){
			printf("%s", s[i].string);
			j++;
		}else{
			if(strcmp(s[i].string, s[j].string) != 0){
				printf("\n%s", s[i].string);
				j=i;
			}else{
				printf("%s", s[i].string);
			}
		}
		printf("\n");
	}
	return 0;
}
