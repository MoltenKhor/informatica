#include <stdlib.h>
#include <stdio.h>

typedef struct _node{
	int key;
	struct _node * left;
	struct _node * right;
}Node;

void oread(Node *t){
	if(t==NULL){ return; }
	oread(t->left);
	printf("%d\n" ,t->key);
	oread(t->right);
}

Node * insertNode(Node *t, int k){
	Node * new = (Node*)malloc(sizeof(Node));
	new->key = k;
	new->left = NULL;
	new->right = NULL;
	if(t==NULL){
		return new;
	}
	if(k < t->key){
		t->left = insertNode(t->left, k);	
	}else{
		t->right = insertNode(t->right, k);
	}
	return t;
}

Node * read(int * N){
	int n;
	int k;
	Node * raw;
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		scanf("%d", &k);
		raw = insertNode(raw, k);
	}
	*N = n;
	return raw;
}

int main(){
	int N=0;
	Node * ABR;
	ABR = read(&N);
	oread(ABR);
	return 0;
}
