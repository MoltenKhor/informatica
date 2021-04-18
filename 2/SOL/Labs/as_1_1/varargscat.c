#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#define REALLOC_INC 16
//[a] La macro utilizza la funzione realloc per modificare la dimensione 
//dell'allocazione di memoria di buff con newsize, se la funzione realloc() ritorna NULL
//in caso di errore allora il preogramma esce e stampa errore di memoria.
#define RIALLOCA(buf, newsize) 					\
    buf = realloc(buf, newsize); 				\
	if(!buf){									\
		printf("ERRORE memoria terminata\n");	\
		exit(-1);								\
	}
 
char* mystrcat(char *buf, size_t sz, char *first, ...) {
	va_list ap;																						//[1] Nomino ap la lista di argomenti variabile di mystrcat
	va_start(ap, first);																			//[2] inizializzo ap ed inserisco il primo elemento tra gli argomenti 

	if(sz < (strlen(first)+1)){																		//[3] Controllo il valore di sz rispetto alla dimensione del primo argomento
		RIALLOCA(buf, sz+strlen(first)+1+REALLOC_INC);												//se la dimensione sz riportata come argomento non e' sufficiente viene
		sz+=strlen(first)+1+REALLOC_INC;															//invocata la macro di reallocazione di memoria con la nuova dimensione
	}

	strncat(buf, first, strlen(first));																//[4] Concateno l'attuale buffer con il primo argomento tra le variabili
	
	char *s=NULL;																						
	while((s=va_arg(ap, char*))!=NULL){																//[5] Scorro il vettore contenente gli argomenti della funzione e di volta in volta
		if(sz < strlen(buf) + strlen(s)+1){															//effettuo il controllo e il ridimensionamento dell'allocazione di memoria e poi 
			RIALLOCA(buf, strlen(buf)+strlen(s)+1+REALLOC_INC);										//il concatenamento 
			sz = strlen(buf)+strlen(s)+1+REALLOC_INC;
		}
		strncat(buf, s, strlen(s));
	}
	
	va_end(ap);																						//[6] Concludo, infine, l'uso del vettore di argomenti
	return buf;
}  
 
int main(int argc, char *argv[]) {
  if (argc != 7) { printf("troppi pochi argomenti\n"); return -1; }
  char *buffer=NULL;
  RIALLOCA(buffer, REALLOC_INC);  // macro che effettua l'allocazione
  buffer[0]='\0';
  buffer = mystrcat(buffer, REALLOC_INC, argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], NULL);
  printf("%s\n", buffer);     
  free(buffer);
  return 0;
}