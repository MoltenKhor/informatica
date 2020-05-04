#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_LEN 101 
/* 
  !!!!!!!!!!!! D A  F A R E !!!!!!!!!!!!
  sx e dx sono le posizioni del primo e dell'ultimo elemento dell'array mentre 
  px è la posizione dell'elemento perno.
  La funzione deve restituire la posizione del perno dopo che gli elementi sono 
  stati partizionati.
*/
void swap(char** a, char** b){
	char *tmp = *a;
	*a = *b;
	*b = tmp;
}

int distribuzione(char** a, int sx, int px, int dx) { 
	int i = sx-1;
	int j;
	swap(&a[px], &a[dx]);

	for(j=sx; j<=dx-1; j++){
		if( strcmp(a[j], a[dx]) <= 0 ){
			i++;
			swap(&a[i], &a[j]);
		}
	}
	swap(&a[i+1], &a[dx]);
	return i+1;
}

void quicksort(char** a, int sx, int dx ) {
  
  int perno, pivot;
  if( sx < dx ) {
 		
    pivot = (rand()%(dx-sx+1))+sx;

    perno = distribuzione(a, sx, pivot, dx); /* separa gli elementi minori di a[pivot] 
					        da quelli maggiori o uguali */
    /* Ordina ricorsivamente le due metà */
    quicksort(a, sx, perno-1);
    quicksort(a, perno+1, dx);
    
  }

}

/* Lettura di un array di interi da input. 
Il primo elemento è la lunghezza dell'array */
int legge(char **a, int *len) {

  int i;
  scanf("%d", len);
  if(*len <= 0) return 1;

  a = (char **) malloc(sizeof(char*)* *len);
	if(a==NULL){
		printf("allocated leak 1\n");
	}else{
  for( i = 0; i < *len; i++ )	
	  a[i] = (char *) malloc(MAX_LEN * sizeof(char));
		if(a[i]==NULL){ printf("allocated leak 2\n"); }
		else{
			scanf("%s", a[i]);
		}
	}
  return 0;

}

int main() {
  
  int i, n;
  char **a;

  scanf("%d", &n);
  if(n <= 0) return 1;
 
  a = (char **) malloc(sizeof(char*) * n);
   for( i = 0; i < n; i++ ){ 
     a[i] = (char*) malloc(MAX_LEN * sizeof(char));
     scanf("%s", a[i]);
   }
 
 


  srand(time(NULL));
  quicksort(a, 0, n-1);
  
  /* Stampa l'array ordinato */
  for( i = 0; i < n; i++ ) 
    printf("%s ", a[i]);
	
  return 0;
}
