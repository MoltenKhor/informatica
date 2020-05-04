#include <stdio.h>
#include <string.h>
const int M = 100;

void sort(char words[][M], int N){
	int i,j;
	char single[100];
	for(i=1; i<N; i++){
		strcpy(single, words[i]);
		j=i-1;

		while(j>=0 && strcmp(words[j], single)>0){
			strcpy(words[j+1], words[j]);
			j--;
		}
		strcpy(words[j+1], single);															
	}
	for(i=0; i<N; i++){
		printf("%s\n", words[i]);
	}
	return;
}

int main(){
	char words[3000][M];
	int N;
	int i;
	scanf("%d", &N);
	for(i=0; i<N; i++){
		scanf("%s", &words[i][0]);
	}

	sort(words, N);

	return 0;
}
