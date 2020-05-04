#include <stdlib.h>
#include <stdio.h>

typedef struct _node{
	int key;
	struct _node * left;
	struct _node * cent;
	struct _node * right;
}Node;

int count(Node *t){
	if(t==NULL){ return 0;}
	if(t->left != NULL && t->right != NULL && t->cent != NULL){ return 1 + count(t->left) + count(t->right) + count(t->cent); }
	return count(t->left) + count(t->right) + count(t->cent);	
}

Node * insertNode(Node *t, int k){
	Node * new = (Node*)malloc(sizeof(Node));
	new->key = k;
	new->left=NULL;
	new->right=NULL;
	new->right=NULL;
	if(t==NULL){
		return new;
	}
	if((k%t->key)==0){
		t->cent = insertNode(t->cent, k);
	}else{
		if(k < t->key){
			t->left = insertNode(t->left, k);
		}else{
			t->right = insertNode(t->right, k);
		}
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
	Node * ABR;
	int N=0;
	ABR = read(&N);

	printf("%d\n", count(ABR));
	return 0;
}
