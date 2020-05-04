#include <stdlib.h>
#include <stdio.h>

typedef struct _node{
	int key;
	int counter;
	struct _node * next;
	struct _node * prev;
}Node;

void insert(Node **tail, Node **head, int val){
	Node* new = malloc(sizeof(Node));
	new->key = val;
	new->counter = 0;
	new->next = NULL;
	new->prev = *tail;

	if(*tail != NULL){
		(*tail)->next = new;
	}

	*tail = new;

	if(*head == NULL){
		*head = new;
	}
}

int search(Node **head, Node **tail, int val){
	Node *current = *head;
	int pos = 0;

	while(current!=NULL && current->key != val){
		current = current->next;
		pos++;
	}

	if(current == NULL){
		return -1;
	}

	(current->counter)++;
	
	while(current->prev != NULL && current->counter > current->prev->counter){
		Node *appo = current->prev;
		current->prev = appo->prev;
		appo->next = current->next;
		appo->prev = current;
		
		if(current->next != NULL){
			current->next->prev = appo;
		}
		if(current->prev != NULL){
			current->prev->next = current;
		}

		current->next = appo;
	}

	if(current->prev == NULL){
		*head = current;
	}

	if(current->next == NULL){
		*tail = current;
	}

	return pos;
}

int main(){
	int n;
	scanf("%d", &n);
	Node *head = NULL;
	Node *tail = NULL;

	for(int i=0; i<n; i++){
		int val;
		scanf("%d", &val);
		insert(&tail, &head, val);
	}

	int result;
	do{
		int tmp;
		scanf("%d", &tmp);
		result = search(&head, &tail, tmp);
		printf("%d\n", result);
	}while(result != -1);
	return 0;
}
