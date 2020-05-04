#include <stdio.h>

#define MAXSIZE 100000

void reset(int contatore[], int lenght){
	int i=0;
	for(i; i<lenght; i++){
		contatore[i]=0;
	}
}

void add(int contatore[], int lenght, int val){
	contatore[val]++;
}

int main(){
	int contatore[10];
	reset(contatore, 10);
	int ins;
	
	while(1){
		scanf("%d", &ins);
		if(ins>=0 && ins <=9){
			add(contatore, 10, ins);
		}else if(ins == -1){
			int j;
			for(j=0; j<10; j++){
				printf("%d\n", contatore[j]);
			}
			return 0;
		}else{
			return 0;
		}
	}
	return 0;
}
