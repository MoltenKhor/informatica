#include <stdio.h>

void somma(int N, int* S, int* som){
	*som+=*S;
	if(N!=1){
		*S+=2;
		somma(N-1, S, som);	
	}else return;
}

int main(){
	int N;
	scanf("%d", &N);
	int S=1;
	int som=0;
	somma(N, &S, &som);
	printf("%d\n", som);
	return 0;
}	
