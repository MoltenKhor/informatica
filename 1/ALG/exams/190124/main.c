#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

typedef struct _node{
	int k;
	int c; //1=black 0=red
	struct _node * left;
	struct _node * right;
}Node;

Node * insertABR(Node * t, int key, int color){
	if(t == NULL){
		Node * aux = malloc(sizeof(Node));
	 	aux->k=key;
		aux->c=color;
		aux->left=NULL;
		aux->right=NULL;
		return aux;	
	}else{
		if(key < t->k){
			t->left = insertABR(t->left, key, color);
		}else{
			t->right = insertABR(t->right, key, color);
		}
	}
	return t;
}

Node * readABR(int n){
	Node * aux = NULL;
	int k;
	int c;
	for(int i=0; i<n; i++){
		scanf("%d %d", &k, &c);
		aux = insertABR(aux, k, c);
	}
	return aux;
}

int max(int a, int b){
	if(a>=b)return a;
	else return b;
}

int getMaxDim(Node * t, int d){
	if(t==NULL) return d;
	int dSx;
	int dDx;
	if(t->c == 0){
		dSx = getMaxDim(t->left, d+1);
		dDx = getMaxDim(t->right, d+1);
	}else{
		d = 0;
		dSx = getMaxDim(t->left, d);
		dDx = getMaxDim(t->right, d);
	}
	return max(dSx,dDx);
}

int main(){
	Node * tree = NULL;
	int n = 0;
	scanf("%d", &n);
	tree = readABR(n);
	printf("%d\n", getMaxDim(tree,0));
	return 0;
}
