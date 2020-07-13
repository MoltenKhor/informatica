#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct _node{
    int k;
    struct _node * left;
    struct _node * right;
    struct _node * prev;
}Node;

typedef struct _res{
    int maxSum;
    int min;
}Res;

Res getMaxSum(Node * u){
    if(u==NULL){
        Res r;
        r.maxSum = 0;
        r.min = INT_MAX;
        return r;
    }else{
        Res res;
        res.maxSum = u->k;
        res.min = u->k;

        Res rDx = getMaxSum(u->right);
        Res rSx = getMaxSum(u->left);

        if(rSx.maxSum == rDx.maxSum){
            res.maxSum += rSx.maxSum;
            if(rSx.min < res.min){
                res.min = rSx.min;
            }
        }else{
            if(rSx.maxSum < rDx.maxSum){
                res.maxSum += rDx.maxSum;
                if(rDx.min < res.min){
                    res.min = rDx.min;
                }
            }else{
                res.maxSum += rSx.maxSum;
                if(rSx.min < res.min){
                    res.min = rSx.min;
                }
            }
        }
        return res;
    }
}

Node * insertABR(Node * t, int k){
    if(t == NULL){
        Node * aux = (Node*)malloc(sizeof(Node));
        aux->k = k;
        aux->right = NULL;
        aux->left = NULL;
        aux->prev = NULL;
        return aux;
    }else{
        if(k< t->k){
            t->left = insertABR(t->left, k);
        }else{
            t->right = insertABR(t->right, k);
        }
    }
    return t;
}

Node * readTree(int * dim){
    Node * aux = NULL;
    int n; 
    int k;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%d", &k);
        aux = insertABR(aux, k);
    }
    *dim = n;
    return aux;
}

int main(){
    int N;
    Node * tree;
    tree = readTree(&N);
    if(N==0) printf("--0--\n");
    else{
        Res r = getMaxSum(tree);
        printf("%d\n", r.min); 
    }
    return 0;
}