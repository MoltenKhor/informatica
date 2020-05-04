#include <stdio.h>
#include <stdlib.h>

void sort(int *numbers, int N){
	int i;
	int j;
	int posmin;
	int tmp;
	for(i=0; i<N-1; i++){
		posmin = i;
		for(j=i+1; j<N; j++){
			if(numbers[j]<numbers[posmin]){
				posmin=j;
			}
		}
		if(posmin != i){
			tmp = numbers[i];
			numbers[i] = numbers[posmin];
			numbers[posmin] = tmp;
		}
	}
	for(i=0; i<N; i++){
		printf("%d\n", numbers[i]);
	}
	return;
}

int main(){
	int N;
	scanf("%d", &N);
	int i;
	int numbers[10000];
	for(i=0; i<N; i++){
		scanf("%d", &numbers[i]);
	}

	sort(numbers, N);

	return 0;
}
