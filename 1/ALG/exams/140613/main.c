#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>

#define MAX_LEN 101

typedef struct _exam{
	char name[MAX_LEN];
	int cfu;
	int diff;
}Exam;

Exam * readExams(int n){
	Exam * aux = NULL;
	if(n>0){
		aux = (Exam*)malloc(n * sizeof(Exam));
		for(int i=0; i<n; i++){
			scanf("%s", aux[i].name);
			scanf("%d", &aux[i].cfu);
			scanf("%d", &aux[i].diff);
		}
	}
	return aux;
}

int compExams(const void * a, const void * b){
	Exam x = *((Exam *)a);
	Exam y = *((Exam *)b);
	if(x.cfu != y.cfu){
		return (y.cfu-x.cfu);
	}else if(x.diff != y.diff){
			return(x.diff - y.diff);
		}else{			
				return(strcmp(x.name, y.name));	
		}
}

int compExamNames(const void * a, const void * b){
	Exam x = *((Exam*)a);
	Exam y = *((Exam*)b);
	return(strcmp(x.name,y.name));
}

void printExams(Exam * e, int n, int k){
	int i=0;
	int sumCFU = 0;
	int count = 0;
	Exam * selected = malloc(n * sizeof(Exam));
	while(i<n && sumCFU<k){
		if(sumCFU + e[i].cfu <= k){
			sumCFU += e[i].cfu;
			strcpy(selected[count].name, e[i].name);
			count++;
		}
		i++;
	}
	qsort(selected, count, sizeof(Exam), compExamNames);
	for(int i=0; i<count; i++){
		printf("%s\n", selected[i].name);
	}
	free(selected);
}

int main(){
	int k;
	int n;

	Exam * exams;
	scanf("%d", &k);
	scanf("%d", &n);
	exams = readExams(n);

	qsort(exams, n, sizeof(Exam), compExams);
	printExams(exams, n, k);
	return 0;
}

