#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	int key;
	struct _node * left;
	struct _node * right;
}Node;

void depth(Node * t, int k, int h){
	if(t==NULL){printf("NO\n"); return;}
	if(t->key == k){printf("%d\n", h); return;}
	if(k > t->key){
		depth(t->right, k, h+1);
	}else{
		depth(t->left, k, h+1);
	}
}

Node * insertNode(Node * t, int k){
	Node * new = (Node*)malloc(sizeof(Node));
	new->key = k;
	new->left = NULL;
	new->right = NULL;
	if(t == NULL){
		return new;
	}
	if(k > t->key){
		t->right = insertNode(t->right, k);
	}else{
		t->left = insertNode(t->left, k);
	}
	return t;
}

Node * read(int *N){
	Node * abr = NULL;
	int n=0;
	int k;
	scanf("%d", &n);

	for(int i=0; i<n; i++){
		scanf("%d", &k);
		abr = insertNode(abr, k);
	}
	*N = n;
	return abr;
}

int main(){
	Node * ABR = NULL;
	int N=0;
	int k;
	ABR = read(&N);
	
	if(N<=0) return -1;

	do{
		scanf("%d", &k);
		if(k!=-1) depth(ABR, k, 0);
	}while(k>0);


	return 0;
}
