#include <stdlib.h>
#include <stdio.h>

int somma(int *a, int len){
	int max = 0;
	int somma = 0;
	int i;

	for(i=0; i<len; i++){

		if(somma>0){
			somma+=a[i];
		}else{
			somma = a[i];
		}
		if(somma>max){
			max = somma;
		}
	}
	return max;
}

int main(){
	unsigned int a[1000];
	int len;
	scanf("%d", &len);
	int i;
	for(i=0; i<len; i++){
		scanf("%d", &a[i]);
	}

	printf("%d\n", somma(a, len));

	return 0;
}
