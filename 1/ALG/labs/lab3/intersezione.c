#include <stdio.h>
#include <stdlib.h>

int intersection_ord(int *x, int lenx, int *y, int leny){
	int i = 0, j = 0;
	int size = 0;
	while(i < lenx && j < leny){
		if(x[i] < y[j]){
			i++;
			continue;
		}
		if(x[i]>y[j]){
			j++;
			continue;
		}
		size++;
		i++;
		j++;
	}
	return size;
}

int main(){
	int a1[1000000];
	int a2[1000000];
	int q1, q2;

	scanf("%d", &q1);
	int len1, len2;
	for(len1=0; len1<q1; len1++){
		scanf("%d", &a1[len1]);
	}

	scanf("%d", &q2);
	for(len2=0; len2<q2; len2++){
		scanf("%d", &a2[len2]);
	}
	int count = intersection_ord(a1, q1, a2, q2);
	printf("%d\n", count);
	return 0;
}
