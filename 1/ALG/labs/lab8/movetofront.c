#include <stdlib.h>
#include <stdio.h>

typedef struct _node{
	int key;
	struct _node * next;
}Node;

void insert(Node** list, int val){
	Node * new = malloc(sizeof(Node));
	new->key = val;
	new->next = NULL;
	if(*list == NULL){
		*list = new;
	}else{
		Node *current = *list;

		while(current->next != NULL){
			current = current->next;
		}
		current->next = new;
	}
}

int moveToFront(Node** list, int search){
	int pos = 0;
	Node* current = *list;
	Node* prev = NULL;

	while(current != NULL && current->key != search){
		pos++;
		prev=current;
		current=current->next;
	}

	if(current == NULL){
		return -1;
	}else{
		if(prev==NULL){
			return pos;
		}

		prev->next = current->next;
		current->next = *list;
		*list = current;
		return pos;
	}
}

int main(){
	Node * list = NULL;
	int n;
	int val;
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		scanf("%d", &val);
		insert(&list, val);
	}

	int output = 0;
	int search;
	while(output != -1){
		scanf("%d", &search);
		output = moveToFront(&list, search);
		printf("%d\n", output);
	}
	return 0;
}
