#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search(char** words, char* searched, int left, int right){
	
	if(left>right){
		return -1;
	}
	
	int pos = (left + right) / 2;
	int cmp = strcmp(searched, words[pos]);

	if(cmp==0){
		return pos;
	}	
	if(cmp<0){
		return search(words, searched, left, pos-1);
	}else{
		return search(words, searched, pos+1, right);
	}
}

int main(){
	int n;
	char **words;
	char **searched;
	scanf("%d", &n);
	words = (char**) malloc(n * sizeof(char*));
	searched = (char**) malloc(n * sizeof(char*));
	int i;
	for(i=0; i<n; i++){
		words[i] = (char*) malloc(101 * sizeof(char));			
		scanf("%s", words[i]);
	}
	int j,k;
	scanf("%d", &j);
	k=0;
	while(j==1){
		searched[k] = (char*) malloc(101 * sizeof(char));			
		scanf("%s", searched[k]);
		k++;
		scanf("%d", &j);
	}
	int z=0;
	for(z; z<k; z++){
		printf("%d\n", search(words, searched[z], 0, n-1));
	}
	return 0;
}
