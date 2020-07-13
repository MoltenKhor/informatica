#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>

#define MAX_LEN 101

typedef struct _exam{
	char name[MAX_LEN];
	int credit;
	int difficulty;
}Exam;

Exam * readExams(int n){
	Exam * aux = NULL;
	if(n>0){
		aux = (Exam * )malloc(n*sizeof(Exam));
		for(int i=0; i<n; i++){
			scanf("%s", aux[i].name);
			scanf("%d", &aux[i].credit);
			scanf("%d", &aux[i].difficulty);
		}
	}
	return aux;
}

int compExams(const void * a, const void * b){
	Exam x = *((Exam*)a);
	Exam y = *((Exam*)b);
	if(x.credit != y.credit) return y.credit - x.credit;
	else{
		if(x.difficulty != y.difficulty) return y.difficulty - x.difficulty;
		else return strcmp(x.name, y.name);
	}
}

int compExamName(const void * a, const void * b){
	Exam x = *((Exam*)a);
	Exam y = *((Exam*)b);
	return strcmp(x.name, y.name);
}

void printExams(Exam * e, int n, int k){
	Exam * selected = malloc(n*sizeof(Exam));
	int i=0;
	int count = 0;
	int sumCredit = 0;
	while(i<n && sumCredit < k){
		if(sumCredit + e[i].credit <= k){
			sumCredit += e[i].credit;
			strcpy(selected[count].name, e[i].name);
			count++;
		}
		i++;
	}
	qsort(selected, count, sizeof(Exam), compExamName);

	for(int i=0; i<count; i++){
		printf("%s\n", selected[i].name);
	}
	free(selected);
}

int main(){
	Exam * exams;
	int k;
	int n;
	scanf("%d", &k);
	scanf("%d", &n);
	exams = readExams(n);
	qsort(exams,n,sizeof(Exam), compExams);
	printExams(exams, n, k);
	free(exams);
	return 0;
}
