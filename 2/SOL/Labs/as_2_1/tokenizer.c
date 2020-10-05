#define _POSIX_C_SOURCE 200112L  // necessaria per strtok_r
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// strdup non e' C99, ed e' necessario il prototipo altrimenti 
// il compilatore restituisce un warning
char *strdup(const char *s);

int main(int argc, char *argv[]) {
    if (argc != 3) {
	fprintf(stderr, "use: %s stringa1 stringa2\n", argv[0]);
	return -1;
    }
#if 0  // versione non corretta
    
    char* token1 = strtok(argv[1], " ");
    
    while (token1) {
	printf("%s\n", token1);
	char* token2 = strtok(argv[2], " ");
	while(token2) {
	    printf("%s\n", token2);
	    token2 = strtok(NULL, " ");
	}
	token1 = strtok(NULL, " ");
    }
    
#else  // versione rientrante 

    char *str1    = strdup(argv[1]);  // copio la prima stringa perche' strtok_r la modifica

    char* tmpstr1 = NULL; // stato della prima strtok_r
    char* tmpstr2 = NULL; // stato della seconda strtok_r
    char* token1  = strtok_r(str1, " ", &tmpstr1);
    while (token1) {
	printf("%s\n", token1);

	char *str2    = strdup(argv[2]); // copio la seconda stringa
	char* token2  = strtok_r(str2, " ", &tmpstr2); // <--- qui si puo' usare strtok

	while(token2) {
	    printf("%s\n", token2);
	    token2 = strtok_r(NULL, " ", &tmpstr2);  // <--- qui si puo' usare strtok
	}
	free(str2);  // libero memoria
	token1 = strtok_r(NULL, " ", &tmpstr1); // continuo con la prima stringa
    }

    free(str1);  // libero la memoria prima di uscire
#endif
    return 0;
}
