#include <stdio.h>
#include <stdlib.h>
 
void sort(int *numbers, int N){
  int i;
  int j;
	int val;
	for(i=1; i<N; i++){
		val = numbers[i];
		j=i-1;

		while(j>=0 && numbers[j]>val){
			numbers[j+1] = numbers[j];
			j--;
		}
		numbers[j+1] = val;
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
