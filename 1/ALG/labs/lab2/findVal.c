#include <stdio.h>

int* FindVal(int a[], int len, int val){
	int i;
	int *p=NULL;
	for(i=0; i<len; i++){
		if(a[i]==val){
			p = &a[i];			
			return p;
		}
	}
return NULL;
}

int main(){
	int i=0;
	int a[10];
	
	for(i=0; i<10; i++){
		scanf("%d", &a[i]);
	}	
	int val;
	scanf("%d", &val);
	if(FindVal(a, 10, val) != NULL){
		printf("trovato\n");
	}else printf("non trovato\n");
	return 0;
}
