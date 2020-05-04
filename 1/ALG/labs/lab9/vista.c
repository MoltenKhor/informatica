#include <stdlib.h>
#include <stdio.h>

typedef struct _node{
	int key;
	struct _node * left;
	struct _node * right;
}Node;

Node * insertNode(Node * t, int k){
	Node * new = (Node*)malloc(sizeof(Node));
	new->key = k;
	new->left = NULL;
	new->right= NULL;
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
	int k;
	int n;
	Node * raw;
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		scanf("%d", &k);
		raw = insertNode(raw, k);
	}
	*N = n;
	return raw;
}

int max(int a, int b){return (a>b)?a:b;}

int visit(Node * t){
	if(t==NULL) return 0;
	return 1 + max(visit(t->right), visit(t->left));
}

int main(){
	Node * ABR = NULL;
	int N=0;
	ABR = read(&N);
	printf("%d\n", visit(ABR));
	return 0;
}
