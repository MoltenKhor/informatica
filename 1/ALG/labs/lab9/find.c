#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	int key;
	struct _node * left;
	struct _node * right;
}Node;

int find(Node *a, Node *b, int K){
	if(a == NULL && b == NULL){ return 1; }
	if((a == NULL && b != NULL) || (a != NULL && b == NULL)){ return 0; }

	if((a->key == K) && (b->key == K)){ return 1; }

	if((a->key == K && b->key != K) ||(a->key != K && b->key == K)){ return 0; }

	if(K < a->key){
		return find(a->left, b->left, K);
	}else{
		return find(a->right, b->right, K);
	}
	
}

Node * insertNode(Node *t, int k){
	Node * new = (Node*)malloc(sizeof(Node));
 	new->key = k;
	new->left = NULL;
	new->right = NULL;
	if(t == NULL){
		return new;
	}	
	if(k < t->key){
		t->left = insertNode(t->left, k);
	}else{
		t->right = insertNode(t->right, k);
	}
	return t;
}

Node * read(int N){
	int k;
	Node * raw;
	for(int i=0; i<N; i++){
		scanf("%d", &k);
		raw = insertNode(raw, k);
	}
	return raw;
}

int main(){
	Node * ABR1;
	Node * ABR2;
	int N, K;
	scanf("%d %d", &N, &K);
	ABR1 = read(N);
	ABR2 = read(N);
	printf("%d\n", find(ABR1, ABR2, K));
	return 0;
}
