#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct _tnode{
	int key;
	struct _tnode * left;
	struct _tnode * right;
	struct _tnode * prev;

}TNode;

typedef struct _res{
	int maxSum;
	int min;
}Res;

Res getMaxSum(TNode * u){
	if(u == NULL){
		Res r;
		r.maxSum = 0;
		r.min = INT_MAX;
		return r;
	}else{
		Res res;
		res.maxSum = u->key;
		res.min = u->key;
		Res sx = getMaxSum(u->left);
		Res dx = getMaxSum(u->right);

		if(sx.maxSum == dx.maxSum){
			res.maxSum += sx.maxSum;
			if(sx.min < res.min){
				res.min = sx.min;
			}
		}else{
			if(sx.maxSum < dx.maxSum){
				res.maxSum += dx.maxSum;
				if(dx.min < res.min){
					res.min = dx.min;
				}
			}else{
				res.maxSum += sx.maxSum;
				if(sx.min <res.min){
					res.min = sx.min;
				}
			}
		}
		return res;
	}
}

TNode * insertABR(TNode * node, int key){
	if(node == NULL){
		TNode * aux = (TNode *) malloc(sizeof(TNode));
		aux->key = key;
		aux->right = NULL;
		aux->left = NULL;
		return aux;
	}
	if(key < node->key){
		node->left = insertABR(node->left, key);
	}else{
		node->right = insertABR(node->right, key);
	}

	return node;
}

TNode * readTree(int * dim){
		TNode * t = NULL;
		int n;
		int k;
		scanf("%d", &n);
		for(int i=0; i<n; i++){
			scanf("%d", &k);
			t = insertABR(t,k);
		}
		*dim = n;
		return t;
}

int main(){
	TNode * tree;
	int n;
	tree = readTree(&n);
	if(n==0){
		printf("0\n");
	}else{
		Res r = getMaxSum(tree);
		printf("%d\n", r.min);
	}
	return 0;
}
