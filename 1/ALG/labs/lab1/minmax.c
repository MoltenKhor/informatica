#include <stdio.h>

void minmax(int* valori,int lenght, int* min, int* max){
	int i=0;
	int minval=10000000;
	int maxval=0;
	
	for(i; i<lenght; i++){
		if(valori[i]<minval){
			*min=i;
			minval=valori[i];
		}
		if(valori[i]>maxval){
			*max=i;
			maxval=valori[i];
		}
	}
	return;
}

int main(){
	int valori[10];
	int i=0;
	int min, max;
	for(i; i<10; i++){
		scanf("%d", &valori[i]);
	}
	int* ptr = &valori[0];
	minmax(ptr, 10, &min, &max);
	int minval=valori[min];
	int maxval=valori[max];
	printf("%d\n%d\n%d\n%d\n", min, minval, max, maxval);
	return 0;
}
