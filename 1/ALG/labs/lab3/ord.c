#include <stdlib.h>
#include <stdio.h>

void merge(int *a, int lena, int *b, int lenb){
	int i, j, k;
	int *c;
	c = (int*) malloc(sizeof(int) * (lena+lenb));
	i=0;
	j=0;
	for(k=0; k<(lena+lenb); k++){
		if(a[i]<b[j] && i<lena || j==lenb){
			c[k] = a[i];
			i++;	
		}else if(j<lenb){
			c[k] = b[j];
			j++;
		}
	}
	for(i=0; i< lena+lenb; i++){
		printf("%d\n", c[i]);
	}
}

int main(){
	int a[100000];
	int b[100000];
	int lena, lenb;

	scanf("%d", &lena);
	int i;
	for(i=0; i<lena; i++){
		scanf("%d", &a[i]);
	}
	scanf("%d", &lenb);
	for(i=0; i<lenb; i++){
		scanf("%d", &b[i]);
	}

	merge(a, lena, b, lenb);
	return 0;
}
