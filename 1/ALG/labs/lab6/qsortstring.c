#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int counting(const void * p_a, const void * p_b){
	char** a = (char**)p_a;
	char** b = (char**)p_b;
	return strcmp(*a,*b) * -1;
}

int main(){
	int N;
	char** words;
	scanf("%d", &N);
	words = (char**)malloc(N * sizeof(char*));
	int i;
	for(i=0; i<N; i++){
		words[i] = (char*)malloc(101 * sizeof(char));
		scanf("%s", words[i]);
	}
	qsort(words, N, sizeof(char*), counting);
	for(i=0; i<N; i++){
		printf("%s\n", words[i]);
	}
}
