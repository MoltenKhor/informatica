#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct _node{
	int k;
	int L;
	int R;
	struct _node * left;
	struct _node * right;
	struct _node * prev;
}Node;

Node * insertNode(Node * node, int key){
	if(node == NULL){
		Node * aux = (Node*)malloc(sizeof(Node));
		aux->k = key;
		aux->L = 0;
		aux->R = 0;
		aux->left = NULL;
		aux->right = NULL;
		return aux;
	}
	if(key < node->k){
		node->L++;
		node->left = insertNode(node->left, key);
	}else{
		node->R++;
		node->right = insertNode(node->right, key);
	}
	return node;
}

Node * readABR(int * dim){
	int n;
	int k;
	Node * t = NULL;
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		scanf("%d", &k);
		t = insertNode(t,k);
	}
	*dim = n;
	return t; 
}

void printNodes(Node * t){
	if(t == NULL){ return; }
	printNodes(t->left);
	printNodes(t->right);
	if(t->L > t->R){
		printf("%d\n", t->k);
	}
	return;
}

int main (){
	Node * tree;
	int n;
	tree = readABR(&n);
	if(n != 0){
		printNodes(tree);
	}else{
		printf("0\n");
	}
	return 0;
}
