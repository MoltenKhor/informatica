#include <stdio.h>
#include <stdlib.h>
typedef struct _node{
    int k;
    struct _node * left;
    struct _node * right;
    int hasProp;
}Node;

Node * insertABR(Node * t, int key){
    if(t == NULL){
        Node * aux = (Node*)malloc(sizeof(Node));
        aux->k=key;
        aux->left=NULL;
        aux->right=NULL;
        return aux;
    }else{
        if(key < t->k){
            t->left = insertABR(t->left, key);
        }else{
            t->right = insertABR(t->right, key);
        }
    }
}

Node * readABR(int * dim){
    Node * t;
    int n;
    int k;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%d", &k);
        t = insertABR(t, k);
    }
    *dim = n;
    return t;
}
typedef struct _res{
    int R;
    int L;
}Res;


Res numLR(Node * t){
    Res res;
    res.L=0;
    res.R=0;
    if(t==NULL){
        return res;
    }
    if(t->left != NULL){
        Res rSx = numLR(t->left);
        res.L += 1+rSx.L;
    }
    if(t->right != NULL){
        Res rDx = numLR(t->right);
        res.R += 1+rDx.R;
    }

    if(res.L > res.R) t->hasProp = 1;
    return res;
}

void printABR(Node * t){
    if(t==NULL) return;
    printABR(t->left);
    if(t->hasProp){
        printf("%d\n",t->k);
    }
    printABR(t->right);
}

void freeABR(Node *t){
    if(t==NULL) return;
    if(t->left == NULL && t->right == NULL){
        free(t); return;
    }
    freeABR(t->left);
    freeABR(t->right);
}

int ian(){
    Node * tree;
    int n;
    tree = readABR(&n);
    numLR(tree);
    printABR(tree);
    freeABR(tree);
    return 0;
}